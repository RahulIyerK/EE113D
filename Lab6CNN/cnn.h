/*
 * conv.h
 *
 */

#ifndef CNN_H_
#define CNN_H_

void conv(float input[], float kernel[], float bias[], float result[],int input_height, int input_width, int input_channel, int kernel_size, int kernel_channel);
void nn_pool(float input[], float output[], int height, int width, int channel, int pool_size);
void dense(float input[],float kernel[], float bias[], double output[], int input_size, int output_size);
#endif /* CNN_H_ */
