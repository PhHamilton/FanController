#include "config_handler.h"
#include "main.h"
#include "timer.h"
#include "led_handler.h"
#include "uart_handler.h"
#include "mode_handler.h"
#include "settings.h"

#define LED_ON_TIME 250
#define UINT16_ERROR 65535

void handle_leds(void);
void handle_uart_message(void);
void handle_config_message(char* msg, uint8_t msg_size);
uint16_t fetch_parameter(char* msg, uint8_t msg_size, uint16_t start_index);

void handle_config_state()
{
    /*
     * Flash LEDs
     */
    handle_leds();
    handle_uart_message();
}

void handle_leds(void)
{
    if(!timer_enabled(CONFIG_LED_TIMER))
    {
        enable_timer(CONFIG_LED_TIMER);
        configure_timer(CONFIG_LED_TIMER, LED_ON_TIME);
        turn_on_led(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
        turn_off_led(LED_RED_GPIO_Port, LED_RED_Pin);
    }

    if(timer_ready(CONFIG_LED_TIMER))
    {
        toggle_led(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
        toggle_led(LED_RED_GPIO_Port, LED_RED_Pin);
    }
}

void handle_uart_message(void)
{
    uart_status_codes_t code = get_uart_status();
    if(code == UART_MSG_AVAILABLE)
    {
        char msg[UART_RX_BUF_SIZE] = {0};

        get_uart_message(msg, UART_RX_BUF_SIZE);
        controller_modes_t mode = (controller_modes_t)(msg[0] - '0');
        switch(mode)
        {
            case CONTROLLER_MODE_OFF:
            {
                set_controller_mode(mode);
                turn_off_led(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
                turn_off_led(LED_RED_GPIO_Port, LED_RED_Pin);
            }
            break;
            case CONTROLLER_MODE_MEASURING:
            {
                set_controller_mode(mode);
            }
            break;
            case CONTROLLER_MODE_CONFIG:
            {
                handle_config_message(msg, UART_RX_BUF_SIZE);
            }
            break;
            default:
            {
            	//Unknown type
            }
            break;
        }
    }
}

/*
 * Config Message:
 * 
 * 2, MP/MR(uint16_t)
 * 2, MP, (uint16_t) R, (uint16_t) L, (uint16_t) J
 * 2, MR, (uint16_t) V, (uint16_t) C
 */
void handle_config_message(char* msg, uint8_t msg_size)
{
    char update_type = msg[3];
    switch(update_type)
    {
        case 'P':
        {
            motor_parameters_t motor_parameters;
            motor_parameters.R = fetch_parameter(msg, msg_size, 5);
            update_motor_parameters(&motor_parameters);

        }
        break;
        case 'R':
        {

        }
        break;
        default:
        {
            // Unknown type
        }
        break;
    }
}

uint16_t fetch_parameter(char* msg, uint8_t msg_size, uint16_t start_index)
{
    uint16_t val = 0;
    for(uint8_t i = start_index; msg[i] != ',' && msg[i] != '\0'; i++)
    {
        uint8_t num = msg[i] - '0';

        if(num > 9)
        {
            return UINT16_ERROR;
        }

        val = 10 * val + num;
    }

    return val;
}
