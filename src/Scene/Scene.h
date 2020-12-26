#pragma once
#include "../Rendering/Camera.h"
#include "Entities/QuadEntity.h"
class Scene
{
private:
	Camera* m_Camera;
	QuadEntity* m_Entity;

public:
	Scene();
	~Scene();

	void Update(Timestep ts);

	Camera* GetCurrentCamera();

	void Draw();
};