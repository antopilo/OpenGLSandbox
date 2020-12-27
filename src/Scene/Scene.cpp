#pragma once
#include "Scene.h"

Scene::Scene()
{
	m_Camera = new Camera(PERSPECTIVE, glm::vec3(-1, 0, -1));
	m_Environement = new Environment();
	m_Entity = new QuadEntity(this);
}

Scene::~Scene() {
	delete m_Camera;
	delete m_Entity;
	delete m_Environement;
}

void Scene::Update(Timestep ts)
{
	m_Camera->Update(ts);
}

void Scene::Draw()
{
	m_Entity->Draw(m_Camera->GetPerspective(), m_Camera->GetTransform());
}

// Getter
Camera* Scene::GetCurrentCamera()
{
	return m_Camera;
}

Environment* Scene::GetEnvironment() {
	return m_Environement;
}
