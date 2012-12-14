#include "SceneLeon.h"


SceneLeon::SceneLeon()
{
	//engine::Scene::Scene();

	barrel = new engine::Model("barrel.X");
	barrel->SetPosition( engine::Vector3(0.0f, 0.0f, 0.0f) );
	barrel->SetRotation( engine::Vector3(  -(M_PI/2), 0.0f, 0.0f) );
	barrel->SetScaling( engine::Vector3(0.05f, 0.05f, 0.05f) );
	this->AddModel(barrel);
}


SceneLeon::~SceneLeon()
{
	
}

void SceneLeon::Update()
{
	//engine::Vector3 position = barrel->GetPosition();
	////position.x += cos(angle / 180 * M_PI) * 0.08f;
	////position.z += sin(angle / 180 * M_PI) * 0.08f;
	//barrel->SetPosition(position);

	engine::Vector3 rotation = barrel->GetRotation();
	rotation.y -= 0.0175f;
	barrel->SetRotation(rotation);


}

void SceneLeon::Draw(engine::Renderer* argPRenderer)
{
	Scene::Draw(argPRenderer);
	//engine::Scene::Draw(argPRenderer);
}