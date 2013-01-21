#ifndef FPS_H_
#define FPS_H_
#include "../logger/Logger.h"
#include <Windows.h>
namespace engine
{
	/**
	 * This class is responsible for show the fps in the logger 
	 */
	class fps
	{
	private:
		unsigned long frames;
		unsigned long currentTime;
		unsigned long lastUpdateTime;
		unsigned long elapsedTime;

	public:
		fps();
		~fps();
		void FPScount();
	};
}
#endif

