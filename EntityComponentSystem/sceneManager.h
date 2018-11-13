#pragma once

#include <unordered_map>
#include <vector>

#include "scene.h"

namespace ECS
{
	class Engine;

	class SceneManager
	{
		friend Engine;

	private:
		SceneManager(void) {};
		~SceneManager(void) {};

	private:
		std::unordered_map<std::string, std::vector<Scene*>> scenes_;

	public:
		template<class _SCENE, class ... _ARGS>
		Scene * const addScene(_ARGS &&... args)
		{
			auto scene = new _SCENE(std::forward<_ARGS>(args)...);
			scenes_["unnamed"].emplace_back(scene);
			return scene;
		}
		const std::vector<Scene*> getScenesByName(const std::string & name)
		{
			return scenes_[name];
		}
		void removeScenesByName(const std::string & name)
		{
			for (auto & scene : scenes_[name])
				delete scene;

			scenes_.erase(name);
		}
		void removeAllScenes(void)
		{
			for (auto & scenes : scenes_)
				for (auto & scene : scenes.second)
					delete scene;

			scenes_.clear();
		}
	};
}