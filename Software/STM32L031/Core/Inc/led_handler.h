#ifndef __LED_HANDLER_H__
#define __LED_HANDLER_H__

#include <stm32l0xx_hal.h>
#include <stdint.h>

typedef enum
{
    LED_OK,
    FAILED_TO_UPDATE_LED,
}led_error_codes_t;

led_error_codes_t turn_on_led(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
led_error_codes_t turn_off_led(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
led_error_codes_t toggle_led(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

#endif //__LED_HANDLER_H__
