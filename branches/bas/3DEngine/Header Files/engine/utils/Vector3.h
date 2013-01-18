#ifndef VECTOR3_H_
#define VECTOR3_H_

namespace engine
{
	/**
	 * Struct for the containment of x, y and z values
	 */
	struct Vector3
	{
		float x;
		float y;
		float z;
		Vector3() : x(0), y(0), z(0){}
		Vector3(float x, float y, float z) : x(x), y(y), z(z){}
	};
}

#endif