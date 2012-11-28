
namespace engine
{
	/**
	 *	This class defines an interface for a window.
	*/
	class Window
	{
	public:
		//---Public methods---
		Window(void);
		virtual ~Window(void);
		virtual int Show()=0;
	};
}