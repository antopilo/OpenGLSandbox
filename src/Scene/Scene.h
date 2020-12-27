#pragma once
#include "../Rendering/Camera.h"
#include "Entities/QuadEntity.h"
#include "Lighting/Environment.h"
class Scene
{
private:
	Camera* m_Camera;
	QuadEntity* m_Entity;
	Environment* m_Environement;
public:
	Scene();
	~Scene();

	void Update(Timestep ts);
	void Draw();

	Camera* GetCurrentCamera();
	Environment* GetEnvironment();
	
};