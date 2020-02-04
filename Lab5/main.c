#include "L138_LCDK_aic3106_init.h"
#include "evmomapl138_gpio.h"
#include <stdint.h>
#include <math.h>
#include "L138_LCDK_switch_led.h"
#include "hamming_constants.h"

#define N 1024

int16_t data[N];

#pragma DATA_ALIGN(ham_data,8);
float ham_data[2 * N];

int32_t counter;

int i;
#define ign_samples 1024

int bool;
int rec_finished;
int ham_finished;

#pragma DATA_ALIGN(y_sp,8);
float   y_sp [2*N];
#pragma DATA_ALIGN(w_sp,8);
float   w_sp [2*N];

#define PI 3.14159265358979323

float y_real_sp [N];
float y_imag_sp [N];

float psd[N];

separateRealImg () {
    int i, j;

    for (i = 0, j = 0; j < N; i+=2, j++) {
        y_real_sp[j] = y_sp[i];
        y_imag_sp[j] = y_sp[i + 1];
    }
}

unsigned char brev[64] = {
    0x0, 0x20, 0x10, 0x30, 0x8, 0x28, 0x18, 0x38,
    0x4, 0x24, 0x14, 0x34, 0xc, 0x2c, 0x1c, 0x3c,
    0x2, 0x22, 0x12, 0x32, 0xa, 0x2a, 0x1a, 0x3a,
    0x6, 0x26, 0x16, 0x36, 0xe, 0x2e, 0x1e, 0x3e,
    0x1, 0x21, 0x11, 0x31, 0x9, 0x29, 0x19, 0x39,
    0x5, 0x25, 0x15, 0x35, 0xd, 0x2d, 0x1d, 0x3d,
    0x3, 0x23, 0x13, 0x33, 0xb, 0x2b, 0x1b, 0x3b,
    0x7, 0x27, 0x17, 0x37, 0xf, 0x2f, 0x1f, 0x3f
};

// Function for generating sequence of twiddle factors
void gen_twiddle_fft_sp (float *w, int n)
{
    int i, j, k;
    double x_t, y_t, theta1, theta2, theta3;

    for (j = 1, k = 0; j <= n >> 2; j = j << 2)
    {
        for (i = 0; i < n >> 2; i += j)
        {
            theta1 = 2 * PI * i / n;
            x_t = cos (theta1);
            y_t = sin (theta1);
            w[k] = (float) x_t;
            w[k + 1] = (float) y_t;

            theta2 = 4 * PI * i / n;
            x_t = cos (theta2);
            y_t = sin (theta2);
            w[k + 2] = (float) x_t;
            w[k + 3] = (float) y_t;

            theta3 = 6 * PI * i / n;
            x_t = cos (theta3);
            y_t = sin (theta3);
            w[k + 4] = (float) x_t;
            w[k + 5] = (float) y_t;
            k += 6;
        }
    }
}

interrupt void interrupt4(void) // interrupt service routine
{
	int16_t left_sample = input_right_sample();
	if (i < 16000){
		LCDK_LED_on(4);
		i++;
	}
	else{
		LCDK_LED_off(4);

		if(counter<ign_samples){
		}

		else if(counter-ign_samples < N){
			data[counter-ign_samples] = left_sample;
			if(counter-ign_samples == N - 1){
				rec_finished = 1;
			}
		}
		counter++;

	}


	output_right_sample(0);


}


void multiply_hamming(){
	//multiply with the hamming window
	int a = 0;
	for(; a < N; a++){
		ham_data[2*a] = (float)data[a] * (float)hamming_lookup[a];
		ham_data[2*a + 1] = 0;
	}
}

void compute_fft(){
	DSPF_sp_fftSPxSP(N,x_sp,w_sp,y_sp,brev,4,0,N);
	int i;
	i = 0;
	for(;i < N; i++){
		psd[i] = y_sp[2*i] * y_sp[2*i] + y_sp[2*i+1] * y_sp[2*i+1];
	}
}

int main(void)
{
	counter = 0;
	bool = 0;
	i = 0;
	rec_finished = 0;
	ham_finished = 0;

	LCDK_LED_init();
	gen_twiddle_fft_sp(w_sp,N);
	L138_initialise_intr(FS_16000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);

	while(1){
		if(bool == 1){
			rec_finished = 0;
			ham_finished = 0;
			counter = 0;
			i = 0;
		}

		if(rec_finished == 1){
			//multiply with the hamming window
			multiply_hamming();

			//compute the FFT



		}
	}

}
