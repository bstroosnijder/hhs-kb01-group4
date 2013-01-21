#include "..\..\..\..\Header Files\engine\scene\entities\Sound.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---
	//---Private methods---
	//---Public methods---

	/**
	 * Construct the Sound object.
	 */
	Sound::Sound(WavFile* argPWavFile) : Entity(Entity::SOUND)
	{
		Logger::Log("Sound: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->pWavFile = argPWavFile;


		alGenSources(1, &this->source);
		alGenBuffers(1, &this->buffer);
		alBufferData(this->buffer, this->pWavFile->GetFormat(), this->pWavFile->GetBuffer(), this->pWavFile->GetBufferSize(), this->pWavFile->GetFrecuency());

		Logger::Log("Sound: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the Light Point object.
	 */
	Sound::~Sound()
	{
		Logger::Log("Sound: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void Sound::CleanUp()
	{
	}

	/**
	 * Default implementation of the Update method for all entities
	 * @return		void
	 */
	void Sound::Update()
	{
		Entity::Update();

		ALenum state;
		alGetSourcei(this->source, AL_SOURCE_STATE, &state);
		if(!(state == AL_PLAYING))
		{
			this->Play();
		}
	}

	/**
	 * Draw the model
	 * @param		Renderer*			The renderer to use.
	 * @return		void
	 */
	void Sound::Draw(Renderer* argPRenderer)
	{
		Entity::Draw(argPRenderer);
		
		D3DXVECTOR3 vecScale;
		D3DXQUATERNION quadRot;
		D3DXVECTOR3 vecPos;
		D3DXMatrixDecompose(&vecScale, &quadRot, &vecPos, (D3DXMATRIXA16*)argPRenderer->GetWorldTop());

		// Set the source of the sound
		alSourcei (this->source, AL_BUFFER, this->buffer);
		alSourcef (this->source, AL_PITCH, 1.0f);
		alSourcef (this->source, AL_GAIN, 1.0f);
		ALfloat alPos[]		= { vecPos.x, vecPos.y, vecPos.z };
		alSourcefv(this->source, AL_POSITION, alPos);
		ALfloat alVel[]		= { this->speed.x, this->speed.y, this->speed.z };
		alSourcefv(this->source, AL_VELOCITY, alVel);
		alSourcei (this->source, AL_LOOPING, AL_FALSE);
	}

	/**
	 * Plays the sound from the start
	 * @return		void
	 */
	void Sound::Play()
	{
		alSourcePlay(this->source);
	}

	/**
	 * Pauses the sound
	 * @return		void
	 */
	void Sound::Pause()
	{
		alSourcePause(this->source);
	}

	/**
	 * Stops the sound
	 * @return		void
	 */
	void Sound::Stop()
	{
		alSourceStop(this->source);
	}
}