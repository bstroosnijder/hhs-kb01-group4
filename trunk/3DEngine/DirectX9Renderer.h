#include "Renderer.h"
#include <d3dx9.h>

namespace engine
{
	/**
	 * The DirectX9Renderer is responsible for providing a communication gateway towards the DirectX9 API.
	 */
	class DirectX9Renderer : public Renderer
	{
		LPDirect3D9

		DirectX9Renderer();
		~DirectX9Renderer();

		void Clear();
		void BeginScene();
		void EndScene();
		void Present(Window* argWindow);
	};
}