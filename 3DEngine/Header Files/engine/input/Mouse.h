#ifndef MOUSE_H_
#define MOUSE_H_

	/**
	 * This class is responsible for listening to, and handling of, mouse input.
	 * @author Alex Hodes
	 */
namespace engine
{
	class Mouse
	{
	public:
		Mouse();//HWND argHwnd );
		~Mouse();
		bool Mouse::InitMouse();
		//MouseStruct Mouse::GetMouseInput();
		bool Mouse::DoAcquire();
		void Mouse::SetMouseBuffer();
		void Mouse::SaveReleaseDevice(); 

	};
}
#endif
