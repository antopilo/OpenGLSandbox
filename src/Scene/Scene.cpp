#pragma once
#include "Scene.h"
#include "Entities/Entity.h"
#include "Entities/Components.h"
#include "../Rendering/Renderer.h"
#include "../Core/MaterialManager.h"
Scene::Scene()
{
	m_Environement = new Environment();


	auto cubeEntity1 = CreateEntity("cube3");
	cubeEntity1.AddComponent<MeshComponent>();
	cubeEntity1.GetComponent<MeshComponent>().SetMaterial("Paving");

	//auto cubeEntity2 = CreateEntity("cube2");
	//cubeEntity2.AddComponent<MeshComponent>();
	//cubeEntity2.GetComponent<TransformComponent>().Translation.x = 1.0f;
	//cubeEntity2.GetComponent<MeshComponent>().SetMaterial("Marble");
	//
	//auto cubeEntity3 = CreateEntity("cube3");
	//cubeEntity3.AddComponent<MeshComponent>();
	//cubeEntity3.GetComponent<TransformComponent>().Translation.x = -1.0f;
	//cubeEntity3.GetComponent<MeshComponent>().SetMaterial("Gold");
	//
	//auto cubeEntity4 = CreateEntity("cube4");
	//cubeEntity4.AddComponent<MeshComponent>();
	//cubeEntity4.GetComponent<TransformComponent>().Translation.x = -7.0f;
	//cubeEntity4.GetComponent<MeshComponent>().SetMaterial("Planks");
	//
	//auto cubeEntity5 = CreateEntity("cube5");
	//cubeEntity5.AddComponent<MeshComponent>();
	//cubeEntity5.GetComponent<TransformComponent>().Translation.x = -5.0f;
	//cubeEntity5.GetComponent<MeshComponent>().SetMaterial("Paving");


	//MaterialManager::Get()->LoadMaterial("DefaultMaterial");

	//auto cubeEntity3 = CreateEntity("cube3");
	//cubeEntity3.AddComponent<CubeComponent>();
	//cubeEntity3.GetComponent<TransformComponent>().Translation.x = 0.0f;

	auto camEntity = CreateEntity("Camera");
	camEntity.AddComponent<CameraComponent>().transformComponent = &camEntity.GetComponent<TransformComponent>();

	auto lightEntity = CreateEntity("Light");
	lightEntity.AddComponent<LightComponent>();
	lightEntity.GetComponent<TransformComponent>().Translation.y = 1.1f;
}

Scene::~Scene() {
	delete m_Environement;
}

void Scene::Init() {
	m_Skybox = new SkyboxHDR("Res/Textures/Skyboxes/HDR/station_4k.hdr");
}

void Scene::Update(Timestep ts)
{
	auto group = m_Registry.group<TransformComponent>(entt::get<CameraComponent>);
	for (auto e : group) {
		auto [transform, cam] = group.get<TransformComponent, CameraComponent>(e);
		cam.Camera.Update(ts);
	}
}

void Scene::Draw()
{
	// Find the camera of the scene.
	Camera* cam = nullptr;
	{
		auto view = m_Registry.view<TransformComponent, CameraComponent>();
		for (auto e : view) {
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(e);
			cam = &camera.Camera;
			break;
		}
	}

	// Push lights
	{
		auto view = m_Registry.view<TransformComponent, LightComponent>();
		for (auto l : view) {
			auto [transform, light] = view.get<TransformComponent, LightComponent>(l);
			light.Draw(transform);
		}
	}

	m_Skybox->Draw(cam->GetPerspective(), cam->GetTransform());

	Renderer::m_Shader->Bind();

	m_Skybox->Push();

	if (cam) {

		Renderer::m_Shader->SetUniform1f("u_Exposure", cam->Exposure);

		auto view = m_Registry.view<TransformComponent, MeshComponent>();
		for (auto e : view) {
			auto [transform, cube] = view.get<TransformComponent, MeshComponent>(e);
			cube.Draw(cam->GetPerspective(), cam->GetTransform(), transform.GetTransform());
		}
	}
}

std::vector<Entity> Scene::GetAllEntities() {
	std::vector<Entity> allEntities;
	auto view = m_Registry.view<TransformComponent, NameComponent>();
	for (auto e : view) {
		allEntities.push_back(Entity(e, this));
	}
	return allEntities;
}

Entity Scene::CreateEntity(const std::string name) {
	Entity entity = { m_Registry.create(), this };

	// Must have transform
	entity.AddComponent<TransformComponent>();

	NameComponent& nameComponent = entity.AddComponent<NameComponent>();
	nameComponent.Name = name;
	return entity;
}

void Scene::DestroyEntity(Entity entity) {
	entity.Destroy();
}

// Getter
Camera* Scene::GetCurrentCamera()
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
	return cam;
}

Environment* Scene::GetEnvironment() {
	return m_Environement;
}
