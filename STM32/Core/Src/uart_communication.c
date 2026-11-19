/*
 * uart_communication.c
 */
#include "uart_communication.h"
#include "command_parser.h"
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "software_timer.h"
#include "global.h"

static UARTCommunicationState state = UART_WAIT;

uint32_t ADC_value = 0;

static void send_adc_response(void)
{
    char response[20];

    snprintf(response, sizeof(response), "!ADC=%lu#\r",
             (unsigned long)ADC_value);

    HAL_UART_Transmit(&huart2, (uint8_t *)response,
                      (uint16_t)strlen(response), 1000);
}

void uart_communication_init(void)
{
    state = UART_WAIT;
}

void uart_communication_fsm(void)
{
    switch (state) {
        case UART_WAIT:
            if (isRST) {
                HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin);
                isRST = 0;
                state = UART_IDLE;
            }
            break;

        case UART_IDLE:
            state = UART_SEND_RESPONSE;
            break;

        case UART_SEND_RESPONSE:
            /* Sample ADC once and retain this value for retransmissions. */
            ADC_value = HAL_ADC_GetValue(&hadc1);
            send_adc_response();
            setTimer(3000);
            state = UART_END;
            break;

        case UART_END:
            if (isOK) {
                state = UART_FINAL;
            } else if (timer_flag == 1) {
                /* Resend the saved ADC_value; do not sample ADC again. */
                send_adc_response();
                setTimer(3000);
            }
            break;

        case UART_FINAL:
            {
                char response[] = "END RST\r\n";
                HAL_UART_Transmit(&huart2, (uint8_t *)response,
                                  (uint16_t)strlen(response), 1000);
            }
            state = UART_WAIT;
            isOK = 0;
            break;

        default:
            state = UART_WAIT;
            break;
    }
}
