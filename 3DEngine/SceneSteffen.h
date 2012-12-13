#ifndef SCENESTEFFEN_H_
#define SCENESTEFFEN_H_

#include "Scene.h"

class SceneSteffen : public engine::Scene
{
public:
	SceneSteffen();
	~SceneSteffen();
	void CleanUp();

	void Update();
	void Draw(engine::Renderer* argPRenderer);
};

#endif