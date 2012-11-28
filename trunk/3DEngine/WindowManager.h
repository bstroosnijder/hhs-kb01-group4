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
		void MakeWindow(unsigned int argWidth, unsigned int argHeight);
	};
}