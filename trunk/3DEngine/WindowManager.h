namespace engine
{
	/**
	 * This class manages all created windows.
	 */
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();
		void NewWindow(unsigned int argWidth, unsigned int argHeight);
	};
}