#pragma once
#include "../Rendering/Camera.h"
#include "Lighting/Environment.h"
#include <vector>
#include "entt/entt.hpp"

class Entity;
class Scene
{
	friend Entity;
private:
	Environment* m_Environement;
	entt::registry m_Registry;

public:
	Scene();
	~Scene();

	void Update(Timestep ts);
	void Draw();

	Entity CreateEntity(const std::string name);
	void DestroyEntity(Entity entity);
	
	Camera* GetCurrentCamera();
	Environment* GetEnvironment();
};