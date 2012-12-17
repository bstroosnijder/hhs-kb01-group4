#ifndef SCENEBAS_H_
#define SCENEBAS_H_

#include "Scene.h"
#include "Model.h"

class SceneBas : public engine::Scene
{
private:
	engine::Model* tiger1;
	engine::Model* tiger2;
	engine::Model* tiger3;
	engine::Model* tiger4;
	float speed;
public:
	SceneBas();
	~SceneBas();
	void CleanUp();

	void Update();
	void Draw(engine::Renderer* argPRenderer);
};

#endif