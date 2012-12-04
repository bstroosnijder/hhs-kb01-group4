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