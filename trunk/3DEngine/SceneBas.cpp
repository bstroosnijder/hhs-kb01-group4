#define _USE_MATH_DEFINES
#include <math.h>
#include "SceneBas.h"

SceneBas::SceneBas()
{
	Scene::Scene();
	this->speed = 0.05f;
	this->GetCamera()->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	this->GetCamera()->SetPosition(engine::Vector3(0.0f, 0.0f, 0.0f));
	
	// Create an entity
	tiger1 = new engine::Model("tiger.x");
	tiger1->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	tiger1->SetPosition(engine::Vector3(0.0f, 0.0f, 10.0f));

	// Create an entity
	tiger2 = new engine::Model("table_lowpoly.x");
	tiger2->SetScaling(engine::Vector3(0.5f, 0.5f, 0.5f));
	tiger2->SetRotation(engine::Vector3(0.0f, 0.0f, 0.0f));
	tiger2->SetPosition(engine::Vector3(-1.0f, 0.0f, 0.0f));

	// Create an entity
	tiger3 = new engine::Model("barrel.x");
	tiger3->SetScaling(engine::Vector3(0.04f, 0.04f, 0.04f));
	tiger3->SetRotation(engine::Vector3(0.0f, 0.0f, M_PI_2));
	tiger3->SetPosition(engine::Vector3(1.0f, 0.0f, 2.0f));
	
	// Add entities to the scene
	this->AddModel(tiger1);
	//tiger1->AddModel(tiger2);
	tiger1->AddModel(tiger3);
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
	engine::Vector3 cPos = this->GetCamera()->GetPosition();
	cPos.z += this->speed;
	this->GetCamera()->SetPosition(cPos);

	engine::Vector3 cRot = this->GetCamera()->GetRotation();
	if(cPos.z >= 10.0f)
	{
		cRot.y = (float)M_PI;
	}
	else
	{
		cRot.y = 0.0f;
	}
	this->GetCamera()->SetRotation(cRot);

	if(cPos.z >= 20 || cPos.z <= 0)
	{
		this->speed *= -1;
	}

	engine::Vector3 t1Rot = this->tiger1->GetRotation();
	t1Rot.y += (float)M_PI/360;
	//this->tiger1->SetRotation(t1Rot);
	
	engine::Vector3 t3Rot = this->tiger3->GetRotation();
	t3Rot.y += (float)M_PI/90;
	this->tiger3->SetRotation(t3Rot);

	Scene::Update();
}

void SceneBas::Draw(engine::Renderer* argPRenderer)
{
	Scene::Draw(argPRenderer);
}