#ifndef BMP
#define BMP
#include "m_mem.h"
#include <stdlib.h>

#pragma pack(1)
struct BitMap
{
   unsigned short int Type;
   unsigned int Size;
   unsigned short int Reserved1, Reserved2;
   unsigned int Offset;
} Header;

struct BitMapInfo
{
   unsigned int Size;
   int Width, Height;
   unsigned short int Planes;
   unsigned short int Bits;
   unsigned int Compression;
   unsigned int ImageSize;
   int xRes, yRes;
   unsigned int Colors;
   unsigned int ImptColors;
} InfoHeader;

unsigned char* usb_imread(char* g_cTmpBuf)
{
	FRESULT fresult;
	FIL file;
	unsigned short usBytesRead;
	unsigned char *bitmap;
	int i, dataSize;
	int padding;
	unsigned char *pad;

	//
	// Open the file for reading.
	//
	fresult = f_open(&file, g_cTmpBuf, FA_READ);

	//
	// If there was some problem opening the file, then return an error.
	//
	if(fresult != FR_OK)
	{
		printf("\nCannot open file\n");
		exit(1);
	}

	printf("Reading the bmp header...\n");

	// Read the file header
	f_read(&file, &Header.Type, sizeof(Header.Type), &usBytesRead);
	f_read(&file, &Header.Size, sizeof(Header.Size), &usBytesRead);
	f_read(&file, &Header.Reserved1, sizeof(Header.Reserved1), &usBytesRead);
	f_read(&file, &Header.Reserved2, sizeof(Header.Reserved2), &usBytesRead);
	f_read(&file, &Header.Offset, sizeof(Header.Offset), &usBytesRead);
	printf("size of Header = %d\n", sizeof(Header));

	// Read the info header
	f_read(&file, &InfoHeader.Size, sizeof(InfoHeader.Size), &usBytesRead);
	f_read(&file, &InfoHeader.Width, sizeof(InfoHeader.Width), &usBytesRead);
	f_read(&file, &InfoHeader.Height, sizeof(InfoHeader.Height), &usBytesRead);
	f_read(&file, &InfoHeader.Planes, sizeof(InfoHeader.Planes), &usBytesRead);
	f_read(&file, &InfoHeader.Bits, sizeof(InfoHeader.Bits), &usBytesRead);
	f_read(&file, &InfoHeader.Compression, sizeof(InfoHeader.Compression), &usBytesRead);
	f_read(&file, &InfoHeader.ImageSize, sizeof(InfoHeader.ImageSize), &usBytesRead);
	f_read(&file, &InfoHeader.xRes, sizeof(InfoHeader.xRes), &usBytesRead);
	f_read(&file, &InfoHeader.yRes, sizeof(InfoHeader.yRes), &usBytesRead);
	f_read(&file, &InfoHeader.Colors, sizeof(InfoHeader.Colors), &usBytesRead);
	f_read(&file, &InfoHeader.ImptColors, sizeof(InfoHeader.ImptColors), &usBytesRead);
	printf("size of InfoHeader = %d\n", sizeof(InfoHeader));
	printf("Width: %d\n", InfoHeader.Width);
	printf("Height: %d\n", InfoHeader.Height);

	dataSize = InfoHeader.Width*InfoHeader.Height*3;

	padding = (4 - ((InfoHeader.Width*3) % 4)) % 4 ;
	pad = malloc(padding*sizeof(unsigned char));

	bitmap = m_malloc(dataSize);



	if (!bitmap)
	{
		printf("out of memory!\n");
	}
	else
	{
		printf("Successfully allocated memory for the bitmap\n");
	}

	printf("Reading BMP file...\n");
	for (i=0; i <  InfoHeader.Height; i++)
	{
		// Read one row at a time
		fresult = f_read(&file, &bitmap[i * InfoHeader.Width * 3], InfoHeader.Width * 3, &usBytesRead);
		if (fresult || usBytesRead == 0)
		{
			// Error or EOF
			printf("BMP_ERROR_PREMATUREEOF");
			return 0;
		}
		fresult = f_read(&file, &pad, padding, &usBytesRead);
		if (fresult || (usBytesRead == 0) && (padding != 0))
		{
			// Error or EOF
			printf("BMP_ERROR_PREMATUREEOF");
			return 0;
		}
	}


	printf("Finish reading BMP file...\n");

	return bitmap;
}

float* usb_txtread(char* g_cTmpBuf, int data_size)
{
	FRESULT fresult;
	FIL file;
	unsigned short usBytesRead;
	float *array_out;
	int i, j, k;
	unsigned char test_1;
	unsigned char temp[32];
	float temp_f;
	//
	// Open the file for reading.
	//
	fresult = f_open(&file, g_cTmpBuf, FA_READ);

	//
	// If there was some problem opening the file, then return an error.
	//
	if(fresult != FR_OK)
	{
		printf("\nCannot open file\n");
		exit(1);
	}

	printf("Reading the txt file...\n");
	array_out = m_malloc(data_size*sizeof(temp_f));
	if (!array_out)
	{
		printf("out of memory!\n");
	}
	// Read the file header
//	printf("%f", test_1);
	for(i=0; i<data_size; i++){
		memset(temp, 0, 32*sizeof(test_1));
		for(j=0; j<32; j++){
			f_read(&file, &test_1, sizeof(test_1), &usBytesRead);
			if(test_1 != 10){
				temp[j] = test_1;
			}else{
				array_out[i] = atof(temp);
				break;
			}
		}
	}


	printf("Finish reading txt file...\n");

	return array_out;
}

void usb_imshow(char* name, unsigned char* bitmap)
{
	FRESULT fresult;
	static FIL file;
	unsigned short bytesWritten;
	int i, padding;
	unsigned char *pad;

	printf("size of InfoHeader = %d\n", sizeof(InfoHeader));
	printf("Width: %d\n", InfoHeader.Width);
	printf("Height: %d\n", InfoHeader.Height);

	// Create a file (overwriting any existing file!)
	fresult = f_open(&file, name, FA_READ | FA_WRITE | FA_CREATE_ALWAYS);
	if(fresult !=FR_OK)
	{
		printf("BMP_ERROR_UNABLETOCREATEFILE\n");
		return;
	}

	printf("Writing BMP file...\n");

	// Write header to usb
	f_write(&file, &Header.Type, sizeof(Header.Type), &bytesWritten);
	f_write(&file, &Header.Size, sizeof(Header.Size), &bytesWritten);
	f_write(&file, &Header.Reserved1, sizeof(Header.Reserved1), &bytesWritten);
	f_write(&file, &Header.Reserved2, sizeof(Header.Reserved2), &bytesWritten);
	f_write(&file, &Header.Offset, sizeof(Header.Offset), &bytesWritten);
	f_write(&file, &InfoHeader.Size, sizeof(InfoHeader.Size), &bytesWritten);
	f_write(&file, &InfoHeader.Width, sizeof(InfoHeader.Width), &bytesWritten);
	f_write(&file, &InfoHeader.Height, sizeof(InfoHeader.Height), &bytesWritten);
	f_write(&file, &InfoHeader.Planes, sizeof(InfoHeader.Planes), &bytesWritten);
	f_write(&file, &InfoHeader.Bits, sizeof(InfoHeader.Bits), &bytesWritten);
	f_write(&file, &InfoHeader.Compression, sizeof(InfoHeader.Compression), &bytesWritten);
	f_write(&file, &InfoHeader.ImageSize, sizeof(InfoHeader.ImageSize), &bytesWritten);
	f_write(&file, &InfoHeader.xRes, sizeof(InfoHeader.xRes), &bytesWritten);
	f_write(&file, &InfoHeader.yRes, sizeof(InfoHeader.yRes), &bytesWritten);
	f_write(&file, &InfoHeader.Colors, sizeof(InfoHeader.Colors), &bytesWritten);
	f_write(&file, &InfoHeader.ImptColors, sizeof(InfoHeader.ImptColors), &bytesWritten);

	padding = (4 - ((InfoHeader.Width*3) % 4)) % 4 ;
	pad = malloc(padding*sizeof(unsigned char));

	//Write data to usb
	for (i=0; i <  InfoHeader.Height; i++)
	{
		// Write one row at a time
		fresult = f_write(&file, &bitmap[i * InfoHeader.Width * 3], InfoHeader.Width * 3, &bytesWritten);
		if(padding != 0)
			fresult = f_write(&file, &pad, padding, &bytesWritten);
	}

	// Write EOF (2 bytes)
	unsigned char eof = 0x0000;
	f_write(&file, &eof, 1, &bytesWritten);
	f_write(&file, &eof, 1, &bytesWritten);

	printf("Finish writing BMP file...\n");
	// Close the file
	f_close(&file);

}

unsigned char* imread(char* name)
{

	unsigned char *bitmap;
	FILE *BMP_in = fopen (name, "rb");
	int i, datasize;
	int padding;
	unsigned char *pad;

	if (BMP_in == NULL)
	{
	    printf("\nCannot open file\n");
	      exit(1);
	}

	printf("Reading the bmp header...\n");
	fread(&Header, sizeof(Header), 1, BMP_in);
	fread(&InfoHeader, sizeof(InfoHeader), 1, BMP_in);


	printf("size of Header = %d\n", sizeof(Header));
	printf("size of InfoHeader = %d\n", sizeof(InfoHeader));
	printf("Width: %d\n", InfoHeader.Width);
	printf("Height: %d\n", InfoHeader.Height);

	datasize = InfoHeader.Width*InfoHeader.Height*3;

	padding = (4 - ((InfoHeader.Width*3) % 4)) % 4 ;
	pad = malloc(padding*sizeof(unsigned char));

	bitmap = m_malloc(datasize);



    if (!bitmap)
     {
    	 printf("out of memory!\n");
     }
     else
     {
    	 printf("Successfully allocated memory for the bitmap\n");

     }

    printf("Reading BMP file...\n");
    for (i=0; i < datasize; i++)
    {
       	 fread(&bitmap[i], 1,1,  BMP_in);

       	 if (i % (3*InfoHeader.Width) == 3*InfoHeader.Width -1)
       	 {
       		fread(&pad, padding*sizeof(unsigned char),1,  BMP_in);
       	 }

    }


    fclose(BMP_in);

    printf("Finish reading BMP file...\n");

	return bitmap;
}


void imshow(char* name,unsigned char* bitmap)
{



    FILE *BMP_out;
    int filesize, datasize, i;
	int padding;
	unsigned char *pad;


    datasize = InfoHeader.Width*InfoHeader.Height*3;
    filesize = 54 + 3*InfoHeader.Width* InfoHeader.Height;

	padding = (4 - ((InfoHeader.Width*3) % 4)) % 4 ;
	pad = malloc(padding*sizeof(unsigned char));

	for (i = 0; i < padding; i++)
	{
		pad[i] = 0;
	}


    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpInfoHeader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);
    bmpInfoHeader[ 4] = (unsigned char)(       InfoHeader.Width    );
    bmpInfoHeader[ 5] = (unsigned char)(       InfoHeader.Width>> 8);
    bmpInfoHeader[ 6] = (unsigned char)(       InfoHeader.Width>>16);
    bmpInfoHeader[ 7] = (unsigned char)(       InfoHeader.Width>>24);
    bmpInfoHeader[ 8] = (unsigned char)(       InfoHeader.Height    );
    bmpInfoHeader[ 9] = (unsigned char)(       InfoHeader.Height>> 8);
    bmpInfoHeader[10] = (unsigned char)(       InfoHeader.Height>>16);
    bmpInfoHeader[11] = (unsigned char)(       InfoHeader.Height>>24);

    BMP_out = fopen(name,"wb");
    fwrite(bmpfileheader,1,14,BMP_out);
    fwrite(bmpInfoHeader,1,40,BMP_out);

    UARTprintf("Writing BMP file...\n");

    for(i=0; i < datasize; i++)
    {

    	if (i%(InfoHeader.Width*3) == 0)
    	{
    		UARTprintf("i = %d\n",i);
    	}

        fwrite(&bitmap[i], 1,1,  BMP_out);

        if (i % (3*InfoHeader.Width) == 3*InfoHeader.Width -1)
        {
        	fwrite(&pad, padding*sizeof(unsigned char),1,  BMP_out);
        }

     }
    UARTprintf("Finish writing BMP file...\n");
    fclose(BMP_out);

}

#endif
