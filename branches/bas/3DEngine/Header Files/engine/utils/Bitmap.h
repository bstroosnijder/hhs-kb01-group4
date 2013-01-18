#ifndef BITMAP_H_
#define BITMAP_H_

#include <fstream>
#include "..\logger\Logger.h"

namespace engine
{
	/**
	 * The BITMAPFILEHEADER structure contains information about the type, size, and layout of a file that contains a DIB.
	 */
	typedef struct tagBITMAPFILEHEADER {
		unsigned short bfType;
		unsigned long bfSize;
		unsigned short  bfReserved1;
		unsigned short  bfReserved2;
		unsigned long bfOffBits;
	} BITMAPFILEHEADER;

	/**
	 * The BITMAPINFOHEADER structure contains information about the dimensions and color format of a DIB.
	 */
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

	/**
	 * Reads the pixel data from a bit map and makes it usable for the engine
	 */
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