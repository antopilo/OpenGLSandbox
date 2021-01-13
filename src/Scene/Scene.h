#pragma once
#include "../Rendering/Camera.h"
#include "Lighting/Environment.h"
#include <vector>
#include "entt/entt.hpp"
#include "../Rendering/SkyboxHDR.h"
#include "../Rendering/GBuffer.h"

class Entity;
class Scene
{
	friend Entity;

private:
	Environment* m_Environement;
	entt::registry m_Registry;

public:

	SkyboxHDR* m_Skybox;
	Scene();
	~Scene();

	void Init();

	void Update(Timestep ts);

	void DrawShadows();
	void DrawGBuffer();
	void DrawDeferred();
	void Draw();

	std::vector<Entity> GetAllEntities();
	Entity CreateEntity(const std::string name);
	void DestroyEntity(Entity entity);
	
	Camera* GetCurrentCamera();
	Environment* GetEnvironment();
};