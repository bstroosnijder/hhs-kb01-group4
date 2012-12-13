#include "SceneBas.h"

SceneBas::SceneBas()
{
	Scene::Scene();
	
	// Create an entity
	engine::Entity* entity1 = new engine::Entity("tiger.x");
	entity1->SetScaling(engine::Vector3(1.0f, 1.0f, 1.0f));
	entity1->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	entity1->SetPosition(engine::Vector3(0.0f, 0.0f, 0.0f));

	// Create an entity
	engine::Entity* entity2 = new engine::Entity("tiger.x");
	entity2->SetScaling(engine::Vector3(1.0f, 1.0f, 1.0f));
	entity2->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	entity2->SetPosition(engine::Vector3(-1.0f, 0.0f, 0.0f));

	// Create an entity
	engine::Entity* entity3 = new engine::Entity("tiger.x");
	entity3->SetScaling(engine::Vector3(.5f, .5f, .5f));
	entity3->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	entity3->SetPosition(engine::Vector3(-1.0f, 0.0f, 0.0f));
	
	// Add entities to the scene
	this->AddEntity(entity1);
	entity1->AddEntity(entity2);
	entity2->AddEntity(entity3);
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