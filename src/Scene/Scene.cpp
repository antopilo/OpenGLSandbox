#pragma once
#include "Scene.h"
#include "Entities/Entity.h"
#include "Entities/Components.h"
Scene::Scene()
{
	m_Camera = new Camera(PERSPECTIVE, glm::vec3(-1, 0, -1));
	m_Environement = new Environment();

	m_Entities.push_back(new QuadEntity(this));
	m_Entity = new QuadEntity(this);

	auto cubeEntity = CreateEntity();
	cubeEntity.AddComponent<CubeComponent>();

	auto camEntity = CreateEntity();
	cubeEntity.AddComponent<CameraComponent>();
}

Scene::~Scene() {
	delete m_Camera;
	delete m_Entity;
	delete m_Environement;
}

void Scene::Update(Timestep ts)
{
	auto group = m_Registry.group<TransformComponent>(entt::get<CameraComponent>);
	for (auto e : group) {
		auto [transform, cam] = group.get<TransformComponent, CameraComponent>(e);

		cam.Camera.Update(ts);
	}
}

Entity Scene::CreateEntity() {
	Entity entity = { m_Registry.create(), this };
	entity.AddComponent<TransformComponent>();
	return entity;
}

void Scene::Draw()
{
	Camera* cam = nullptr;
	{
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto e : view) {
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(e);
			cam = &camera.Camera;
			break;
		}
	}
	

	if (cam) {
		auto view = m_Registry.view<TransformComponent, CubeComponent>();
		for (auto e : view) {
			auto [transform, cube] = view.get<TransformComponent, CubeComponent>(e);
			cube.Draw(cam->GetPerspective(), cam->GetTransform(), transform.GetTransform());
		}
	}
	
	//for(auto e : m_Entities)
	//	e->Draw(m_Camera->GetPerspective(), m_Camera->GetTransform());
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
