/*
 * light_sensor.h
 *
 *  Created on: Oct. 16, 2019
 *      Author: seans
 */

#ifndef DRIVERS_SENSORS_LIGHTSENSOR_LIGHT_SENSOR_H_
#define DRIVERS_SENSORS_LIGHTSENSOR_LIGHT_SENSOR_H_


extern I2C_HandleTypeDef hi2c1;
void MX_I2C1_Init(void);
uint16_t light_Read(void);
uint16_t light_Read_2(void);
#endif /* DRIVERS_SENSORS_LIGHTSENSOR_LIGHT_SENSOR_H_ */
