float input[13]; //should be our MFCCs

#define NUM_NEURONS 5

#define NUM_INPUTS 13

#define NUM_OUTPUTS 4

//preprocessing
float x1_step1_xoffset[13] = {10.55122,18.40086,-39.67926,12.15254,-14.14544,1.953335,-12.63301,-5.024483,-8.485577,3.05835,-9.330165,-5.183512,-6.146364};

float x1_step1_gain[13] = {0.0518000518000518,0.0680134693874775,0.0513846136533492,0.0779698825734584,0.0858046981246997,0.124282540198411,0.0898759949441158,0.149829299479103,0.13590408596314,0.189888079965668,0.213694945755098,0.155075352664613,0.226505901837778};

int x1_step1_ymin = -1;

// Layer 1
float b1[5] = {-1.1090005486442411353,-0.47005990992527546535,0.76651183774701192597,-1.2476098742512853335,-1.6189337372948662264};

double IW1_1[5][13] = 
{
    {0.799826734244586,0.684293017355830,0.343540782550632,-0.298793168548839,-0.372566805020775,-1.13297028748624,0.536240291907740,-0.770677233318099,0.0651439140922618,0.687636659671675,0.0459683883326758,0.273891241843026,-0.211290859488213},

    {0.0393408633135863,-0.139963931297944,-0.788273350691327,0.345952471292520,0.862438424670946,-0.0348649898706708,-0.0627482127940035,0.304967985931216,0.526623591216334,-0.364282604809750,0.303361431108395,-1.24325326526118,0.225704752922956},

    {-0.0525148030094539,0.470780258731225,-1.20055888337574,-0.368536320222410,0.142690417925475,-0.770344531630178,0.734368212531027,-0.849150722697320,0.932682782489963,-0.000297134916850420,0.754099708992633,-0.131572918878189,0.593312408451487},

    {-0.537489608477635,-0.923421942228971,0.213318368844345,0.785673821690430,1.13300483236876,0.398451765620800,0.186566802457949,-0.117662096894144,-0.180720097982794,-0.307407040764196,-0.815695381348144,-0.356752986052008,-0.142609539827437},

    {0.0815920056985584,0.176726237771895,0.386696050170652,-0.371392097109823,0.0222178914595895,-0.603077981402980,-0.348488088052508,0.167996957257226,0.598347136186956,-0.800337606583688,0.294335014161395,0.430610395679496,0.0382915575525462}
}

//layer 2
double b2[4] = {-0.20126178218016088639,-0.022615511899870682777,0.59310903103854462071,-0.58696101768370756435};

double LW2_1[NUM_OUTPUTS][NUM_NEURONS] = 
{
    {1.35677014168525,-1.16874662294516,0.679824401929269,-0.815434014141919,0.249531557447857},
    {-0.705944417496923,0.348153421309614,0.864606695447717,-1.01498310220962,0.171635567212044},
    {0.408723594754667,0.588490751642447,1.21737512036879,1.81202459535658,0.527509322197618},
    {0.0244242669430040,-1.01087009563761,-1.88486690148643,-0.949880789114735,0.142012025621191}
}

float hidden[NUM_NEURONS]; //stores the output of the hidden layers

double output_temp[NUM_OUTPUTS];//same as o[k] in the slides
float output[NUM_OUTPUTS];

double sigmoid(double x)
{
    return(2/(1+exp(-2*x)) - 1);
}

double softmax(uint8_t x){
    //where x is the index into the output_temp array
    int16_t sum;
    sum = 0;
    uint8_t i;
    for(i = 0; i < NUM_OUTPUTS; i++)
    {
        sum += exp(output_temp[i]);
    }
    return((double) (exp(output_temp[x])/sum));
}

void nNet()
{

    //preprocessing steps
    uint8_t i;
    for(i = 0; i < 13; i++)
    {
        neuralY[i] = input[i] - x1_step1_xoffset[i];
        neuralY[i] = neuralY[i] * x1_step1_gain[i];
        neuralY[i] = neuralY[i] + x1_step1_ymin[i];
    }

    uint8_t x; //where x is the xth hidden layer neuron

    for(x = 0; x < NUM_NEURONS; x++)
    {
        double temp;
        temp = 0;
        uint8_t k//where k is the kth input neuron
        for(k = 0; k < NUM_INPUTS; k++){
            temp += IW1_1[k][x] * input[k];
        }
        hidden[x] = (float) sigmoid(temp + b1[x]);
    }

    for(x = 0; x < NUM_OUTPUTS; x++)
    {
        double temp;
        uint8_t k;//where k is the kth hidden neuron
        for(k = 0; k < NUM_NEURONS; k++)
        {
            temp += LW2_1[x][k] * hidden[k];
        }
        output_temp[x] = temp +  + b2[x];
    }

    for(x = 0; x < NUM_OUTPUTS; x++)
    {
        output[x] = (float) softmax(x);
    }
}