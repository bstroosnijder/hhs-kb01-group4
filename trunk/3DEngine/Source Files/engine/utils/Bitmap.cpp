#include "..\..\..\Header Files\engine\utils\Bitmap.h"

namespace engine
{
	bool Bitmap::Load(std::string argFilename)
	{
		FILE* pFile;

		std::string fileName = "Resource Files\\Textures\\" + argFilename;

		pFile = fopen((char*)fileName.c_str(), "rb");
		if (pFile == NULL)
		{
			Logger::Log("Failed loading bitmap file: " + fileName, Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
			Logger::Log(argFilename, Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
			return false;
		}

		// Read the fileheader from the bitmap file.
		// The actual size of the info header is 14 bytes. We however cannot use sizeof(BITMAPFILEHEADER) because a struct is completed to a multiple of 4 bytes.
		// If we were to use sizeof(BITMAPFILEHEADER), the fread() function would read 16 bytes instead of 14 and we would get a padding by 2 bytes.
		fread(&this->bitmapFileHeader, 14, 1, pFile);

		// Read the infoheader from the bitmap file.
		fread(&this->bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pFile);

		if (this->bitmapFileHeader.bfType !=0x4d42)
		{
			Logger::Log("Wrong file type.", Logger::LOG_LEVEL_ERROR, __FILE__, __LINE__);
			return false;
		}

		// TODO - Gaat hier nog iets fout met de bfOffBits.....

		// Set the reading position to the beginning of the color data
		fseek(pFile, this->bitmapFileHeader.bfOffBits, SEEK_SET);

		int size = 3 * this->bitmapInfoHeader.biWidth * this->bitmapInfoHeader.biHeight;
		this->pBitmap = new unsigned char[size];

		fread(this->pBitmap, sizeof(unsigned char), size, pFile);

		fclose(pFile);

		return true;
	}

	unsigned char* Bitmap::GetBitmap()
	{
		return this->pBitmap;
	}
}