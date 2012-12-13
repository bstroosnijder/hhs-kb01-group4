#include "SceneLeon.h"


SceneLeon::SceneLeon()
{
	engine::Scene::Scene();

	barrel = new engine::Entity("barrel.X");
	barrel->SetPosition( engine::Vector3(0.0f, 0.0f, 0.0f) );
	barrel->SetScaling( engine::Vector3(0.05f, 0.05f, 0.05f) );
	this->AddEntity(barrel);
}


SceneLeon::~SceneLeon()
{

}

void SceneLeon::Update()
{

}

void SceneLeon::Draw(engine::Renderer* argPRenderer)
{
	engine::Scene::Draw(argPRenderer);
}