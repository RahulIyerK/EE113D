//#include "L138_LCDK_aic3106_init.h"
//#include "evmomapl138_gpio.h"
//#include <stdint.h>
//#include <math.h>
//#include "L138_LCDK_switch_led.h"
//#include <ti/dsplib/dsplib.h>
//#include "nnet.h"
//
//static float* mfcc;
//
//static double* mfcc_proc;
//
////preprocessing
//static double* x1_step1_xoffset;
//
//static double* x1_step1_gain;
//
//static int x1_step1_ymin;
//
//// Layer 1
//static double* b1;
//
//static double** IW1_1;
//
////layer 2
//static double* b2;
//
//static double** LW2_1;
//
//static double* hidden; //stores the output of the hidden layers
//
//static double* output_temp;//same as o[k] in the slides
//static double* output;
//
//
//double sigmoid(double x)
//{
//    return(2.0/(1+exp(-2*x)) - 1);
//}
//
//double softmax(uint8_t x){
//    //where x is the index into the output_temp array
//    double sum;
//    sum = 0;
//    uint8_t i;
//    for(i = 0; i < NUM_OUTPUTS; i++)
//    {
//        sum += exp(output_temp[i]);
//    }
//    return( (exp(output_temp[x])/sum) );
//}
//
//void nNet()
//{
//
//    //preprocessing steps
//    uint8_t i;
//    for(i = 0; i < 13; i++)
//    {
//        mfcc_proc[i] = mfcc[i] - x1_step1_xoffset[i];
//        mfcc_proc[i] = mfcc_proc[i] * x1_step1_gain[i];
//        mfcc_proc[i] = mfcc_proc[i] + x1_step1_ymin;
//    }
//
//    uint8_t x; //where x is the xth hidden layer neuron
//
//    for(x = 0; x < NUM_NEURONS; x++)
//    {
//        double temp;
//        temp = 0;
//        uint8_t k; //where k is the kth input neuron
//        for(k = 0; k < NUM_INPUTS; k++){
//            temp += IW1_1[x][k] * mfcc_proc[k];
//        }
//        hidden[x] = sigmoid(temp + b1[x]);
//    }
//
//    for(x = 0; x < NUM_OUTPUTS; x++)
//    {
//        double temp;
//        uint8_t k;//where k is the kth hidden neuron
//        for(k = 0; k < NUM_NEURONS; k++)
//        {
//            temp += LW2_1[x][k] * hidden[k];
//        }
//        output_temp[x] = temp + b2[x];
//    }
//
//    for(x = 0; x < NUM_OUTPUTS; x++)
//    {
//        output[x] = softmax(x);
//    }
//}
