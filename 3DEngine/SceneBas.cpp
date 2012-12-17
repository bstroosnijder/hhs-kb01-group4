#define _USE_MATH_DEFINES
#include <math.h>
#include "SceneBas.h"

SceneBas::SceneBas()
{
	Scene::Scene();
	this->speed = 1.05f;
	this->GetCamera()->SetPosition(engine::Vector3(0.0f, 30.0f, 0.0f));
	this->GetCamera()->SetRotation(engine::Vector3(M_PI_2, 0.0f, 0.0f));
	
	// Create an entity5
	tiger1 = new engine::Model("tiger.x");
	tiger1->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	tiger1->SetPosition(engine::Vector3(2.0f, 0.0f, 2.0f));

	// Create an entity
	tiger3 = new engine::Model("barrel.x");
	tiger3->SetScaling(engine::Vector3(0.04f, 0.04f, 0.04f));
	tiger3->SetRotation(engine::Vector3(0.0f, 0.0f, M_PI_2));
	tiger3->SetPosition(engine::Vector3(0.0f, 0.0f, 0.0f));

	// Create an entity
	tiger4 = new engine::Model("barrel.x");
	tiger4->SetScaling(engine::Vector3(0.04f, 0.04f, 0.04f));
	tiger4->SetRotation(engine::Vector3(0.0f, 0.0f, M_PI_2));
	tiger4->SetPosition(engine::Vector3(4.0f, 0.0f, 0.0f));
	
	// Add entities to the scene
	this->AddModel(tiger1);
	this->AddModel(tiger3);
	this->AddModel(tiger4);
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
	engine::Vector3 tRot = this->tiger1->GetRotation();
	tRot.y -= M_PI/360;
	this->tiger1->SetRotation(tRot);

	engine::Vector3 tPos = this->tiger1->GetPosition();
	tPos.x -= sin(tRot.y) * this->speed;
	tPos.z -= cos(tRot.y) * this->speed;
	this->tiger1->SetPosition(tPos);



	engine::Vector3 cRot = this->GetCamera()->GetRotation();
	cRot.x = tRot.x;
	cRot.y = tRot.y + M_PI;
	cRot.z = tRot.z;
	this->GetCamera()->SetRotation(cRot);

	engine::Vector3 cPos = this->GetCamera()->GetPosition();
	cPos.x = tPos.x + (sin(tRot.y) * 10);
	cPos.y = tPos.y + 2;
	cPos.z = tPos.z + (cos(tRot.y) * 10);
	this->GetCamera()->SetPosition(cPos);

	Scene::Update();
}

void SceneBas::Draw(engine::Renderer* argPRenderer)
{
	Scene::Draw(argPRenderer);
}