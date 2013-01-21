#ifndef SOUND_H_
#define SOUND_H_

#include <al.h>
#include <alc.h>
#include "..\Entity.h"
#include "..\..\utils\WavFile.h"

namespace engine
{
	/**
	 * Plays sounds in a 3D enviroment
	 */
	class Sound : public Entity
	{
	private:
		WavFile* pWavFile;

		ALuint source;
		ALuint buffer;
	public:
		Sound(WavFile* argPWavFile);
		~Sound();
		void CleanUp();

		void Update();
		void Draw(Renderer* argPRenderer);

		void Play();
		void Pause();
		void Stop();
	};
}

#endif