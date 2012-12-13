#include "Scene.h"
#include "Renderer.h"

#ifndef SCENEALEX_H_
#define SCENEALEX_H_


class SceneAlex : public engine::Scene
{
public:
	SceneAlex();
	~SceneAlex();
	void Draw(engine::Renderer* argPRenderer);
	void Update();
};
#endif

