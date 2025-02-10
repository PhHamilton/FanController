#ifndef __UART_HANDLER_H__
#define __UART_HANDLER_H__

#include <stdint.h>

#define TRANSMISSION_TIMOUT_MS 10
#define UART_RX_BUF_SIZE 255

typedef enum
{
    UART_FINISHED,
    UART_BUSY,
    UART_MSG_AVAILABLE,
    UART_ERROR
}uart_status_codes_t;


void USART1_IRQHandler(void);


void init_uart();
uart_status_codes_t send_uart_msg(char* msg, uint16_t msg_size);
uart_status_codes_t read_uart_msg(void);
uart_status_codes_t get_uart_status(void);
uart_status_codes_t get_uart_message(char* buffer, uint8_t buf_size);
uart_status_codes_t incomming_uart_msg(void);

#endif //__UART_HANDLER_H__
