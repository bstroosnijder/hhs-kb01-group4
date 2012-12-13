#include "SceneSteffen.h"

SceneSteffen::SceneSteffen()
{
	Scene::Scene();
}


SceneSteffen::~SceneSteffen()
{
	this->CleanUp();
}

void SceneSteffen::CleanUp()
{
}

void SceneSteffen::Update()
{
	Scene::Update();
}

void SceneSteffen::Draw(engine::Renderer* argPRenderer)
{
	Scene::Draw(argPRenderer);
}