#include "led_handler.h"

led_error_codes_t turn_on_led(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

    if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != GPIO_PIN_SET)
        return FAILED_TO_UPDATE_LED;

    return LED_OK;
}

led_error_codes_t turn_off_led(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_RESET);

    if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) != GPIO_PIN_RESET)
        return FAILED_TO_UPDATE_LED;

    return LED_OK;

}

led_error_codes_t toggle_led(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    GPIO_PinState _initialState = HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);

    HAL_GPIO_TogglePin(GPIOx, GPIO_Pin);

    if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == _initialState)
        return FAILED_TO_UPDATE_LED;

    return LED_OK;
}
