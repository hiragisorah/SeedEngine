#pragma once

#include <typeindex>
#include <unordered_map>

#include "component.h"
#include "entity.h"

namespace ECS
{
	class Engine;

	class ComponentManager
	{
		friend Engine;

	private:
		ComponentManager(void) {};
		~ComponentManager(void) { removeAllComponents(); };

	private:
		std::unordered_map<std::type_index, std::unordered_map<Entity*, Component*>> components_;

	public:
		template<class _COMPONENT, class ... _ARGS>
		_COMPONENT * const addComponent(Entity * const entity, _ARGS &&... args)
		{
			auto component = new _COMPONENT(std::forward<_ARGS>(args)...);
			components_[typeid(_COMPONENT)][entity] = component;
			return component;
		}
		template<class _COMPONENT>
		_COMPONENT * const getComponent(Entity * const entity)
		{
			auto component = components_[typeid(_COMPONENT)][entity];
			return static_cast<_COMPONENT*>(component);
		}
		template<class _COMPONENT>
		std::unordered_map<Entity*, Component* > getComponents(void)
		{
			return components_[typeid(_COMPONENT)];
		}
		template<class _COMPONENT>
		void removeComponent(Entity * const entity)
		{
			delete components_[typeid(_COMPONENT)];
			components_[typeid(_COMPONENT)].erase(entity);
		}
		template<class _COMPONENT>
		void removeComponents(void)
		{
			for (auto & component : components_[typeid(_COMPONENT)])
				delete component;

			components_.erase(typeid(_COMPONENT));
		}
		void removeAllComponents(void)
		{
			for (auto & components : components_)
				for (auto & component : components.second)
					delete component.second;

			components_.clear();
		}
	};
}