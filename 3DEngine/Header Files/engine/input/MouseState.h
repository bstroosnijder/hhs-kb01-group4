#ifndef MOUSESTATE_H_
#define MOUSESTATE_H_

namespace engine
{
	struct MouseState {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
		BYTE    rgbButtons[8];
	};
}

#endif