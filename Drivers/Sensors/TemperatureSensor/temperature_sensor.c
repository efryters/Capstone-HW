/*
 * temperature_sensor.c
 *
 *  Created on: Nov 13, 2019
 *      Author: eric
 */

#include "stdint.h"
#include "math.h"

#include "ow/ow.h"
#include "ow/devices/ow_device_ds18x20.h"
#include "ow/devices/scan_devices.h"

/* Create new 1-Wire instance */
ow_t ow;
ow_rom_t rom_ids[20];
size_t rom_found;

void temp_init()
{
	/* Sensor init from example application */

    ow_init(&ow, NULL);                         /* Initialize 1-Wire library and set user argument to NULL */

    do {
        if (scan_onewire_devices(&ow, rom_ids, OW_ARRAYSIZE(rom_ids), &rom_found) == owOK) {
            printf("Devices scanned, found %d devices!\r\n", (int)rom_found);
        } else {
            printf("Device scan error\r\n");
        }
        if (rom_found == 0) {
            HAL_Delay(1000);
        }
    } while (rom_found == 0);

}

void temp_deinit()
{

}

uint16_t temp_read()
{
    float avg_temp;
    float temp;
    size_t avg_temp_count;

	/* Temperature read logic from example application */
    if (rom_found) {

		printf("Start temperature conversion\r\n");
		ow_ds18x20_start(&ow, NULL);        /* Start conversion on all devices, use protected API */
		HAL_Delay(1000);                      /* Release thread for 1 second */

		/* Read temperature on all devices */
		avg_temp = 0;
		avg_temp_count = 0;
		for (size_t i = 0; i < rom_found; i++) {
			if (ow_ds18x20_is_b(&ow, &rom_ids[i])) {

				uint8_t resolution = ow_ds18x20_get_resolution(&ow, &rom_ids[i]);
				if (ow_ds18x20_read(&ow, &rom_ids[i], &temp)) {
					printf("Sensor %02u temperature is %d.%d degrees (%u bits resolution)\r\n",
						(unsigned)i, (int)temp, (int)((temp * 1000.0f) - (((int)temp) * 1000)), (unsigned)resolution);

					avg_temp += temp;
					avg_temp_count++;
				} else {
					printf("Could not read temperature on sensor %u\r\n", (unsigned)i);
				}
			}
		}
		if (avg_temp_count > 0) {
			avg_temp = avg_temp / avg_temp_count;
		}
		printf("Average temperature: %d.%d degrees\r\n", (int)avg_temp, (int)((avg_temp * 100.0f) - ((int)avg_temp) * 100));

    }


    /* Data conversion from float to uint16_t */
    uint16_t u16Temperature = 0;
    temp = (temp + 55.0) * 100;

    u16Temperature = (uint16_t) roundf(temp);



	return u16Temperature;
}

