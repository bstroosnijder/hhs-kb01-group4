#ifndef BITMAP_H_
#define BITMAP_H_

#include <fstream>
#include "..\logger\Logger.h"

namespace engine
{
	typedef struct tagBITMAPFILEHEADER {
		unsigned short bfType;
		unsigned long bfSize;
		unsigned short  bfReserved1;
		unsigned short  bfReserved2;
		unsigned long bfOffBits;
	} BITMAPFILEHEADER;

	typedef struct tagBITMAPINFOHEADER {
		unsigned long biSize;
		long  biWidth;
		long  biHeight;
		unsigned short  biPlanes;
		unsigned short  biBitCount;
		unsigned long biCompression;
		unsigned long biSizeImage;
		long  biXPelsPerMeter;
		long  biYPelsPerMeter;
		unsigned long biClrUsed;
		unsigned long biClrImportant;
	} BITMAPINFOHEADER;

	class Bitmap
	{
	private:
		BITMAPFILEHEADER bitmapFileHeader;
		BITMAPINFOHEADER bitmapInfoHeader;
		unsigned char* pPixelData;
		long imageWidth;
		long imageHeight;
		unsigned long pixelCount;
	public:
		bool Load(std::string argPFilename);
		unsigned char* GetPixelData();
		long GetImageWidth();
		long GetImageHeight();
		unsigned long GetPixelCount();
	};
}

#endif BITMAP_H_