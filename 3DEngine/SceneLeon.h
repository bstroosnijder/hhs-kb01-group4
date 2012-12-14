#define _USE_MATH_DEFINES
#include <math.h>
#include "Scene.h"

class SceneLeon : public engine::Scene
{
private:
	engine::Model* barrel;
public:
	SceneLeon();
	~SceneLeon();
	void Update();
	void Draw(engine::Renderer* argPRenderer);
};