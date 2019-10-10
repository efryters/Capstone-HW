/*
 * hw_i2c.c
 *
 *  Created on: Nov 6, 2019
 *      Author: eric
 */

/* Includes ------------------------------------------------------------------*/
#include "hw.h"
#include "utilities.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static I2C_HandleTypeDef hi2c1;
/* Private function prototypes -----------------------------------------------*/

/*!
* @brief Initializes the I2C object and MCU peripheral
*
* @param [IN] none
*/
void HW_I2C_Init( void )
{

	  hi2c1.Instance = I2C1;
	  hi2c1.Init.Timing = 0x00707CBB;
	  hi2c1.Init.OwnAddress1 = 0;
	  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	  hi2c1.Init.OwnAddress2 = 0;
	  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
	  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /** Configure Analogue filter
	  */
	  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  /** Configure Digital filter
	  */
	  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
	  {
	    Error_Handler();
	  }

	  HW_I2C_IoInit();

}

/*!
* @brief De-initializes the I2C object and MCU peripheral
*
* @param [IN] none
*/
void HW_I2C_DeInit( void )
{

}

/*!
* @brief Initializes the I2C IOs
*
* @param [IN] none
*/
void HW_I2C_IoInit(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (hi2c1.Instance == I2C1)
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();

		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

		HW_GPIO_Init(I2C_PIN_SCL_PORT, I2C_PIN_SCL, &GPIO_InitStruct);
		HW_GPIO_Init(I2C_PIN_SDA_PORT, I2C_PIN_SDA, &GPIO_InitStruct);

		__HAL_RCC_I2C1_CLK_ENABLE();

	}

}

/*!
* @brief De-initializes the I2C IOs
*
* @param [IN] none
*/
void HW_I2C_IoDeInit( void )
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	if (hi2c1.Instance == I2C1)
	{
		__HAL_RCC_I2C1_CLK_DISABLE();

		HAL_GPIO_DeInit(I2C_PIN_SCL_PORT, I2C_PIN_SCL);
		HAL_GPIO_DeInit(I2C_PIN_SDA_PORT, I2C_PIN_SDA);

	}

}

/*!
* @brief Sends outData and receives inData
*
* @param [IN] outData Byte to be sent
* @retval inData      Received byte.
*/
uint16_t HW_I2C_InOut( uint16_t outData )
{

	return 0;
}
