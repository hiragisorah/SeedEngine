#pragma once

#include <vector>

#include "entity.h"

namespace ECS
{
	class Engine;

	class EntityManager
	{
		friend Engine;

	private:
		EntityManager(void) {}
		~EntityManager(void) { destroyAll(); }

	private:
		std::vector<Entity*> entities_;
		
	public:
		template<class _ENTITY, class ... _ARGS>
		_ENTITY * const create(_ARGS &&... args)
		{
			auto entity = new _ENTITY(std::forward<_ARGS>(args)...);
			entities_.emplace_back(entity);
			return entity;
		}
		void destroyAll(void)
		{
			for (auto & entity : entities_)
				delete entity;

			entities_.clear();
		}
	};
}