namespace engine
{
	class Window
	{
	public:
		Window(void);
		virtual ~Window(void);

		virtual int Show()=0;
	};
}