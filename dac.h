/*
 * dac.h
 *
 * 		\brief
 *				This source file helps us to set the DAC values to create
 *				different signals, and start the DAC.
 *  	Created on: Sep 20, 2022
 *		Author: Laura García
 */

#ifndef DAC_H_
#define DAC_H_

#include "stdint.h"

void DAC_init(void);
void DAC_noSignal(void);
void DAC_setValue(uint16_t sin_value);

#endif /* DAC_H_ */
