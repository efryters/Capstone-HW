/*
 * hw_i2c.h
 *
 *  Created on: Nov 6, 2019
 *      Author: eric
 */

#ifndef INC_HW_I2C_H_
#define INC_HW_I2C_H_

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*!
* @brief Initializes the SPI object and MCU peripheral
*
* @param [IN] none
*/
void HW_I2C_Init( void );

/*!
* @brief De-initializes the SPI object and MCU peripheral
*
* @param [IN] none
*/
void HW_I2C_DeInit( void );

/*!
* @brief Initializes the SPI IOs
*
* @param [IN] none
*/
void HW_I2C_IoInit( void );

/*!
* @brief De-initializes the SPI IOs
*
* @param [IN] none
*/
void HW_I2C_IoDeInit( void );

/*!
* @brief Sends outData and receives inData
*
* @param [IN] outData Byte to be sent
* @retval inData      Received byte.
*/
uint16_t HW_I2C_InOut( uint16_t outData );

#endif /* INC_HW_I2C_H_ */
