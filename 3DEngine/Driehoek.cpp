#include "Driehoek.h"

namespace engine
{
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
		//argPRenderer->NewTriangle(		argPRenderer->NewVertex( 0.0f, 1.0f, 0.0f, 0xFFFF0000),
		//								argPRenderer->NewVertex(-1.0f,-1.0f, 0.0f, 0xFFFF0000),
		//								argPRenderer->NewVertex( 1.0f,-1.0f, 0.0f, 0xFFFF0000));
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