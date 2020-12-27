#pragma once
#include "../Rendering/Camera.h"
#include "Entities/QuadEntity.h"
#include "Lighting/Environment.h"
class Scene
{
private:
	Camera* m_Camera;
	Environment* m_Environement;
public:
	Scene();
	~Scene();

	void Update(Timestep ts);
	void Draw();
	QuadEntity* m_Entity;
	Camera* GetCurrentCamera();
	Environment* GetEnvironment();
	
};