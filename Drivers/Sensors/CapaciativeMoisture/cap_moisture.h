/*
 * cap_moist.h
 *
 *  Created on: Oct 14, 2019
 *      Author: eric
 */

#ifndef CAP_MOIST_H_
#define CAP_MOIST_H_

/*
 * Extra Includes
 */
#include "stdbool.h"

/*
 * PIN DEFINES
 */

/*
 * Shared data structures
 */
typedef struct sCapMoistData {

} sMoistSenseData;

/*
 * Exported functions
 */
void cap_moist_init(ADC_HandleTypeDef *adcHW);
uint16_t cap_moist_read();


#endif /* CAP_MOIST_H_ */
