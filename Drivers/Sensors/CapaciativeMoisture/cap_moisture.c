/*
 * cap_moist.c
 *
 *  Created on: Oct 14, 2019
 *      Author: eric
 */

#include "stm32l0xx_hal.h"
#include "cap_moisture.h"

typedef struct adc_hardware {
	ADC_HandleTypeDef *adcHW;
	ADC_ChannelConfTypeDef adcChanConf;

} adc_device;

adc_device gADC = {0};


void cap_moist_init(ADC_HandleTypeDef *adcHW)
{

	gADC.adcHW = adcHW;
	HAL_ADC_Stop(gADC.adcHW);
	gADC.adcChanConf.Channel = ADC_CHANNEL_1;
	gADC.adcChanConf.Rank = ADC_RANK_CHANNEL_NUMBER;
	if (HAL_ADC_ConfigChannel(gADC.adcHW, &gADC.adcChanConf) != HAL_OK)
	{
		// Error_Handler();
	}

}

void cap_moist_HW_init()
{

}

void cap_moist_deinit()
{

}

uint16_t cap_moist_read()
{

	uint16_t u16Reading = 0;
	uint8_t u8SensorData[2] = {0};
	uint16_t uiMeasurementNumber = 0;

	// Read A1
	HAL_ADC_Start(gADC.adcHW);
	if (HAL_OK == HAL_ADC_PollForConversion(gADC.adcHW, 500))
	{
	  u16Reading = HAL_ADC_GetValue(gADC.adcHW);
	  uiMeasurementNumber++;
	}
	HAL_ADC_Stop(gADC.adcHW);

	u8SensorData[0] = u16Reading & 0x00FF;
	u8SensorData[1] = u16Reading >> 8;

	return u16Reading;

}

void cap_moist_cal(int cal_factor)
{

}

