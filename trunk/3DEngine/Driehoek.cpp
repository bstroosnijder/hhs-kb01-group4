#include "Driehoek.h"
#include "DirectX9Renderer.h"

namespace engine
{
// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    float x, y, z;      // The untransformed, 3D position for the vertex
    char color[8];        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

	Driehoek::Driehoek()
	{
	}


	Driehoek::~Driehoek()
	{
		this->CleanUp();
	}

	void Driehoek::CleanUp()
	{
	}

	void Driehoek::Update()
	{
	}

	void Driehoek::Draw(Renderer* argPRenderer)
	{
		DirectX9Renderer* renderer = (DirectX9Renderer*)argPRenderer;

		argPRenderer->SetStreamSource();
		argPRenderer->SetFVF();
		argPRenderer->DrawPrimitive();
	}

	void Driehoek::SetPosition(Vector3 argPosition)
	{
		this->position = argPosition;
	}

	Vector3 Driehoek::GetPosition()
	{
		return this->position;
	}
}