#pragma once
#include "Scene.h"
#include "Entities/Entity.h"
#include "Entities/Components.h"
#include "../Rendering/Renderer.h"

Scene::Scene()
{
	m_Environement = new Environment();


	//int i = 0;
	//for(int x = 0; x < 8; x++)
	//	for (int y = 0; y < 8; y++) {
	//		std::string name = "cube" + std::to_string(i);
	//		auto cubeEntity = CreateEntity(name);
	//		cubeEntity.AddComponent<CubeComponent>();
	//		TransformComponent& component = cubeEntity.GetComponent<TransformComponent>();
	//		component.Translation.x = x * 1.5f;
	//		component.Translation.y = y * 1.5f;
	//
	//		CubeComponent& cube = cubeEntity.GetComponent<CubeComponent>();
	//		cube.roughness = x / 8;
	//		cube.metallic  = y / 8;
	//		i++;
	//	}
	
	auto cubeEntity2 = CreateEntity("cube2");
	cubeEntity2.AddComponent<CubeComponent>();
	cubeEntity2.GetComponent<TransformComponent>().Translation.x = 1.0f;
	//
	//auto cubeEntity3 = CreateEntity("cube3");
	//cubeEntity3.AddComponent<CubeComponent>();
	//cubeEntity3.GetComponent<TransformComponent>().Translation.x = 0.0f;

	auto camEntity = CreateEntity("Camera");
	camEntity.AddComponent<CameraComponent>().transformComponent = &camEntity.GetComponent<TransformComponent>();

	auto lightEntity = CreateEntity("Light");
	lightEntity.AddComponent<LightComponent>();

	auto lightEntity2 = CreateEntity("Light2");
	lightEntity2.AddComponent<LightComponent>();

	
}

Scene::~Scene() {
	delete m_Environement;
}

void Scene::Init() {
	m_Skybox = new SkyboxHDR("Res/Textures/Skyboxes/HDR/lilienstein_4k.hdr");
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
	m_Environement->Push();
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
		auto view = m_Registry.view<TransformComponent, CubeComponent>();
		for (auto e : view) {
			auto [transform, cube] = view.get<TransformComponent, CubeComponent>(e);
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
