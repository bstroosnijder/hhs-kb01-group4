#include "..\..\..\Header Files\engine\renderer\Renderer.h"

namespace engine
{
	//---Private attributes---
	//---Public attributes---

	const unsigned int Renderer::DIRECTX_9 = 0;
	const unsigned int Renderer::OPEN_GL = 1;

	//---Private methods---
	//---Public methods---

	/**
	 * Construct the DirectX9Renderer object.
	 */
	Renderer::Renderer()
	{
		Logger::Log("Renderer: Initializing", Logger::INFO, __FILE__, __LINE__);

		this->pALDevice		= alcOpenDevice(NULL);
		this->pALContext	= alcCreateContext(this->pALDevice, NULL);
		alcMakeContextCurrent(this->pALContext);

		Logger::Log("Renderer: Finished", Logger::INFO, __FILE__, __LINE__);
	}

	/**
	 * Destructs the DirectX9Renderer object.
	 */
	Renderer::~Renderer()
	{
		Logger::Log("Renderer: Disposing", Logger::INFO, __FILE__, __LINE__);
		this->CleanUp();
	}

	/**
	 * Lazy cleanup method for destructing
	 * @return		void
	 */
	void Renderer::CleanUp()
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(this->pALContext);
		alcCloseDevice(this->pALDevice);
	}
}