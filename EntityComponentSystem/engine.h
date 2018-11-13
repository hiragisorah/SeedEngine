#pragma once

#include "systemManager.h"
#include "componentManager.h"
#include "sceneManager.h"
#include "entityManager.h"

#include <memory>

namespace ECS
{
	class Engine final
	{
	public:
		Engine(void);
		~Engine(void);

	public:
		const bool Run(void);

	private:
		const SystemManager system_manager_;
		const ComponentManager component_manager_;
		const SceneManager scene_manager_;
		const EntityManager entity_manager_;
	};
}