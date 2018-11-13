#pragma once

#include <memory>
#include <typeindex>
#include <unordered_map>

#include "system.h"

namespace ECS
{
	class Engine;

	class SystemManager
	{
		friend Engine;

	private:
		SystemManager(void) {};
		~SystemManager(void) {};

	private:
		std::unordered_map<std::type_index, System*> system_map_;

	public:
		template<class _SYSTEM>
		_SYSTEM * const getSystem(void)
		{
			return static_cast<_SYSTEM*>(system_map_[typeid(_SYSTEM)]);
		}
		template<class _SYSTEM, class ... _ARGS>
		_SYSTEM * const addSystem(_ARGS &&... args)
		{
			auto system = new _SYSTEM(std::forward<_ARGS>(args)...);
			return static_cast<_SYSTEM*>(system);
		}
		template<class _SYSTEM>
		void removeSystem(void)
		{
			delete system_map_[typeid(_SYSTEM)];
			system_map_.erase(typeid(_SYSTEM));
		}
	};
}