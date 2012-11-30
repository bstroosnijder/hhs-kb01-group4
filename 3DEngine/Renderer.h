#include "Window.h"

namespace engine
{
	/**
	 * Something about the renderer class here.
	 */
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void Clear();
		void BeginScene();
		void EndScene();
		void Present(Window* window);
	};
}