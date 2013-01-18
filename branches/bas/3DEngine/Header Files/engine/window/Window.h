#ifndef Window_H_
#define Window_H_

#include <string>
#include "..\logger\Logger.h"

namespace engine
{
	/**
	 * This class defines an interface for a window.
	 */
	class Window
	{
	private:
		
	protected:
		std::string title;
		int x;
		int y;
		unsigned int width;
		unsigned int height;
	public:
		virtual void SetTitle(std::string argTitle)=0;
		virtual void AddTitle(std::string argAddTitle)=0;
		virtual std::string GetTitle()=0;
		virtual void SetX(int argX)=0;
		virtual int GetX()=0;
		virtual void SetY(int argY)=0;
		virtual int GetY()=0;
		virtual void SetWidth(unsigned int argWidth)=0;
		virtual unsigned int GetWidth()=0;
		virtual void SetHeight(unsigned int argHeight)=0;
		virtual unsigned int GetHeight()=0;
	};
}

#endif