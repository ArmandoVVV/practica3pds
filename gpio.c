// gpio.c
/**
*	\file
*	\brief
*		This is the source file for the GPIO device driver for Kinetis K64.
*		It contains all the implementation for configuration functions and runtime functions.
*		i.e., this is the application programming interface (API) for the GPIO peripheral.
*	\date	28/09/2022
*	\
*	    Author: Laura García
*
*/
#include <gpio.h>
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "config.h"
#include "pit.h"

volatile static gpio_interrupt_flags_t g_intr_status_flag = {0};

static void (*gpio_E_callback)(uint32_t flags) = 0;
static void (*gpio_D_callback)(uint32_t flags) = 0;
static void (*gpio_C_callback)(uint32_t flags) = 0;
static void (*gpio_B_callback)(uint32_t flags) = 0;
static void (*gpio_A_callback)(uint32_t flags) = 0;


void GPIO_callback_init(gpio_name_t gpio, void (*handler)(uint32_t flags))
{
	switch(gpio){
		case GPIO_A:
			gpio_A_callback = handler;
			break;

		case GPIO_B:
			gpio_B_callback = handler;
			break;

		case GPIO_C:
			gpio_C_callback = handler;
			break;

		case GPIO_D:
			gpio_D_callback = handler;
			break;

		default: // gpio == GPIO_E
			gpio_E_callback = handler;
	}
}


void PORTC_IRQHandler(void)
{

	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOC);

	PIT_stop();

	if(gpio_C_callback)
	{
		gpio_C_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOC, irq_status);


}

void PORTB_IRQHandler(void)
{
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOB);

	if(gpio_B_callback)
	{
		gpio_B_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOB, irq_status);
}


void PORTA_IRQHandler(void)
{
	uint32_t irq_status = 0;

	irq_status = GPIO_PortGetInterruptFlags(GPIOA);

	PIT_start();

	if(gpio_A_callback)
	{
		gpio_A_callback(irq_status);
	}

	GPIO_PortClearInterruptFlags(GPIOA, irq_status);
}

void GPIO_init(void)
{
	gpio_pin_config_t gpio_input_config = {
			        kGPIO_DigitalInput,
			        0,
			    };

//	gpio_pin_config_t gpio_output_config = {
//			        kGPIO_DigitalOutput,
//			        1,
//			    };

	const port_pin_config_t button_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterEnable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */

		  };


	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortC);


	//SWITCHES
	GPIO_PinInit(SW2_GPIO, SW2_PIN, &gpio_input_config);
	PORT_SetPinConfig(SW2_PORT, SW2_PIN, &button_config);
	PORT_SetPinInterruptConfig(SW2_PORT, SW2_PIN, kPORT_InterruptFallingEdge);

	GPIO_PinInit(SW3_GPIO, SW3_PIN, &gpio_input_config);
	PORT_SetPinConfig(SW3_PORT, SW3_PIN, &button_config);
	PORT_SetPinInterruptConfig(SW3_PORT, SW3_PIN, kPORT_InterruptFallingEdge);
}


void GPIO_clear_irq_status(gpio_name_t gpio)
{
	switch(gpio){
		case GPIO_A:
			g_intr_status_flag.flag_port_a = false;
			break;
		case GPIO_B:
			g_intr_status_flag.flag_port_b = false;
			break;
		case GPIO_C:
			g_intr_status_flag.flag_port_c = false;
			break;
		case GPIO_D:
			g_intr_status_flag.flag_port_d = false;
			break;
		default: // gpio == GPIO_E
			g_intr_status_flag.flag_port_e = false;
	}
}

uint8_t GPIO_get_irq_status(gpio_name_t gpio)
{
	uint8_t status = 0;

	switch(gpio){
		case GPIO_A:
			status = g_intr_status_flag.flag_port_a;
			break;

		case GPIO_B:
			status = g_intr_status_flag.flag_port_b;
			break;

		case GPIO_C:
			status = g_intr_status_flag.flag_port_c;
			break;

		case GPIO_D:
			status = g_intr_status_flag.flag_port_d;
			break;

		default: // gpio == GPIO_E
			status = g_intr_status_flag.flag_port_e;
	}
	return(status);
}
