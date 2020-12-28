#pragma once
#include "Scene.h"

Scene::Scene()
{
	m_Camera = new Camera(PERSPECTIVE, glm::vec3(-1, 0, -1));
	m_Environement = new Environment();

	m_Entities.push_back(new QuadEntity(this));
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
	for(auto e : m_Entities)
		e->Draw(m_Camera->GetPerspective(), m_Camera->GetTransform());
}

void Scene::AddEntity() {
	m_Entities.push_back(new QuadEntity(this));
}

void Scene::RemoveEntity(int i) {
	m_Entities.erase(m_Entities.begin() + i);
}

int Scene::GetEntityCount() {
	return m_Entities.size();
}

QuadEntity* Scene::GetEntity(int i) {
	return m_Entities[i];
}

// Getter
Camera* Scene::GetCurrentCamera()
{
	return m_Camera;
}

Environment* Scene::GetEnvironment() {
	//m_Environement->m_DirectionalLight = glm::normalize(m_Environement->m_DirectionalLight);
	return m_Environement;
}
