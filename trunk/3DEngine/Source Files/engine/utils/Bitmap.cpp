#include "..\..\..\Header Files\engine\utils\Bitmap.h"

namespace engine
{
	bool Bitmap::Load(std::string argFilename)
	{
		Logger::Log("Loading bitmap: " + argFilename, Logger::LOG_LEVEL_INFO, __FILE__, __LINE__);
		std::string fileName ("Resource Files\\Textures\\" + argFilename);
		std::ifstream inStream (fileName);
		char buffer[sizeof(unsigned long)];

		// --- READ FILE HEADER ---
		// Read the BMP type bytes
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfType));
		memcpy(&this->bitmapFileHeader.bfType, &buffer, sizeof(this->bitmapFileHeader.bfType));

		// Read the file size bytes
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfSize));
		memcpy(&this->bitmapFileHeader.bfSize, &buffer, sizeof(this->bitmapFileHeader.bfSize));

		// Read the first reserved bytes
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfReserved1));
		memcpy(&this->bitmapFileHeader.bfReserved1, &buffer, sizeof(this->bitmapFileHeader.bfReserved1));
		
		// Read the second reserved bytes
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfReserved2));
		memcpy(&this->bitmapFileHeader.bfReserved2, &buffer, sizeof(this->bitmapFileHeader.bfReserved2));
		
		// Read the offset where the pixel data starts
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfOffBits));
		memcpy(&this->bitmapFileHeader.bfOffBits, &buffer, sizeof(this->bitmapFileHeader.bfOffBits));


		// --- READ INFO HEADER ---
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biSize));
		memcpy(&this->bitmapInfoHeader.biSize, &buffer, sizeof(this->bitmapInfoHeader.biSize));
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biWidth));
		memcpy(&this->bitmapInfoHeader.biWidth, &buffer, sizeof(this->bitmapInfoHeader.biWidth));
		this->imageWidth = this->bitmapInfoHeader.biWidth;
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biHeight));
		memcpy(&this->bitmapInfoHeader.biHeight, &buffer, sizeof(this->bitmapInfoHeader.biHeight));
		this->imageHeight = this->bitmapInfoHeader.biHeight;
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biPlanes));
		memcpy(&this->bitmapInfoHeader.biPlanes, &buffer, sizeof(this->bitmapInfoHeader.biPlanes));
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biBitCount));
		memcpy(&this->bitmapInfoHeader.biBitCount, &buffer, sizeof(this->bitmapInfoHeader.biBitCount));
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biCompression));
		memcpy(&this->bitmapInfoHeader.biCompression, &buffer, sizeof(this->bitmapInfoHeader.biCompression));
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biSizeImage));
		memcpy(&this->bitmapInfoHeader.biSizeImage, &buffer, sizeof(this->bitmapInfoHeader.biSizeImage));
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biXPelsPerMeter));
		memcpy(&this->bitmapInfoHeader.biXPelsPerMeter, &buffer, sizeof(this->bitmapInfoHeader.biXPelsPerMeter));
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biYPelsPerMeter));
		memcpy(&this->bitmapInfoHeader.biYPelsPerMeter, &buffer, sizeof(this->bitmapInfoHeader.biYPelsPerMeter));
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biClrUsed));
		memcpy(&this->bitmapInfoHeader.biClrUsed, &buffer, sizeof(this->bitmapInfoHeader.biClrUsed));
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biClrImportant));
		memcpy(&this->bitmapInfoHeader.biClrImportant, &buffer, sizeof(this->bitmapInfoHeader.biClrImportant));

		// Create an unsigned char array using the image width times images height as the size of the array which stores the pixel data.		
		pixelCount = this->bitmapInfoHeader.biWidth * this->bitmapInfoHeader.biHeight;
		this->pPixelData = new unsigned char[pixelCount];

		inStream.seekg(this->bitmapFileHeader.bfOffBits, std::ifstream::beg);

		//for (unsigned long i = 0; i < pixelCount; i++)
		//{
		//	// We are using a grayscale image, the red, blue and green color channels have the same value.
		//	unsigned char blue;
		//	char colorBuffer;
		//	inStream.read(&colorBuffer, 1);
		//	inStream.seekg(3, std::ifstream::cur);
		//	memcpy(&blue, &colorBuffer, 1);

		//	this->pPixelData[i] = blue;
		//}

		int padding = (4 - (this->bitmapInfoHeader.biWidth * 3) % 4) % 4;
		for(unsigned long z = 0; z < this->bitmapInfoHeader.biHeight; z++)
		{
			for(unsigned long x = 0; x < this->bitmapInfoHeader.biWidth; x++)
			{
				unsigned char blue;
				char colorBuffer;
				inStream.read(&colorBuffer, 1);
				memcpy(&blue, &colorBuffer, 1);

				this->pPixelData[(z * this->bitmapInfoHeader.biWidth) + x] = blue;
			}
			inStream.seekg(padding, std::ifstream::cur);
		}

		return true;
	}

	unsigned char* Bitmap::GetPixelData()
	{
		return this->pPixelData;
	}

	unsigned long Bitmap::GetImageWidth()
	{
		return this->imageWidth;
	}

	unsigned long Bitmap::GetImageHeight()
	{
		return this->imageHeight;
	}

	unsigned long Bitmap::GetPixelCount()
	{
		return this->pixelCount;
	}
}