#ifndef SCENEBUILDER_H_
#define SCENEBUILDER_H_

#include <map>
#include <vector>
#include <string>
#include "..\input\InputListener.h"
#include "..\logger\Logger.h"
#include "..\utils\explode.h"
#include "Scene.h"
#include "..\kernel\ResourceManager.h"
#include "..\renderer\Renderer.h"

namespace engine
{
	class SceneBuilder : public InputListener
	{
	private:
		std::string fileName;
		Scene* pScene;
		ResourceManager* pResourceManager;
		Renderer* pRenderer;

		std::string skyboxTexture;
		std::string heightmapBitmap;
		std::string heightmapTextures[8];

		std::map<std::string, std::string> modelMesh;
		std::map<std::string, std::map<unsigned long, std::string>> modelTextures;
		std::map<std::string, std::string> soundWavFile;

		float FloatIfStringDefault(std::string argValue, float argDefault);
	public:
		SceneBuilder(std::string argFileName, Scene* argPScene,
						ResourceManager* argPResourceManager, Renderer* argPRenderer);
		~SceneBuilder();
		void CleanUp();

		void InputEvent(std::string argBind, float argSpeed);

		void Save();
	};
}

#endif