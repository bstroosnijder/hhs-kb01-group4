#include <vector>
#include "Scene.h"

namespace engine
{
	class SceneManager
	{
	private:
		//---Private attributes---
		std::vector<Scene*> scenes;

	public:
		//---Public methods---
		SceneManager();
		~SceneManager();

		void AddScene(Scene* scene);
		void RemoveScene(Scene* scene);
		Scene* GetScene(int index);
		std::vector<Scene*> GetScenes();
	};
}

