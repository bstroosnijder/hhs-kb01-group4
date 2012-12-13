#ifndef SCENEBAS_H_
#define SCENEBAS_H_

#include "Scene.h"

class SceneBas : public engine::Scene
{
private:
	engine::Entity* tiger1;
	engine::Entity* tiger2;
	engine::Entity* tiger3;
public:
	SceneBas();
	~SceneBas();
	void CleanUp();

	void Update();
	void Draw(engine::Renderer* argPRenderer);
};

#endif