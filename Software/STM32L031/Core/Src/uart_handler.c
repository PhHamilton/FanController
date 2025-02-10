#include "uart_handler.h"
#include <stm32l0xx_hal.h>
#include <stm32l0xx_it.h>
#include <string.h>


#define N_TERMINATION_CHARACTERS 2

extern UART_HandleTypeDef huart2;

volatile uart_status_codes_t uart_status = UART_FINISHED;
volatile uint8_t message_counter = 0;
uint8_t rx_data[UART_RX_BUF_SIZE] = {0};

uint8_t rx_byte, rx_index;

void init_uart(void)
{
    rx_byte = 0;
    rx_index = 0;
    HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
}

uart_status_codes_t send_uart_msg(char* msg, uint16_t msg_size)
{
    uart_status = UART_BUSY;

    char msg_buf[msg_size + N_TERMINATION_CHARACTERS];

    for(uint8_t i = 0; i < msg_size; i++)
    {
        msg_buf[i] = msg[i];
    }

    msg_buf[msg_size]   = '\r';
    msg_buf[msg_size+1] = '\n';

    if(HAL_UART_Transmit(&huart2, (uint8_t*)msg_buf, msg_size + N_TERMINATION_CHARACTERS, 100) != HAL_OK)
    {
        uart_status = UART_ERROR;
    }

    uart_status = UART_FINISHED;

    return uart_status;
}

uart_status_codes_t get_uart_status(void)
{
    return uart_status;
}

uart_status_codes_t get_uart_message(char* buffer, uint8_t buf_size)
{
    if(uart_status == UART_MSG_AVAILABLE)
    {
        uint8_t i;
        for(i = 0; i < buf_size && rx_data[i] != '\0'; i++)
        {
            buffer[i] = rx_data[i];
        }
        buffer[i] = '\0';

        for(uint8_t i = 0; i < UART_RX_BUF_SIZE; i++)
        {
            rx_data[i] = '\0';
        }

        uart_status = UART_FINISHED;
        return UART_FINISHED;
    }
    else
    {
        return UART_ERROR;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART2)
    {
        if (rx_byte == '\n')
        {
            rx_data[rx_index] = '\0';
            rx_index = 0;
            uart_status = UART_MSG_AVAILABLE;
        }
        else
        {
            if (rx_byte != '\r')
            {
                if (rx_index < UART_RX_BUF_SIZE - 1)
                {
                    rx_data[rx_index] = rx_byte;
                    rx_index++;
                }
            }
        }
        HAL_UART_Receive_IT(&huart2, &rx_byte, 1);
    }
}


