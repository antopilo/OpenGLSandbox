#pragma once
#include <string>
#include <glm\ext\matrix_float4x4.hpp>
#include "../Scene.h"

class Entity 
{
public:
	Entity(entt::entity handle, Scene* scene);

	template<typename T>
	bool HasComponent() {
		return m_Scene->m_Registry.has<T>(m_EntityHandle);
	}

	template<typename T>
	void AddComponent() {
		m_Scene->m_Registry.emplace<T>(m_EntityHandle);
	}

private:
	entt::entity m_EntityHandle;
	Scene* m_Scene;
};