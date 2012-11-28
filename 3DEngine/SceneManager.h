#include <vector>
#include "Scene.h"

namespace engine
{
	/**
	 * The SceneManager is responsible for all the scenes that the engine contains or will contain.
	 */
	class SceneManager
	{
	private:
		std::vector<Scene*> scenes;
	public:
		SceneManager();
		~SceneManager();

		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);
		Scene* GetScene(int index);
		std::vector<Scene*> GetScenes();
	};
}

