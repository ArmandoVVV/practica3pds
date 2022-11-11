/*
 * config.h
 *
 * 		\brief
 * 		This is a source file for the configuration for the practice 1.
 * 		Device driver for Kinetis K64.
 * 		it contains all the definitions of the macros.
 *
 *  	Created on: Sep 20, 2022
 *		Author: Laura García
 */

#ifndef CONFIG_H_
#define CONFIG_H_

typedef enum{FALSE, TRUE} bool_t;

typedef enum{DISABLE,
			 ENABLE
}device_status_t;

//GPIO
#define SW2_GPIO 		  (GPIOC)  //SWITCHES
#define SW3_GPIO		  (GPIOA)

//PORTS
#define SW2_PORT	      (PORTC)  //SWITCHES
#define SW3_PORT		  (PORTA)

//PIN
#define SW2_PIN			(6u)   //SWITCHES
#define SW3_PIN			(4u)

// MASKS
#define SW2_MASK	  	  (1 << SW2_PIN)		 // SWITCHES
#define SW3_MASK		  (1 << SW3_PIN)

#define SIZEOF_VAR( var ) ((size_t)(&(var)+1)-(size_t)(&(var)))

#endif /* CONFIG_H_ */
