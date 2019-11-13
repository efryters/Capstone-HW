/*
 * temperature_sensor.h
 *
 *  Created on: Nov 13, 2019
 *      Author: eric
 */

#ifndef DRIVERS_SENSORS_TEMPERATURESENSOR_TEMPERATURE_SENSOR_H_
#define DRIVERS_SENSORS_TEMPERATURESENSOR_TEMPERATURE_SENSOR_H_


/* Exported Functions */


void temp_init();
uint16_t temp_read();
void temp_deinit();



#endif /* DRIVERS_SENSORS_TEMPERATURESENSOR_TEMPERATURE_SENSOR_H_ */
