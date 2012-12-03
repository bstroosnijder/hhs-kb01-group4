#include "entity.h"
namespace engine
	/**
	 * The camera class is the camera where we will see trought
	 * @author Alex Hodes
	 */
{
	class Camera : public Entity
	{
	public:
		Camera();
		Camera(int argX, int argY, int argZ,
				int argLookAtX, int argLookAtY, int argLookAtZ,
				int argUpVecX,int argUpVecY,int argUpVecZ);
		~Camera();
		void Draw(Renderer* argPRenderer);
		void Update();
	private:
		int x;
		int y;
		int z;
		int lookAtX;
		int lookAtY;
		int lookAtZ;
		int upVecX;
		int upVecY;
		int upVecZ;
	};
}

