#pragma once
#include "../Rendering/Camera.h"
#include "Lighting/Environment.h"
#include <vector>
#include "entt/entt.hpp"
#include "../Rendering/Skybox.h"

class Entity;
class Scene
{
	friend Entity;
private:
	Environment* m_Environement;
	entt::registry m_Registry;

	Skybox* m_Skybox;

public:
	Scene();
	~Scene();

	void Update(Timestep ts);
	void Draw();

	std::vector<Entity> GetAllEntities();
	Entity CreateEntity(const std::string name);
	void DestroyEntity(Entity entity);
	
	Camera* GetCurrentCamera();
	Environment* GetEnvironment();
};