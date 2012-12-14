#include "SceneBas.h"

SceneBas::SceneBas()
{
	Scene::Scene();
	
	// Create an entity
	tiger1 = new engine::Entity("tiger.x");
	tiger1->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	tiger1->SetPosition(engine::Vector3(0.0f, 0.0f, 0.0f));

	// Create an entity
	tiger2 = new engine::Entity("table_lowpoly.x");
	tiger2->SetScaling(engine::Vector3(0.5f, 0.5f, 0.5f));
	tiger2->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	tiger2->SetPosition(engine::Vector3(-1.0f, 0.0f, 0.0f));

	// Create an entity
	tiger3 = new engine::Entity("tiger.x");
	tiger3->SetScaling(engine::Vector3(0.5f, 0.5f, 0.5f));
	tiger3->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	tiger3->SetPosition(engine::Vector3(-1.0f, 0.0f, 0.0f));
	
	// Add entities to the scene
	this->AddEntity(tiger1);
	tiger1->AddEntity(tiger2);
	tiger2->AddEntity(tiger3);
}


SceneBas::~SceneBas()
{
	this->CleanUp();
}

void SceneBas::CleanUp()
{
}

void SceneBas::Update()
{


	Scene::Update();
}

void SceneBas::Draw(engine::Renderer* argPRenderer)
{
	Scene::Draw(argPRenderer);
}