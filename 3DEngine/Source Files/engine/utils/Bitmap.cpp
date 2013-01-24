#include "..\..\..\Header Files\engine\utils\Bitmap.h"

namespace engine
{
	/**
	 * Load bitmap pixel- and headerdata into chunks that our engine can understand and interpret.
	 * @param	std::string		The file name of the bitmap that should be loaded.
	 * @return	bool			Whether the load was successful or not.
	 */
	bool Bitmap::Load(std::string argFilename)
	{
		Logger::Log("Loading bitmap: " + argFilename, Logger::INFO, __FILE__, __LINE__);
		std::string fileName ("Resource Files\\Textures\\" + argFilename);
		std::ifstream inStream (fileName);
		char buffer[sizeof(unsigned long)];

		// --- READ FILE HEADER ---
		// Read the BMP type
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfType));
		memcpy(&this->bitmapFileHeader.bfType, &buffer, sizeof(this->bitmapFileHeader.bfType));

		// Read the file size
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfSize));
		memcpy(&this->bitmapFileHeader.bfSize, &buffer, sizeof(this->bitmapFileHeader.bfSize));

		// Read the first reserved
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfReserved1));
		memcpy(&this->bitmapFileHeader.bfReserved1, &buffer, sizeof(this->bitmapFileHeader.bfReserved1));
		
		// Read the second reserved
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfReserved2));
		memcpy(&this->bitmapFileHeader.bfReserved2, &buffer, sizeof(this->bitmapFileHeader.bfReserved2));
		
		// Read the offset where the pixel data starts
		inStream.read(buffer, sizeof(this->bitmapFileHeader.bfOffBits));
		memcpy(&this->bitmapFileHeader.bfOffBits, &buffer, sizeof(this->bitmapFileHeader.bfOffBits));


		// --- READ INFO HEADER ---
		// Reads the size of the info header
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biSize));
		memcpy(&this->bitmapInfoHeader.biSize, &buffer, sizeof(this->bitmapInfoHeader.biSize));
		
		// Read the width in pixels
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biWidth));
		memcpy(&this->bitmapInfoHeader.biWidth, &buffer, sizeof(this->bitmapInfoHeader.biWidth));
		// Save the image width for easy access later
		this->imageWidth = this->bitmapInfoHeader.biWidth;
		
		// Read the height in pixels
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biHeight));
		memcpy(&this->bitmapInfoHeader.biHeight, &buffer, sizeof(this->bitmapInfoHeader.biHeight));
		// Save the image height for easy access later
		this->imageHeight = this->bitmapInfoHeader.biHeight;
		
		// Read how many planes are in the image
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biPlanes));
		memcpy(&this->bitmapInfoHeader.biPlanes, &buffer, sizeof(this->bitmapInfoHeader.biPlanes));
		
		// Read how many bits per pixel this image has
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biBitCount));
		memcpy(&this->bitmapInfoHeader.biBitCount, &buffer, sizeof(this->bitmapInfoHeader.biBitCount));
		
		// Read what kind of compression is used
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biCompression));
		memcpy(&this->bitmapInfoHeader.biCompression, &buffer, sizeof(this->bitmapInfoHeader.biCompression));
		
		// Read the size of the image
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biSizeImage));
		memcpy(&this->bitmapInfoHeader.biSizeImage, &buffer, sizeof(this->bitmapInfoHeader.biSizeImage));
		
		// Read how many pixels per meter over the X axis
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biXPelsPerMeter));
		memcpy(&this->bitmapInfoHeader.biXPelsPerMeter, &buffer, sizeof(this->bitmapInfoHeader.biXPelsPerMeter));
		
		// Read how many pixels per meter over the Y axis
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biYPelsPerMeter));
		memcpy(&this->bitmapInfoHeader.biYPelsPerMeter, &buffer, sizeof(this->bitmapInfoHeader.biYPelsPerMeter));
		
		// Reads what colors are in the color table
		inStream.read(buffer, sizeof(this->bitmapInfoHeader.biClrUsed));
		memcpy(&this->bitmapInfoHeader.biClrUsed, &buffer, sizeof(this->bitmapInfoHeader.biClrUsed));
		
		// Reads the count of important colors
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
				char colorBuffer;
				unsigned int color	= 0;
				unsigned char red	= 0;
				unsigned char green	= 0;
				unsigned char blue	= 0;

				// Read and save the red color
				inStream.read(&colorBuffer, 1);
				memcpy(&red, &colorBuffer, 1);
				color += red;

				// skip 2 byte for 24 bit bmp
				if(this->bitmapInfoHeader.biBitCount == 24)
				{
					// Read and save the green color
					inStream.read(&colorBuffer, 1);
					memcpy(&green, &colorBuffer, 1);

					// Read and save the blue color
					inStream.read(&colorBuffer, 1);
					memcpy(&blue, &colorBuffer, 1);
				}

				this->pPixelData[(z * this->bitmapInfoHeader.biWidth) + x] = (unsigned char)color;
			}
			// Set the cursor after the padding so we can continue reading
			inStream.seekg(padding, std::ifstream::cur);
		}

		return true;
	}

	/**
	 * Gets the pixel data
	 * @return		char*
	 */
	unsigned char* Bitmap::GetPixelData()
	{
		return this->pPixelData;
	}

	/**
	 * Gets the image width
	 * @return		long
	 */
	long Bitmap::GetImageWidth()
	{
		return this->imageWidth;
	}

	/**
	 * Gets the image height
	 * @return		long
	 */
	long Bitmap::GetImageHeight()
	{
		return this->imageHeight;
	}

	/**
	 * Gets the total pixel count
	 * @return		unsigned long
	 */
	unsigned long Bitmap::GetPixelCount()
	{
		return this->pixelCount;
	}
}