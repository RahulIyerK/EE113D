#include "L138_LCDK_aic3106_init.h"
#include "evmomapl138_gpio.h"
#include <stdio.h>

// Second-Order LPF Parameters
#define NUM_SECTIONS 3 // define number of sections


float b[NUM_SECTIONS][3]={ {1.0, 2.0, 1.0} , {1.0, 2.0, 1.0} , {1.0, 1.0, 0.0}};
float a[NUM_SECTIONS][2]={ {-1.9246, 0.9358} , {-1.8296, 0.8403}, {-0.8979,0.0} };
float G[NUM_SECTIONS] = {0.0028, 0.0027, 0.0511};
float w[NUM_SECTIONS][2] = {{0.0,0.0},{0.0,0.0},{0.0,0.0}};

// Use values obtained from Matlab Filter Design Tool

int section;   // index for section number
float input;   // input to each section
float wn,yn;   // intermediate and output values in each stage

interrupt void interrupt4(void) // associated in intvecs.asm with INT4
{
  input = ((float)input_right_sample());

  for (section=0 ; section<NUM_SECTIONS ; section++)
  {
    wn = input - a[section][0]*w[section][0] - a[section][1]*w[section][1];
    yn = (b[section][0]*wn + b[section][1]*w[section][0] + b[section][2]*w[section][1]); //a[section][0];
    w[section][1] = w[section][0];
    w[section][0] = wn;
    yn = G[section]*yn;
    input = yn;              // output of current section will be input to next
  }

  output_right_sample((int16_t)(yn)); // before writing to codec

  return;                       //return from ISR
}

int main(void)
{
  L138_initialise_intr(FS_48000_HZ,ADC_GAIN_0DB,DAC_ATTEN_0DB,LCDK_LINE_INPUT);

  while(1);
}  // end of main()

