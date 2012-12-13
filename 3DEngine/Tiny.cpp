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
		Entity::Load(argPResourceManager, argPRenderer);
	}

	void Tiny::Update()
	{
		Entity::Update();
	}

	void Tiny::Draw(Renderer* argPRenderer)
	{
		DirectX9Renderer* pRenderer = (DirectX9Renderer*)argPRenderer;


		// Scaling
		D3DXMATRIXA16 matScaling;
		D3DXMatrixScaling(&matScaling, this->scaling.x, this->scaling.y, this->scaling.z);
		pRenderer->AddToWorldMatrix(&matScaling);
		
		// Rotation X
		D3DXMATRIXA16 matRotationX;
		D3DXMatrixRotationX(&matRotationX, this->rotation.x);
		pRenderer->AddToWorldMatrix(&matRotationX);
		// Rotation Y
		D3DXMATRIXA16 matRotationY;
		D3DXMatrixRotationY(&matRotationY, this->rotation.y);
		pRenderer->AddToWorldMatrix(&matRotationY);
		// Rotation Z
		D3DXMATRIXA16 matRotationZ;
		D3DXMatrixRotationZ(&matRotationZ, this->rotation.z);
		pRenderer->AddToWorldMatrix(&matRotationZ);

		// Position
		D3DXMATRIXA16 matPosition;
		D3DXMatrixTranslation(&matPosition, this->position.x, this->position.y, this->position.z);
		pRenderer->AddToWorldMatrix(&matPosition);


		// Call the parent draw to make sure the image is actually drawed
		Entity::Draw(argPRenderer);
	}
}