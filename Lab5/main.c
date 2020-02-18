#include "L138_LCDK_aic3106_init.h"
#include "evmomapl138_gpio.h"
#include <stdint.h>
#include <math.h>
#include "L138_LCDK_switch_led.h"
#include "hamming_constants.h"
#include <ti/dsplib/dsplib.h>
#include "nnet.h"
#define N 1024

//#ifndef TRAINING
//#define TRAINING 1
//#endif

#define FILTER_BANK_SIZE 26
#define NUM_MFCCs 13

uint8_t mfcc_done;

#define NUM_PHIS (FILTER_BANK_SIZE + 2)

int16_t data[N];

#pragma DATA_ALIGN(ham_data,8);
float ham_data[2 * N]; //input to FFT
float fft_mag[N];

int32_t counter;

int32_t led_counter;
#define ign_samples 1024

int bool;
int rec_finished;
int ham_finished;

#pragma DATA_ALIGN(y_sp,8);
float   y_sp [2*N]; //output from FFT
#pragma DATA_ALIGN(w_sp,8);
float   w_sp [2*N]; //FFT twiddles

#define PI 3.14159265358979323

float y_real_sp [N];
float y_imag_sp [N];

float fft_resolution = 0;

float psd[N];

float pos_slopes[FILTER_BANK_SIZE] = {0.012314,0.011345,0.010451,0.0096281,
		0.0088699,0.0081714,0.0075279,0.0069351,0.006389,0.0058859,
		0.0054224,0.0049954,0.004602,0.0042396,0.0039057,0.0035981,
		0.0033148,0.0030538,0.0028133,0.0025917,0.0023876,0.0021996,
		0.0020264,0.0018668,0.0017198,0.0015844};

float neg_slopes[FILTER_BANK_SIZE] = {-0.011345,-0.010451,-0.0096281,-0.0088699,
		-0.0081714,-0.0075279,-0.0069351,-0.006389,-0.0058859,-0.0054224,
		-0.0049954,-0.004602,-0.0042396,-0.0039057,-0.0035981,-0.0033148,
		-0.0030538,-0.0028133,-0.0025917,-0.0023876,-0.0021996,-0.0020264,
		-0.0018668,-0.0017198,-0.0015844,-0.0014596};

float phis[NUM_PHIS] = {250,331.21,419.35,515.04,618.9,731.64,854.02,986.86,1131,
		1287.6,1457.5,1641.9,1842.1,2059.4,2295.2,2551.3,2829.2,3130.9,3458.3,3813.8,
		4199.6,4618.5,5073.1,5566.6,6102.3,6683.7,7314.9,8000};

float y_filters [FILTER_BANK_SIZE]; //filter bank output
float x_filters [FILTER_BANK_SIZE]; //log (y_filters)

float mfcc [NUM_MFCCs];

uint8_t hold;

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

	if (hold == 0)
	{
		if (led_counter < 16000)
		{
			LCDK_LED_on(4);
			led_counter++;
			rec_finished = 0;
		}
		else
		{

			if(counter<ign_samples)
			{
				rec_finished = 0;
				counter++;

			}

			else if(counter-ign_samples < N)
			{
				data[counter-ign_samples] = left_sample;

				if(counter-ign_samples == N - 1)
				{
					rec_finished = 1;
					LCDK_LED_off(4);
				}
				else
				{
					rec_finished = 0;
				}
				counter++;
			}


		}
	}
	else
	{
		rec_finished = 0;
	}

	output_right_sample(0);


}


void multiply_hamming()
{
	//multiply with the hamming window

	uint16_t a = 0;

	for(; a < N; a++)
	{
		ham_data[2*a] = (float)data[a] * (float)hamming_cos_lookup[a]; // real part
		ham_data[2*a + 1] = 0;                                     // imaginary part
	}
}

void compute_fft()
{
	DSPF_sp_fftSPxSP(N,ham_data,w_sp,y_sp,brev,4,0,N);

	uint16_t i;
	i = 0;
	for(;i < N; i++){
		psd[i] = y_sp[2*i] * y_sp[2*i] + y_sp[2*i+1] * y_sp[2*i+1]; //psd = fft output magnitude squared
		fft_mag[i] = sqrt(y_sp[2*i] * y_sp[2*i] + y_sp[2*i+1] * y_sp[2*i+1]); //psd
	}
}

void multiply_filter_banks()
{
	uint16_t i;
	for (i = 0; i < FILTER_BANK_SIZE; i++)
	{
		//for each filter

		//find start index of psd for current filter (ceil(filter start phi / FFT resolution))

		float filter_start_phi = phis[i];

		uint16_t psd_start_index = (uint16_t)(ceil(filter_start_phi/fft_resolution));

		//find last index of psd on positive slope of current filter (floor(filter peak phi / FFT resolution))

		float filter_peak_phi = phis[i+1];

		uint16_t psd_last_pos_index = (uint16_t)(filter_peak_phi/fft_resolution);

		//find end index of psd for current filter (floor(filter end phi / FFT resolution))

		float filter_end_phi = phis[i+2];
		uint16_t psd_end_index = (uint16_t)(filter_end_phi/fft_resolution);

		//multiply and accumulate with linear interpolation

		//positive slope
		uint16_t j;
		float accumulator = 0;
		for (j=psd_start_index; j < psd_last_pos_index; j++)
		{
			float cur_freq = fft_resolution * j;
			accumulator += psd[j] * (pos_slopes[i] * (cur_freq - filter_start_phi));
		}
		//negative slope

		for (j = psd_last_pos_index + 1; j < psd_end_index; j++)
		{
			float cur_freq = fft_resolution * j;
			accumulator += psd[j] * (neg_slopes[i] * (cur_freq - filter_peak_phi) + 1);
		}

		//store sum

		y_filters[i] = accumulator;

		// store log of sum

		x_filters[i] = (float)(log((double)accumulator));
	}
}

void calculate_mfccs()
{
	//sigma 1..26 X_m cos((m - 0.5) * k*pi/26);

	uint8_t m = 0;

	float accumulator = 0;

	uint8_t k = 0;

	for (k = 1; k <= 13; k++)
	{
		for (m = 1; m <= 26; m++)
		{
			accumulator += (float)(x_filters[m - 1] * cos((double)(((double)m - 1/2.0) * (k * PI)/(26.0))));
		}

		mfcc[k-1] = accumulator;
		accumulator = 0;
	}

}

//void nNet();

double mfcc_proc[13]; //should be our MFCCs




//preprocessing
double x1_step1_xoffset[13] = {10.55122,18.40086,-39.67926,12.15254,-14.14544,1.953335,-12.63301,-5.024483,-8.485577,3.05835,-9.330165,-5.183512,-6.146364};

double x1_step1_gain[13] = {0.0518000518000518,0.0680134693874775,0.0513846136533492,0.0779698825734584,0.0858046981246997,0.124282540198411,0.0898759949441158,0.149829299479103,0.13590408596314,0.189888079965668,0.213694945755098,0.155075352664613,0.226505901837778};


int x1_step1_ymin = -1;

// Layer 1
double b1[5] = {1.0164066416070700605,-2.2568204677192356122,0.66134404040363592436,0.18535977971440445455,1.7698318614421919559};

double IW1_1[NUM_NEURONS][NUM_INPUTS] =
{
    {-1.23870365751233,-0.405603422676608,0.805069573143060,1.00755415571320,0.448542345844904,-0.604347681410447,-0.814698590482039,-0.611966723993180,-0.629185325660739,0.217385236986731,-0.363938601313529,0.176324652979557,0.0650093972594191},

    {0.903340617021653,-0.136186002656182,-0.116746468170718,-0.530074623841976,0.163816648884418,-2.53168631248207,-1.82356521004074,-1.62032116700071,-0.876315527525455,0.779566802454068,1.67908931605754,0.942260663661116,1.51545997042103},

    {0.450005206288241,-1.53875725237325,-0.673513371072038,-0.638746034654803,0.154777398975361,0.0146951625238065,0.265772464287166,-0.836387593238653,0.595016423703234,-0.731414762463787,-0.242756252083001,-0.875965675295040,2.32401221453712},

    {-0.652366758777784,-0.744789163905541,0.960993645233636,1.91955952840238,1.28098152784414,0.974134535837299,0.277176149853257,-0.0547090304334035,-0.320639457557060,0.588485324136474,-1.13995512373277,-0.350902790871050,-2.00576819879276},

    {0.138233057776905,-1.15985830651868,-0.911750370282723,-0.456441076531383,0.606947023741142,0.862741343358838,2.31639832864599,0.844646514830315,0.471324514973744,-0.980989650233357,-0.847586865955043,-1.75230473629809,0.130873850863195}
};

//layer 2
double b2[4] = {1.6296247566886563618,-0.44277282482429142219,-1.1982419687001186759,0.9469068289694889673};

double LW2_1[NUM_OUTPUTS][NUM_NEURONS] =
{
    {0.632299857566359,5.55061123498436,0.370787282348035,-1.62618236482520,-2.87398352977029},
    {-2.48894757672857,-3.01218340228191,1.00869412401127,-5.46863097529729,2.82704843880217},
    {-0.360202645303264,-0.704127915991869,5.07265982678808,6.92077921914024,0.908079693038243},
    {0.682892298291095,-2.65236892254860,-6.12830475700577,1.34089017262973,-1.68240863013094}
};

double hidden[NUM_NEURONS]; //stores the output of the hidden layers

double output_temp[NUM_OUTPUTS];//same as o[k] in the slides
double output[NUM_OUTPUTS];

double sigmoid(double x)
{
    return(2.0/(1+exp(-2*x)) - 1);
}

double softmax(uint8_t x){
    //where x is the index into the output_temp array
    double sum;
    sum = 0;
    uint8_t i;
    for(i = 0; i < NUM_OUTPUTS; i++)
    {
        sum += exp(output_temp[i]);
    }
    return( (exp(output_temp[x])/sum) );
}

void nNet()
{

    //preprocessing steps
    uint8_t i;
    for(i = 0; i < 13; i++)
    {
        mfcc_proc[i] = mfcc[i] - x1_step1_xoffset[i];
        mfcc_proc[i] = mfcc_proc[i] * x1_step1_gain[i];
        mfcc_proc[i] = mfcc_proc[i] + x1_step1_ymin;
    }

    uint8_t x; //where x is the xth hidden layer neuron

    for(x = 0; x < NUM_NEURONS; x++)
    {
        double temp;
        temp = 0;
        uint8_t k; //where k is the kth input neuron
        for(k = 0; k < NUM_INPUTS; k++){
            temp += IW1_1[x][k] * mfcc_proc[k];
        }
        hidden[x] = sigmoid(temp + b1[x]);
    }

    for(x = 0; x < NUM_OUTPUTS; x++)
    {
        double temp;
        uint8_t k;//where k is the kth hidden neuron
        for(k = 0; k < NUM_NEURONS; k++)
        {
            temp += LW2_1[x][k] * hidden[k];
        }
        output_temp[x] = temp + b2[x];
    }

    for(x = 0; x < NUM_OUTPUTS; x++)
    {
        output[x] = softmax(x);
    }
}

int main(void)
{
	counter = 0;
	bool = 1;
	led_counter = 0;
	rec_finished = 0;

	mfcc_done = 0;

	fft_resolution = (16000)/N;

	uint16_t p = 0;

	for (p = 0 ; p < 2*N; p++)
	{
		ham_data[p] = 0.0;
	}

	LCDK_LED_init();
	gen_twiddle_fft_sp(w_sp,N);
	L138_initialise_intr(FS_16000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_MIC_INPUT);

	while(1)
	{
		//user should press, then unpress record button on GUI composer to begin recording

		if(bool == 1)
		{
			counter = 0;	 // reset counter to allow data overwrite
			led_counter = 0; // reset led counter to being 1 second countdown
			hold = 1;        // enter into hold state (waiting for button unpress)
			mfcc_done = 0;   // after collecting data, we want to clear old mfcc
		}
		else
		{
			hold = 0;		 // on button unpress, begin recording data
		}

		if(rec_finished == 1 && mfcc_done == 0)
		{
			//multiply with the hamming window
			multiply_hamming();

			//compute the FFT

			compute_fft();

			//multiply by filter banks

			multiply_filter_banks();

			//calculate cepstrum coefficients

			calculate_mfccs();

#ifndef TRAINING
			nNet();
#endif //TRAINING

			mfcc_done = 1; //only want the computation to occur once

		}
	}

}
