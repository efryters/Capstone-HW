#include "light_sensor.h"

void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */
	 RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
	 PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
	  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
	  {
	    Error_Handler();
	  }
	  hi2c1.Instance = I2C1;
	  hi2c1.Init.Timing = 0x00000708;
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
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

uint16_t light_Read(void)
{	unsigned char buffer[5];
	uint16_t rawL = 0;
	static const uint8_t light_Addr = 0x4A << 1;
		  buffer[0]=0x03;
		  HAL_I2C_Master_Transmit(&hi2c1,light_Addr,buffer,1,100);
		  HAL_Delay(20);
		  HAL_I2C_Master_Receive(&hi2c1,light_Addr,buffer,2,100);

		  //receive 2 bytes, store into buffer[0] and buffer[1]
		 	  //buffer[0] : MSB data
		 	  //buffer[1] : LSB data
		  rawL = buffer[0]<<4 | buffer[1]>>4;
		  return rawL;
}
