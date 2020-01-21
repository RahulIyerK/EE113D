#include "L138_LCDK_aic3106_init.h"
#include "evmomapl138_gpio.h"
#include <stdint.h>
#include <math.h>
#include "L138_LCDK_switch_led.h"

#define SAMPLING_RATE FS_8000_HZ
#define LED_ERR_TICKS (0.5/(1/SAMPLING_RATE))
#define RECORDING_TICKS (1/(1/SAMPLING_RATE))

uint8_t state;

#define s_start 0
#define s_error 1
#define s_record 2
#define s_wait 3
#define s_slow 4
#define s_speed 5
#define s_reverb 6
#define s_playback 7

int led_err_tim;
int led_err_toggle;

int recording_tim;


int bool1;
int bool2;
int bool3;
int bool4;


int check_error(){
	if( (bool1 + bool2 + bool3 + bool4) > 1 ){
		return 1;
	}
	else{
		return 0;
	}
}

void all_led_off(){
	LCDK_LED_off(4);
	LCDK_LED_off(5);
	LCDK_LED_off(6);
	LCDK_LED_off(7);
}

void all_led_on(){
	LCDK_LED_on(4);
	LCDK_LED_on(5);
	LCDK_LED_on(6);
	LCDK_LED_on(7);
}

interrupt void interrupt4(void) // interrupt service routine
{
	int16_t left_sample = input_right_sample();

	switch(state){
	case s_error:{
		output_right_sample(0);
		if(led_err_tim == LED_ERR_TICKS){
					led_err_tim = 0;

					if(led_err_state == 0){
						all_led_on();
						led_err_state = 1;
					}
					else{
						all_led_off();
						led_err_state = 0;
					}

				}

				led_err_tim++;
		break;

	}

	case s_record:{

	}

	}

}

void set_state_err(){
	led_err_tim = 0;
	led_err_toggle = 0;
	state = s_error;
}

int main(void)
{
	bool1 = 0;
	bool2 = 0;
	bool3 = 0;
	bool4 = 0;

	state = 0;

	led_err_tim = 0;
	led_err_toggle = 0;

	recording_tim = 0;


	L138_initialise_intr(SAMPLING_RATE,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);
	LCDK_LED_init();

	while(1){
		if(check_error()){
			set_state_err();
			continue;
		}

		switch(state){
		case s_start: {
			if(bool1 == 1){
				all_led_off();
				state = s_record;
				recording_tim = 0;
				break;
			}
		}
		case s_record:{
			if(recording_tim < RECORDING_TICKS){
				state = s_record;
			}
			else{
				state = s_wait;
			}
			break;
		}

		case s_wait:{
			if(bool1 == 1){
				all_led_off();
				state = s_record;
				recording_tim = 0;
				break;
			}
			if(bool2 == 1){
				all_led_off();
				LCDK_LED_on(5);
				state = s_reverb;
				break;
			}

			if(bool3 == 1){
				all_led_off();
				LCDK_LED_on(6);
				state = s_speed;
				break;
			}

			if(bool4 == 1){
				all_led_off();
				LCDK_LED_on(7);
				state = s_slow;
				break;
			}
			break;
		}


		}
	}

}
