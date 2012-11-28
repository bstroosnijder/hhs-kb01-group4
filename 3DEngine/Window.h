namespace engine
{
	/**
	 * This class defines an interface for a window.
	 */
	class Window
	{
	public:
		Window();
		virtual ~Window();
		virtual int Show()=0;
	};
}