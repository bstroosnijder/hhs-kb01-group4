#ifndef WAVFILE_H_
#define WAVFILE_H_

#include <string>
#include <fstream>
#include <al.h>
#include <alc.h>
#include "..\logger\Logger.h"

namespace engine
{
	struct WavChunkDescription {
		// Type of the file
		char type[4];
		// Size of the file
		unsigned long size;
		// Wave Description Header
		char desc[4];
		
		// Format Description Header
		char format[4];
		// Size of the section chunk size
		unsigned long chunkSize;
		// Wave type format
		unsigned short typeFormat;
		// Number for channels
		unsigned short channels;
		// Samples per second
		unsigned long samplePerSec;
		// Bytes per second
		unsigned long bytesPerSec;
		// Block alignment
		unsigned short alignment;
		// Bits per sample
		unsigned short bitsPerSample;
	};

	struct WavDataChunkDescription {
		// Data Description Header
		char type[4];
		// Size of data
		unsigned long size;
	};

	/**
	 * The WavFile load a wav file. derp! :D
	 */
	class WavFile
	{
	private:
		WavChunkDescription wavHeader;

		unsigned long bufferSize;
		void* buffer;

		ALuint frecuency;
		ALuint format;
	public:
		WavFile(std::string argFileName);
		~WavFile();
		void CleanUp();

		unsigned long GetBufferSize();
		void* GetBuffer();

		ALuint GetFrecuency();
		ALuint GetFormat();
	};
}

#endif