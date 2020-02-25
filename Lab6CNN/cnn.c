#include "cnn.h"
#include <stdio.h>
#include <math.h>
/*
 * conv.c
 *
 */


void conv(float input[], float kernel[], float bias[], float result[], int input_height, int input_width, int input_channel, int kernel_size, int kernel_channel){
    int pad_size = (kernel_size-1)/2;
    int x, y, c, kx, ky, kc;
    for(y = 0; y < input_height; y++){
    	for(x = 0; x < input_width; x++){
            for(c = 0; c < kernel_channel; c++){
                result[(y*input_width+x)*kernel_channel+c] = 0;
                for(ky = 0; ky < kernel_size; ky++){
                    for(kx = 0; kx < kernel_size; kx++){
                        for(kc = 0; kc < input_channel; kc++){
                            if((x + kx < pad_size) || (x + kx >= pad_size + input_width)){
                                continue;
                            }else if((y + ky < pad_size) || (y + ky >= pad_size + input_height)){
                                continue;
                            }else{
                                int input_idx = ((y + ky - pad_size)*input_width + x + kx - pad_size)*input_channel + kc;
                                int kernel_dix = ((ky*kernel_size + kx)*input_channel + kc)*kernel_channel+c;
                                float temp_out = input[input_idx]
                                                       *kernel[kernel_dix];
                                result[(y*input_width+x)*kernel_channel+c] += temp_out;
                            }

                        }
                    }
                }
                result[(y*input_width+x)*kernel_channel+c] += bias[c];
                if(result[(y*input_width+x)*kernel_channel+c] < 0.0){
                	result[(y*input_width+x)*kernel_channel+c] = 0.0;
                }
            }
        }
    }
}

void nn_pool(float input[], float output[], int height, int width, int channel, int pool_size){
    int x, y, c, kx, ky;
    int out_width = width/pool_size;
    int out_height = height/pool_size;
    for (y = 0; y < out_height; y++){
    	for (x = 0; x < out_width; x++){
            for (c = 0; c < channel; c++){
                float max = -100000;
                for (ky = 0; ky < pool_size; ky++){
                	for (kx = 0; kx < pool_size; kx++){
                        if (input[(((y*pool_size + ky)*width) + x*pool_size + kx)*channel + c] > max)
                            max = input[(((y*pool_size + ky)*width) + x*pool_size + kx)*channel + c];
                    }
                }
                output[(y*out_width + x)*channel + c] = max;
            }
        }
    }
}

double softmax(double input_vec[], double input, int input_size){
    int i = 0;
    double sum = 0;
    for(i = 0; i < input_size; i++){
        double sum += exp(input_vec[i]);
    }
    return input/sum;
}

void dense(float input[],float kernel[], float bias[], double output[], int input_size, int output_size){
	int i = 0;
    int j = 0;
    for(j = 0; j < input_size; j++){
        for(i = 0; i < output_size; i++){
            output[i] += (double) input[j] * (double) kernel[j * output_size + i];
        }

    }

    i = 0;
    for(i = 0; i < output_size; i++){
        output[i] += (double) bias[j];
        output[i] = softmax(output, output[i], output_size);
    }
}