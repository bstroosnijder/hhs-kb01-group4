
namespace engine
{
	/**
	 *	This class manages all created windows.
	*/
	class WindowManager
	{
	public:
		//---Public methods---
		WindowManager();
		~WindowManager();
		void MakeWindow(unsigned int argWidth, unsigned int argHeight);
	};
}