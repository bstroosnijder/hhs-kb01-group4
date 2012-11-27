#ifndef KERNEL_H_
#define KERNEL_H_

#include "stdlib.h"
#include "WindowManager.h"
#include "Logger.h"
#include "TextLog.h"
#include "ConsoleLog.h" 
#include "SceneManager.h"

namespace engine {  
	class Kernel
	{
	private:
		//Private attributes
		Logger logger;

		//Private methods
		Logger GetLogger(void);
	public:
		Kernel(void);
		~Kernel(void);
	};
}

#endif

