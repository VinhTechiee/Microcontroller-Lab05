/*
 * command_parser.h
 */
#ifndef INC_COMMAND_PARSER_H_
#define INC_COMMAND_PARSER_H_

#include <stdint.h>

typedef enum {
    CMD_IDLE,
    CMD_EXCLAMATION,
    CMD_R,
    CMD_O,
    CMD_S,
    CMD_T,
    CMD_K
} CommandParserState;

void command_parser_init(void);
void command_parser_fsm(uint8_t received_char);

#endif /* INC_COMMAND_PARSER_H_ */
