/**
 * @file    practica3_pds.c
 * @brief   Application entry point.
 */

#include "config.h"
#include "pit.h"
#include "gpio.h"
#include "dac.h"
#include "notes.h"
#include "nvic.h"

void start_song(void){
	if(get_end_flag() == TRUE){

	}
}

int main(void) {
	GPIO_init();
	DAC_init();

	NVIC_set_basepri_threshold(PRIORITY_8);
	NVIC_EnableIRQ(PIT_CH0_IRQ);
	NVIC_SetPriority(PIT_CH0_IRQ, PRIORITY_3);

	NVIC_EnableIRQ(PORTA_IRQ);
	NVIC_SetPriority(PORTA_IRQ, PRIORITY_3);

	NVIC_EnableIRQ(PORTC_IRQ);
	NVIC_SetPriority(PORTC_IRQ, PRIORITY_3);

	NVIC_global_enable_interrupts;

	PIT_callback_init(kPIT_Chnl_0, sound_note);

	PIT_init();

    while(TRUE) {

    	if(get_end_flag() == TRUE){
    		set_current_note( get_next_partiture_note() );
    		set_sound_index(0);
    		PIT_start();
    		set_end_flag(FALSE);
    	}

    }
    return 0 ;
}
