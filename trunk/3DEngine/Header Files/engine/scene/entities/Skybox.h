#ifndef SKYBOX_H_
#define SKYBOX_H_

#include <d3dx9.h>
#include "..\..\logger\Logger.h"
#include "..\Entity.h"
#include "..\..\renderer\DirectX9Renderer.h"
#include "..\..\utils\TexturedVector3.h"

namespace engine
{
	/**
	 * The Skybox is the entity that fills the outer sides of the 3D world.
	 * The "Walls", "Ceiling" and "Floor" that confine the 3D world are set up by this entity.	
	 */
	class Skybox : public Entity
	{
	private:
		LPDIRECT3DTEXTURE9 textures[8];
		LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
		LPDIRECT3DINDEXBUFFER9 pIndexBuffer;
	public:
		Skybox();
		~Skybox();
		void CleanUp();

		void SetupVertices(Renderer* argPRenderer);

		void Update();
		void Draw(Renderer* argPRenderer);

		void SetTexture(unsigned long argIndex, LPDIRECT3DTEXTURE9 argTexture);
	};
}

#endif