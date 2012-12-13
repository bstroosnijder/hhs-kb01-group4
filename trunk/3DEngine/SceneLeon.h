#include "Scene.h"

class SceneLeon : public engine::Scene
{
private:
	engine::Entity* barrel;
public:
	SceneLeon(void);
	~SceneLeon(void);
	void Update();
	void Draw(engine::Renderer* argPRenderer);
};