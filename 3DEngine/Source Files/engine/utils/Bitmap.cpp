#include "..\..\..\Header Files\engine\utils\Bitmap.h"

namespace engine
{
	bool Bitmap::Load(std::string argFilename)
	{
		Logger::Log("Loading bitmap: " + argFilename, Logger::INFO, __FILE__, __LINE__);
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
		// Save the image width for easy access later
		this->imageWidth = this->bitmapInfoHeader.biWidth;
		
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biHeight));
		memcpy(&this->bitmapInfoHeader.biHeight, &buffer, sizeof(this->bitmapInfoHeader.biHeight));
		// Save the image height for easy access later
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

		// Calculate the total number for pixels (width * height
		this->pixelCount = this->imageWidth * this->imageHeight;

		// Create an unsigned char array using the total number of pixels
		// as the size of the array which stores the pixel data.
		this->pPixelData = new unsigned char[this->pixelCount];

		// Set the cursor at the beginnning of the offset
		inStream.seekg(this->bitmapFileHeader.bfOffBits, std::ifstream::beg);

		// calculate the padding for each pixel data row.
		int padding = (4 - (this->imageWidth * 3) % 4) % 4;
		for(long z = 0; z < this->imageHeight; z++)
		{
			for(long x = 0; x < this->imageWidth; x++)
			{
				unsigned char blue;
				char colorBuffer;
				inStream.read(&colorBuffer, 1);
				memcpy(&blue, &colorBuffer, 1);

				this->pPixelData[(z * this->bitmapInfoHeader.biWidth) + x] = blue;
			}
			// Set the cursor after the padding so we can continue reading
			inStream.seekg(padding, std::ifstream::cur);
		}

		return true;
	}

	unsigned char* Bitmap::GetPixelData()
	{
		return this->pPixelData;
	}

	long Bitmap::GetImageWidth()
	{
		return this->imageWidth;
	}

	long Bitmap::GetImageHeight()
	{
		return this->imageHeight;
	}

	unsigned long Bitmap::GetPixelCount()
	{
		return this->pixelCount;
	}
}