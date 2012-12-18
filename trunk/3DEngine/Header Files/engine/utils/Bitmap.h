#ifndef BITMAP_H_
#define BITMAP_H_

#include <iostream>
#include <fstream>
#include <windows.h>
#include <ios>
#include "..\logger\Logger.h"

namespace engine
{
	typedef struct tagBITMAPFILEHEADER {
	  WORD  bfType;
	  DWORD bfSize;
	  WORD  bfReserved1;
	  WORD  bfReserved2;
	  DWORD bfOffBits;
	} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

	typedef struct tagBITMAPINFOHEADER {
		DWORD biSize;
		LONG  biWidth;
		LONG  biHeight;
		WORD  biPlanes;
		WORD  biBitCount;
		DWORD biCompression;
		DWORD biSizeImage;
		LONG  biXPelsPerMeter;
		LONG  biYPelsPerMeter;
		DWORD biClrUsed;
		DWORD biClrImportant;
	} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

	class Bitmap
	{
	private:
		BITMAPFILEHEADER bitmapFileHeader;
		BITMAPINFOHEADER bitmapInfoHeader;
		unsigned char* pBitmap;
	public:
		bool Load(std::string argPFilename);
		unsigned char* GetBitmap();
	};
}

#endif BITMAP_H_