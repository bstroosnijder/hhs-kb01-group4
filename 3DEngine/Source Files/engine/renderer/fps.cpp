#include "../../../Header Files/engine/renderer/fps.h"

namespace engine
{
	//constructs the fps object
	fps::fps()
	{
		this->frames=0;
		this->currentTime=0;
		this->lastUpdateTime=0;
		this->elapsedTime=0;
	}
	
	
	fps::~fps()
	{
	}
	/**
	 * This spams the fps count per second to the logger. Once every 1000ms
	 * @return		void
	 */
	void fps::FPScount()
	{
		frames++;
		currentTime = GetTickCount();
		elapsedTime = currentTime - lastUpdateTime;
		if (elapsedTime >=1000)
		{
			std::stringstream ss;
			ss << "Frames per Second: " << frames;
			Logger::Log(ss.str(),Logger::INFO,0,0);
			this->frames=0;
			this->elapsedTime=0;
			lastUpdateTime=currentTime;
		}

	}
	
}