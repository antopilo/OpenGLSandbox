#pragma once
#include "Scene.h"

Scene::Scene()
{
	m_Camera = new Camera(PERSPECTIVE, glm::vec3(0, 0, -2));
	m_Entity = new QuadEntity();
}

Scene::~Scene() {
	delete m_Camera;
}

void Scene::Update(Timestep ts)
{
	m_Camera->Update(ts);
}

void Scene::Draw()
{
	m_Entity->Draw(m_Camera->GetPerspective(), m_Camera->GetTransform());
}
