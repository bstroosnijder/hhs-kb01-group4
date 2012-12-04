#ifndef Window_H_
#define Window_H_

namespace engine
{
	/**
	 * This class defines an interface for a window.
	 */
	class Window
	{
	private:
		
	protected:
		char* title;
		unsigned int x;
		unsigned int y;
		unsigned int width;
		unsigned int height;
	public:
		virtual void SetTitle(char* argTitle)=0;
		virtual char* GetTitle()=0;
		virtual void SetX(unsigned int argX)=0;
		virtual unsigned int GetX()=0;
		virtual void SetY(unsigned int argY)=0;
		virtual unsigned int GetY()=0;
		virtual void SetWidth(unsigned int argWidth)=0;
		virtual unsigned int GetWidth()=0;
		virtual void SetHeight(unsigned int argHeight)=0;
		virtual unsigned int GetHeight()=0;
	};
}

#endif