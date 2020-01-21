#include "L138_LCDK_aic3106_init.h"
#include "evmomapl138_gpio.h"
#include <stdint.h>
#include <math.h>
#include "L138_LCDK_switch_led.h"

int bool1;
int bool2;
int bool3;
int bool4;

int led_err_tim;
int led_err_state;

int tim;

int check_error(){
	if( (bool1 + bool2 + bool3 + bool4) > 1 ){
		return 1;
	}
	else{
		return 0;
	}
}

interrupt void interrupt4(void) // interrupt service routine
{
	int16_t left_sample = input_right_sample();


	if(check_error() == 1){
		output_right_sample(0);

		if(led_err_tim == 4000){
			led_err_tim = 0;

			if(led_err_state == 0){
				LCDK_LED_on(4);
				LCDK_LED_on(5);
				LCDK_LED_on(6);
				LCDK_LED_on(7);
				led_err_state = 1;
			}
			else{
				LCDK_LED_off(4);
				LCDK_LED_off(5);
				LCDK_LED_off(6);
				LCDK_LED_off(7);
				led_err_state = 0;
			}

		}

		led_err_tim++;


	}
	else{

		if(bool2 == 1){
			if(tim == 8000){
				LCDK_LED_on(4);
				LCDK_LED_off(5);
				LCDK_LED_off(6);
				LCDK_LED_off(7);

			}
			if(tim == 16000){
				LCDK_LED_off(4);
				LCDK_LED_on(5);
				LCDK_LED_off(6);
				LCDK_LED_off(7);

			}
			if(tim == 24000){
				LCDK_LED_off(4);
				LCDK_LED_off(5);
				LCDK_LED_on(6);
				LCDK_LED_off(7);

			}
			if(tim == 32000){
				LCDK_LED_off(4);
				LCDK_LED_off(5);
				LCDK_LED_off(6);
				LCDK_LED_on(7);
				tim = 0;

			}


		}

		LCDK_LED_off(4);
		LCDK_LED_off(5);
		LCDK_LED_off(6);
		LCDK_LED_off(7);
		led_err_state = 0;

		if(bool2 == 1){

		}

	}

	if(bool1 == 1)
		output_right_sample(left_sample);
	else
		output_right_sample(0);

	return;
}

int main(void)
{
	bool1 = 0;
	bool2 = 0;
	bool3 = 0;
	bool4 = 0;

	tim = 0;

    led_err_state = 0;
    led_err_tim = 0;

	L138_initialise_intr(FS_8000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);
	LCDK_LED_init();

	while(1);

}
