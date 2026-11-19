/*
 * command_parser.c
 */
#include "global.h"
#include "command_parser.h"

static CommandParserState state = CMD_IDLE;

void command_parser_init(void)
{
    state = CMD_IDLE;
}

void command_parser_fsm(uint8_t received_char)
{
    /* A new '!' starts or restarts command parsing. */
    if (received_char == '!') {
        state = CMD_EXCLAMATION;
        return;
    }

    switch (state) {
        case CMD_IDLE:
            /* Ignore characters outside a command, including CR/LF. */
            break;

        case CMD_EXCLAMATION:
            if (received_char == 'R') {
                state = CMD_R;
            } else if (received_char == 'O') {
                state = CMD_O;
            } else {
                state = CMD_IDLE;
            }
            break;

        case CMD_R:
            state = (received_char == 'S') ? CMD_S : CMD_IDLE;
            break;

        case CMD_S:
            state = (received_char == 'T') ? CMD_T : CMD_IDLE;
            break;

        case CMD_T:
            if (received_char == '#') {
                isRST = 1;
            }
            state = CMD_IDLE;
            break;

        case CMD_O:
            state = (received_char == 'K') ? CMD_K : CMD_IDLE;
            break;

        case CMD_K:
            if (received_char == '#') {
                isOK = 1;
            }
            state = CMD_IDLE;
            break;

        default:
            state = CMD_IDLE;
            break;
    }
}
