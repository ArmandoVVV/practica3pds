/*
 * pit.h
 *
 * 		\brief
 * 		This is the PIT source file for the device driver for Kinetis K64.
 * 		It contains all PIT´s configuration functions and runtime functions.
 *      Created on: Sep 20, 2022
 *      Author: Armando Cabrales
 */

#include "fsl_pit.h"

#ifndef PIT_H_
#define PIT_H_

void PIT_init(void);
void PIT_stop(void);
void PIT_start(void);
void PIT0_IRQHandler(void);
void PIT1_IRQHandler(void);
void PIT_callback_init(pit_chnl_t channel, void (*handler)(uint32_t flags));


#endif /* PIT_H_ */
