#include "adc.h"

volatile uint16_t adc_val = 0;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    adc_val = HAL_ADC_GetValue(hadc);
}

HAL_StatusTypeDef start_adc()
{
    return HAL_ADC_Start_IT(&hadc);
}

uint16_t read_adc_value(void)
{
    return adc_val;
}
