#ifndef __ADC_H__
#define __ADC_H__

#include <stm32l0xx_hal.h>
#include <stdint.h>

extern ADC_HandleTypeDef hadc;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc);

HAL_StatusTypeDef start_adc(void);
uint16_t read_adc_value(void);

#endif //__ADC_H__
