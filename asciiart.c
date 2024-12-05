#include <stdlib.h>
#include <stdio.h>


#include <stdbool.h>
#include <string.h>

// symbolic constants for array indices for rgb
#define RED 0
#define GREEN 1
#define Blue 2

//function prototypes
// convert array in the format of bgr to rgb (changes ordering)
void BGRtoRGB(short int imgArray[]);
// find luma based on bt.709 luma formula (assumes rgb)
void luma(short int imgArray[], double lumaArray[], long numPixels);

int main (int argc, char **argv)
{
	// check number of arguments for input location and output location
	if (argc != 3) {
		printf("Usage: ./asciiart inputfile outputfile\n");
		return 0;
	}

	FILE *inputptr;
	inputptr = fopen(argv[1], "r");
	if (inputptr == NULL) {
		printf("Can't open file!\n");
		return 0;
	}
	
	// safely read header from file (14 bytes)
	char headerbuff[54] = {};
	if (fgets(headerbuff, 54, inputptr) == NULL || feof(inputptr)) {
		printf("Error reading header.\n");
		return 0;
	}

	unsigned int fsize;
	unsigned int arrayOffset;
	unsigned int imgWidth;
	int imgHeight;
	unsigned int bitPerPixel;
	unsigned int compression;

	memcpy(&fsize, &headerbuff[2], 4);
	memcpy(&arrayOffset, &headerbuff[10], 4);
	memcpy(&imgWidth, &headerbuff[0x12], 4);
	memcpy(&imgHeight, &headerbuff[0x16], 4);
	memcpy(&bitPerPixel, &headerbuff[0x1C], 2);
	memcpy(&compression, &headerbuff[0x1E], 4);

	//apparently height can be negative....
	bool heightReversed = imgHeight < 0;
	imgHeight = abs(imgHeight);

	// check for bmp format
	if (headerbuff[0] != 'B' || headerbuff[1] != 'M') {
		printf("Not a bitmap file!\n");
		return 0;
	}
	// filesize sanity checks
	if (fsize == 0 || arrayOffset == 0) {
		printf("Invalid File\n");
		return 0;
	}
	//bitperpixel and compression settings check
	if (bitPerPixel != 24 || compression != 0) {
		printf("Doesn't support 24bits per pixel or compression yet!\n");
		return 0;
	}

	// calculate number of pixels, make future uses easier
	long numPixels = imgWidth * imgHeight;

	// allocate space for the rgb 3d array initialized as 1d array
	short int *imgArray = (short int*) malloc(sizeof(short int) * numPixels * 3);
	if (imgArray == NULL) {
		printf("Something has gone wrong allocating! \n");
		return 0;
	}
	
	// read file into array
	if (fgets((char*)imgArray, numPixels * 3, inputptr) == NULL || feof(inputptr)) {
		printf("Error reading img.\n");
		return 0;
	}
	// done with the input file
	fclose(inputptr);

	//find luma
	double *luma = (double*) malloc(sizeof(double) * numPixels);

	free(imgArray);
	free(luma);
	return 0;
}

void luma(short int *imgArray[], double *lumaArray[], long numPixels)
{
	short int red;
	short int green;
	short int blue;

	for (pixelIndex = 0; pixelIndex < numPixels; pixelIndex++) {
		red = imgArray[pixleIndex * 3];
		green = imgArray[pixleIndex * 3 + 1];
		blue = imgArray[pixelIndex * 3 + 2];

		lumaArray[pixelIndex]
	}
}
