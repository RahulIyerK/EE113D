//#include "L138_LCDK_aic3106_init.h"
//#include "evmomapl138_gpio.h"
//#include <stdint.h>
//#include <math.h>
//#include "L138_LCDK_switch_led.h"
//
//// bilinear coefficients
//
//// first order bilinear difference equation:
//
//// y[n] = B0 x[n] + B1 x[n-1] - A1 y[n-1]
//// where B0, B1, A1 are normalized coefficients:
//
////en.wikipedia.org/wiki/Bilinear_transform
//
//// these are the first order filter coefficients for 1kHz filter
//// we use matlab to calculate these values
////#define B0 0.0614
////#define B1 0.0614
////#define A1 -0.8771
//
////these are the filter coefficients for 20kHz filter
//#define B0 0.0614
//#define B1 0.0614
//#define A1 -0.8771
//
//float x_n;
//float x_n1;
//float y_n;
//float y_n1;
//
//interrupt void interrupt4(void) // interrupt service routine
//{
//	int16_t left_sample = input_right_sample();
//
//	//measuring the frequency response with our first order filter implemented as a difference equation
//	x_n = (float) left_sample;
//
//	y_n = B0 * x_n + B1 * x_n1 - A1 * y_n1;
//
//	output_right_sample((int16_t)y_n);
//	y_n1 = y_n;
//	x_n1 = x_n;
//
//	//measuring the frequency response of just LCDK alone
//	//we just output whatever we read in
////	output_right_sample(left_sample);
//
//}
//
//
//
//int main(void)
//{
//	x_n = 0.0;
//	x_n1 = 0.0;
//	y_n = 0.0;
//	y_n1 = 0.0;
//
//	L138_initialise_intr(FS_48000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);
//
//	while(1);
//
//}
