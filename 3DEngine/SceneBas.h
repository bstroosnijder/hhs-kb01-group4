#ifndef SCENEBAS_H_
#define SCENEBAS_H_

#include "Scene.h"

class SceneBas : public engine::Scene
{
public:
	SceneBas();
	~SceneBas();
	void CleanUp();

	void Update();
	void Draw(engine::Renderer* argPRenderer);
};

#endif