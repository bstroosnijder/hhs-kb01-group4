#include "Tiny.h"

namespace engine
{
	Tiny::Tiny()
	{
	}

	Tiny::~Tiny()
	{
		this->CleanUp();
	}

	void Tiny::CleanUp()
	{
	}
	
	void Tiny::Load(ResourceManager* argPResourceManager, Renderer* argPRenderer)
	{
		this->SetResource(argPResourceManager->LoadResource(argPRenderer, "tiny.x"));
	}

	void Tiny::Update()
	{
	}

	void Tiny::Draw(Renderer* argPRenderer)
	{
		argPRenderer->SetupMatricis();
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;

		D3DXMATRIXA16 matTranslation;
		D3DXMatrixTranslation(&matTranslation, this->position.x, this->position.y, this->position.z);
		pRenderer->AddToWorldMatrix(&matTranslation);

		Entity::Draw(argPRenderer);
	}
}