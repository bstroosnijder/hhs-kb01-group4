#ifndef KEYBOARD_H_
#define KEYBOARD_H_


	/**
	 * This class is responsible for listening to, and handling of, keyboard input.
	 * @author Alex Hodes
	 */
namespace engine
{
	class Keyboard
	{
	public:
		Keyboard();//TODO
		~Keyboard();//TODO
		//Keyboard::Keyboard(); //HWND argHwnd );//TODO HWND needed to set coop level within the initkeyB
		bool Keyboard::InitKeyboard(); //TODO //was eerst een bool
		void Keyboard::SaveReleaseDevice();//TODO 
		bool Keyboard::DoAcquire();//todo
	};
}
#endif

