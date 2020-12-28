#pragma once
#include "../Rendering/Camera.h"
#include "Entities/QuadEntity.h"
#include "Lighting/Environment.h"
#include <vector>
#include "entt/entt.hpp"
class Entity;
class Scene
{
	friend Entity;
private:
	Camera* m_Camera;
	Environment* m_Environement;
	std::vector<QuadEntity*> m_Entities;
	entt::registry m_Registry;

public:
	Scene();
	~Scene();

	void Update(Timestep ts);
	Entity CreateEntity();
	void Draw();

	void AddEntity();

	void RemoveEntity(int i);

	int GetEntityCount();
	QuadEntity* GetEntity(int i);
	QuadEntity* m_Entity;

	Camera* GetCurrentCamera();
	Environment* GetEnvironment();
};