#include "imgproc.h"

template<class T>
void tfePixelsToTensor(
	unsigned char* pixels,
    int bytesInPixel,	
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	T* floatValues)
{
	int idx = 0;
	if (flipUpsideDown)
	{
		//handle flip upside down
		for (int i = 0; i < height; i++)
			for (int j = 0; j < width; j++)
			{
				unsigned char* val = &pixels[((height - i - 1) * width + j) * bytesInPixel];
				if (swapBR)
				{
					floatValues[idx++] = (T) ( *(val+2) - inputMean) * scale;
					floatValues[idx++] = (T) ( *(val+1) - inputMean) * scale;
					floatValues[idx++] = (T) ( *val - inputMean) * scale;
				}
				else
				{
					floatValues[idx++] = (T) ( *val - inputMean) * scale;
					floatValues[idx++] = (T) ( *(val+1) - inputMean) * scale;
					floatValues[idx++] = (T) ( *(val+2) - inputMean) * scale;
				}
			}
	}
	else
	{
		for (int i = 0; i < height*width; ++i)
		{
			unsigned char* val = &pixels[i * bytesInPixel];
			if (swapBR)
			{
				floatValues[idx++] = (T) (*(val+2) - inputMean) * scale;
				floatValues[idx++] = (T) (*(val+1) - inputMean) * scale;
				floatValues[idx++] = (T) (*val - inputMean) * scale;
			}
			else
			{
				floatValues[idx++] = (T) (*val - inputMean) * scale;
				floatValues[idx++] = (T) (*(val+1) - inputMean) * scale;
				floatValues[idx++] = (T) (*(val+2) - inputMean) * scale;
			}
		}
	}
}


void tfePixel32ToPixelFloat(
	unsigned char* pixels, 
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	float* floatValues)
{
	tfePixelsToTensor<float>(pixels, 4, width, height, inputMean, scale, flipUpsideDown, swapBR, floatValues);
}

void tfePixel32ToPixelByte(
	unsigned char* pixels, 
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	unsigned char* result)
{
	tfePixelsToTensor<unsigned char>(pixels, 4, width, height, inputMean, scale, flipUpsideDown, swapBR, result);
}

void tfePixel24ToPixelFloat(
	unsigned char* pixels, 
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	float* floatValues)
{
	tfePixelsToTensor<float>(pixels, 3, width, height, inputMean, scale, flipUpsideDown, swapBR, floatValues);
}

void tfePixel24ToPixelByte(
	unsigned char* pixels, 
	int width, 
	int height, 
	float inputMean, 
	float scale, 
	bool flipUpsideDown, 
	bool swapBR, 
	unsigned char* result)
{
	tfePixelsToTensor<unsigned char>(pixels, 3, width, height, inputMean, scale, flipUpsideDown, swapBR, result);
}
