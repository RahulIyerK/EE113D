//#include <stdio.h>
//#include "L138_LCDK_aic3106_init.h"
//#include "L138_LCDK_switch_led.h"
//#include <math.h>
//
//#include "evmomapl138_gpio.h"
//#include <stdint.h>
//#include <math.h>
//#include <ti/dsplib/dsplib.h>
//
//#define pi 3.1415
//#define N 1024
//float data[1024];
//float inputSignal[1024];
//
//int count = 0;
//
//int sw5 = 0;
//int sw6 = 0;
//int sw7 = 0;
//int sw8 = 0;
//float w[1024];
//
//float alpha = 0.54;
//float beta = 0.46;
//int i;
//
//float f_mel[28];
//float f_fb[28];
//
//int lambda[28];
//
///* Align the tables that we have to use */
//
//// The DATA_ALIGN pragma aligns the symbol in C, or the next symbol declared in C++, to an alignment boundary.
//// The alignment boundary is the maximum of the symbol's default alignment value or the value of the constant in bytes.
//// The constant must be a power of 2. The maximum alignment is 32768.
//// The DATA_ALIGN pragma cannot be used to reduce an object's natural alignment.
//
////The following code will locate mybyte at an even address.
////#pragma DATA_ALIGN(mybyte, 2)
////char mybyte;
//
////The following code will locate mybuffer at an address that is evenly divisible by 1024.
////#pragma DATA_ALIGN(mybuffer, 1024)
////char mybuffer[256];
//#pragma DATA_ALIGN(x_in,8);
//int16_t x_in[2*N];
//
//#pragma DATA_ALIGN(x_sp,8);
//float   x_sp [2*N];
//#pragma DATA_ALIGN(y_sp,8);
//float   y_sp [2*N];
//#pragma DATA_ALIGN(w_sp,8);
//float   w_sp [2*N];
//
//// brev routine called by FFT routine
//unsigned char brev[64] = {
//    0x0, 0x20, 0x10, 0x30, 0x8, 0x28, 0x18, 0x38,
//    0x4, 0x24, 0x14, 0x34, 0xc, 0x2c, 0x1c, 0x3c,
//    0x2, 0x22, 0x12, 0x32, 0xa, 0x2a, 0x1a, 0x3a,
//    0x6, 0x26, 0x16, 0x36, 0xe, 0x2e, 0x1e, 0x3e,
//    0x1, 0x21, 0x11, 0x31, 0x9, 0x29, 0x19, 0x39,
//    0x5, 0x25, 0x15, 0x35, 0xd, 0x2d, 0x1d, 0x3d,
//    0x3, 0x23, 0x13, 0x33, 0xb, 0x2b, 0x1b, 0x3b,
//    0x7, 0x27, 0x17, 0x37, 0xf, 0x2f, 0x1f, 0x3f
//};
//
//// The seperateRealImg function separates the real and imaginary data
//// of the FFT output. This is needed so that the data can be plotted
//// using the CCS graph feature
//float y_real_sp [N];
//float y_imag_sp [N];
//float y_mag [N];
//float y_mag_squared [513];
//
//float H[26][513];
//float mult[513];
//
//float Y[26];
//double X[26];
//
//float MFCC[13];
//
//float samples[40][13];
//
//void HammingWindow()
//{
//	for (i = 0; i < 1024; i++)
//	{
//		w[i] = alpha - (beta*cos((2*pi*i)/(float)(N-1)));
//		inputSignal[i] = data[i]*w[i];
//	}
//}
//
//separateRealImg () {
//    int i, j;
//
//    for (i = 0, j = 0; j < N; i+=2, j++) {
//        y_real_sp[j] = y_sp[i];
//        y_imag_sp[j] = y_sp[i + 1];
//    }
//}
//
//// Function for generating sequence of twiddle factors
//void gen_twiddle_fft_sp (float *w, int n)
//{
//    int i, j, k;
//    double x_t, y_t, theta1, theta2, theta3;
//
//    for (j = 1, k = 0; j <= n >> 2; j = j << 2)
//    {
//        for (i = 0; i < n >> 2; i += j)
//        {
//            theta1 = 2 * pi * i / n;
//            x_t = cos (theta1);
//            y_t = sin (theta1);
//            w[k] = (float) x_t;
//            w[k + 1] = (float) y_t;
//
//            theta2 = 4 * pi * i / n;
//            x_t = cos (theta2);
//            y_t = sin (theta2);
//            w[k + 2] = (float) x_t;
//            w[k + 3] = (float) y_t;
//
//            theta3 = 6 * pi * i / n;
//            x_t = cos (theta3);
//            y_t = sin (theta3);
//            w[k + 4] = (float) x_t;
//            w[k + 5] = (float) y_t;
//            k += 6;
//        }
//    }
//}
//
//interrupt void interrupt4(void)  // interrupt service routine
//{
//	int16_t samp = input_left_sample();
//
//
//	if (sw5 == 1 && sw6 == 0 && sw7 == 0 && sw8 == 0) {
//
//		if (count < 1024) {
//			data[count] = samp;
//
//			count++;
//		}
//
//	} else if (sw5 == 0 && sw6 == 0 && sw7 == 0 && sw8 == 0) {
//		count = 0;
//	}
//
//	output_left_sample(0);
//
//	return;
//}
//
//void filterBank() {
//	int i;
//
//	f_fb[0] = 250;
//	f_fb[27] = 8000;
//
//	f_mel[0] = 2595 * log10(1+(f_fb[0]/700.0));
//	f_mel[27] = 2595 * log10(1+(f_fb[27]/700.0));
//
//	float inc = (f_mel[27] - f_mel[0]) / 27.0;
//
//	for (i = 1; i < 27; i++) {
//		f_mel[i] = f_mel[i-1] + inc;
//		f_fb[i] = (pow(10, (f_mel[i]/2595.0))-1) * 700;
//	}
//
//	int q;
//	for (q=0; q<28; q++) {
//		lambda[q] = 512 * f_fb[q] / 8000;
//	}
//
//	int j, k;
//
//
//	for (j = 0; j < 26; j++) { //counting triangles 0...25
//		for (k = 0; k < 513; k++) { //counting points in DFT 0...512
//			if (k < lambda[0] || k > lambda[27]) {
//				H[j][k] = 0;
//			} else if (k < lambda[j]) {
//				H[j][k] = 0;
//			} else if (k >= lambda[j] && k <= lambda[j+1]) {
//				H[j][k] = (float)(k - lambda[j]) / (lambda[j+1] - lambda[j]);
//			} else if (k >= lambda[j+1] && k <= lambda[j+2]) {
//				H[j][k] = (float)(lambda[j+2]-k) / (lambda[j+2] - lambda[j+1]);
//			} else if (k > lambda[j+2]) {
//				H[j][k] = 0;
//			}
//
//			Y[j] += (y_mag_squared[k]*H[j][k]);
//		}
//		X[j] = log10(Y[j]);
//	}
//
//
//
//	int m, n;
//	for (m = 0; m < 13; m++) {
//		for (n = 0; n < 26; n++) {
//			MFCC[m] = X[n] * cos(m * (((float)n) - (1/2.0)) * (pi /26));
//		}
//	}
//}
//
//int main(void)
//{
//	LCDK_GPIO_init();
//	L138_initialise_intr(FS_16000_HZ,ADC_GAIN_24DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);
//	LCDK_SWITCH_init();
//	LCDK_LED_init();
//
//	int i;
//	for (i = 0; i < 1024; i++)
//	{
//		data[i] = 0;
//		w[i] = 0;
//	}
//
//
//	while(1)
//   {
//		if (count == 1024)
//		{
//			HammingWindow();
//
//			int j;
//			for (j = 0; j < 1024; j++) {
//				x_in[2*j] = inputSignal[j];
//				x_in[2*j+1] = (float)0.0;
//			}
//
//			  // SAMPLE CODE: USE OF FFT ROUTINES
//
//				// Copy input data to the array used by DSPLib functions
//			  int n;
//			  for (n=0; n<N; n++)
//				{
//				  x_sp[2*n]   = x_in[2*n];
//				  x_sp[2*n+1] = x_in[2*n+1];
//				}
//
//				// Call twiddle function to generate twiddle factors needed for FFT and IFFT functions
//			  gen_twiddle_fft_sp(w_sp,N);
//
//			  // Call FFT routine
//			  DSPF_sp_fftSPxSP(N,x_sp,w_sp,y_sp,brev,4,0,N);
//
//			  // Call routine to separate the real and imaginary parts of data
//			  // Results saved to floats y_real_sp and y_imag_sp
//			  separateRealImg ();
//
//			  int i;
//			  for (i=0; i<N; i++)
//			  {
//			  	y_mag[i] = sqrt(pow(y_real_sp[i], 2) + pow(y_imag_sp[i], 2));
//
//			  	if (i < 513) {
//			  		y_mag_squared[i] = pow(y_mag[i], 2);
//			  	}
//			  }
//
//
//			count++;
//
//			filterBank();
//		}
//
//
//   }
//}
