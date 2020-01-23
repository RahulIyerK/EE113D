#include "L138_LCDK_aic3106_init.h"
#include "evmomapl138_gpio.h"
#include <stdint.h>
#include <math.h>
#include "L138_LCDK_switch_led.h"

#define SAMPLING_RATE FS_8000_HZ
#define LED_ERR_TICKS (0.5 * SAMPLING_RATE)//(0.5/(1/SAMPLING_RATE))
#define RECORDING_TICKS SAMPLING_RATE //(1/(1/SAMPLING_RATE))

uint8_t state;

#define s_start 0
#define s_error 1
#define s_record 2
#define s_wait 3
#define s_slow 4
#define s_speed 5
#define s_reverb 6
#define s_playback 7
#define s_prerecord 8

#define delay_ms 70

#define REVERB_TICKS ((70*SAMPLING_RATE)/1000)

int led_err_tim;
int led_err_toggle;

int recording_tim;
int16_t recording_dat[RECORDING_TICKS];

int16_t slow_dat[RECORDING_TICKS * 3 / 2];

int16_t fast_dat[RECORDING_TICKS * 3 / 4];

int16_t* playback_arr;

int prerecord_tim;

int play_ticks;

int bool1;
int bool2;
int bool3;
int bool4;

int playback_tim;

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

					if(led_err_toggle == 0){
						all_led_on();
						led_err_toggle = 1;
					}
					else{
						all_led_off();
						led_err_toggle = 0;
					}

				}

				led_err_tim++;
		break;

	}

	case s_prerecord:{

		if(prerecord_tim < 8000){
			LCDK_LED_on(4);
			LCDK_LED_off(5);
			LCDK_LED_off(6);
			LCDK_LED_off(7);

		}
		else if(prerecord_tim < 16000){
			LCDK_LED_off(4);
			LCDK_LED_on(5);
			LCDK_LED_off(6);
			LCDK_LED_off(7);

		}
		else if(prerecord_tim < 24000){
			LCDK_LED_off(4);
			LCDK_LED_off(5);
			LCDK_LED_on(6);
			LCDK_LED_off(7);

		}
		else if(prerecord_tim == 24000){
			state = s_record;

		}
		prerecord_tim++;
		output_right_sample(0);
		break;
	}

	case s_record:{
		output_right_sample(0);

		LCDK_LED_off(4);
		LCDK_LED_off(5);
		LCDK_LED_off(6);
		LCDK_LED_on(7);


        if(recording_tim >= RECORDING_TICKS){
        	all_led_off();
            state = s_wait; // *?* right state?
            break;
        }

        recording_dat[recording_tim] = left_sample;
        recording_tim++;
        break;
	}



    case s_playback:{
        if(playback_tim >= play_ticks){
            playback_tim = 0;
            if(bool1 + bool2 + bool3 + bool4 == 0){
                state = s_start;
        		output_right_sample(0);
                break;
            }
        }
        output_right_sample(10 * playback_arr[playback_tim]);
        playback_tim++;
        break;
    }

    default:{
		output_right_sample(0);
    	break;
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

	prerecord_tim = 0;

	state = s_start;

	led_err_tim = 0;
	led_err_toggle = 0;

	recording_tim = 0;

    playback_tim = 0;

	L138_initialise_intr(SAMPLING_RATE,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_MIC_INPUT);
	LCDK_LED_init();

	while(1){
		if(check_error() && state != s_error ){
			set_state_err();
		}

		switch(state){
        case s_error: {
            if(check_error() == 0){
            	all_led_off();
                state = s_start;
            }
            break;
        }
		case s_start: {
			if(bool1 == 1){
				all_led_off();
				state = s_prerecord;
				prerecord_tim = 0;
				recording_tim = 0;
				break;
			}
			break;
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
			all_led_off();
//			if(bool1 == 1){
//				all_led_off();
//				state = s_record;
//				prerecord_tim = 0;
//				recording_tim = 0;
//				break;
//			}
			if(bool2 == 1){
				LCDK_LED_on(5);
				state = s_reverb;
				break;
			}

			if(bool3 == 1){
				LCDK_LED_on(6);
				state = s_speed;
				break;
			}

			if(bool4 == 1){
				LCDK_LED_on(7);
				state = s_slow;
				break;
			}
			break;
		}

	    case s_reverb:{
	        int i = REVERB_TICKS;
	        for(; i < RECORDING_TICKS; i++){
	        	recording_dat[i] = recording_dat[i] + (int) ((2.0/3) * (float)recording_dat[i - REVERB_TICKS]);
	        }
	        state = s_playback;
	        playback_tim = 0;
	        playback_arr = recording_dat;
	        play_ticks = RECORDING_TICKS;
	        break;
	    }

	    case s_slow:{
	    	int i = 0;
	    	for(;i < 3* (RECORDING_TICKS/2); i++){
//	    		if(2*i%3 == 0){
//	    			slow_dat[i] = recording_dat[2/3*i];
//	    		}
//
////	    		if(2*i%3 == 2){
////	    			slow_dat[i] = recording_dat[(int) (2.0/3*i)] + (int) 2/3 * (recording_dat[(int) (2.0/3*i) + 1] - recording_dat[(int) (2.0/3*i)]);
////	    		}
////	    		if(2*i%3 == 1){
////	    			slow_dat[i] = recording_dat[(int) (2.0/3*i)] + (int) 1/3 * (recording_dat[(int) (2.0/3*i) + 1] - recording_dat[(int) (2.0/3*i)]);
////	    		}
//	    		else
//	    		{
	    			float alpha = (float)((2*i)%3);
	    			slow_dat[i] = recording_dat[(int) (2.0/3*i)] + (int) (alpha/3) * (recording_dat[(int) (2.0/3*i) + 1] - recording_dat[(int) (2.0/3*i)]);

//	    		}
	    	}

		playback_tim = 0;
		play_ticks = 3* (RECORDING_TICKS/2);
		playback_arr = slow_dat;
		state = s_playback;
		break;
	    }

	    case s_speed:{
	    	int i = 0;
	    	for(;i < 3* (RECORDING_TICKS/4); i++){
//	    		if(2*i%3 == 0){
//	    			slow_dat[i] = recording_dat[2/3*i];
//	    		}
//
////	    		if(2*i%3 == 2){
////	    			slow_dat[i] = recording_dat[(int) (2.0/3*i)] + (int) 2/3 * (recording_dat[(int) (2.0/3*i) + 1] - recording_dat[(int) (2.0/3*i)]);
////	    		}
////	    		if(2*i%3 == 1){
////	    			slow_dat[i] = recording_dat[(int) (2.0/3*i)] + (int) 1/3 * (recording_dat[(int) (2.0/3*i) + 1] - recording_dat[(int) (2.0/3*i)]);
////	    		}
//	    		else
//	    		{
	    			float alpha = (float)((4*i)%3);
	    			fast_dat[i] = recording_dat[(int) (4.0/3*i)] + (int) (alpha/3) * (recording_dat[(int) (4.0/3*i) + 1] - recording_dat[(int) (4.0/3*i)]);

//	    		}
	    	}

		playback_tim = 0;
		play_ticks = 3* (RECORDING_TICKS/4);
		playback_arr = fast_dat;
		state = s_playback;
		break;
	    	    }


		}
	}

}
