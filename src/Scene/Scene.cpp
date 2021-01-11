#pragma once
#include "Scene.h"
#include "Entities/Entity.h"
#include "Entities/Components.h"
#include "../Rendering/Renderer.h"
#include "../Core/MaterialManager.h"
Scene::Scene()
{
	m_Environement = new Environment();

	// Kind of, im using ENTT for entity managment
	// I made a wrapper over it. so no.
	// okay.
	auto cubeEntity1 = CreateEntity("cube3");
	cubeEntity1.AddComponent<ModelComponent>();
	cubeEntity1.GetComponent<ModelComponent>().LoadModel("Res/Models/Sponza/Sponza.gltf");
	cubeEntity1.GetComponent<TransformComponent>().Scale = glm::vec3(0.01f, 0.01f, 0.01f);

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
	m_Skybox = new SkyboxHDR("Res/Textures/Skyboxes/HDR/lilienstein_4k.hdr");
}

// update entities and some components.
void Scene::Update(Timestep ts)
{
	auto group = m_Registry.group<TransformComponent>(entt::get<CameraComponent>);
	for (auto e : group) {
		auto [transform, cam] = group.get<TransformComponent, CameraComponent>(e);
		cam.Camera.Update(ts);
	}
}

void Scene::DrawShadows()
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

	auto modelView = m_Registry.view<TransformComponent, ModelComponent>();
	auto view = m_Registry.view<TransformComponent, LightComponent>();

	for (auto l : view) {
		auto [lightTransform, light] = view.get<TransformComponent, LightComponent>(l);
		if (light.Type != Directional)
			continue;

		light.BeginDrawShadow();
		for (auto e : modelView)
		{
			auto [transform, model] = modelView.get<TransformComponent, ModelComponent>(e);
			//glm::mat4 lightView = glm::lookAt(light.GetDirection(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			
			glm::vec3 pos = lightTransform.Translation;
			glm::mat4 lightView = glm::lookAt(pos, pos - light.GetDirection(), glm::vec3(0.0f, 1.0f, 0.0f));
			Renderer::m_ShadowmapShader->SetUniformMat4f("lightSpaceMatrix", light.GetProjection() * lightView);
			Renderer::m_ShadowmapShader->SetUniformMat4f("model", transform.GetTransform());

			model.Draw();
		}

		light.EndDrawShadow();
	}
}

void Scene::Draw()
{
	Renderer::m_Shader->Bind();

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
			light.Draw(transform, cam);
		}
	}

	// first pass
	m_Skybox->Draw(cam->GetPerspective(), cam->GetTransform());

	// isnt deferred multi-pass rendering?
	// What reflections options there is for forward rendering.
	// yes? no. It involves multiple passes but multi-pass rendering is not necessarily deffered.
	// I would suggest moving to deferred
	// Most graphics techniques rely on deferred
	// you see how you are doing the lighting?
	// Rendering the geometry and then directly lighting it in the fragment shader?

	// in deferred
	// Instead of rendering out the actual lighting when you render your geometry
	// you output the following in multiple textures
	// normals
	// roughness
	// metalness
	// position
	// albedo
	// depth etc

	// Then in another pass
	// you take those textures and then draw a screen quad
	// then you sample them to get the values for lighting
	// and then you do the lighting
	// That's deferred.
	// Well instead of doing the lighting in one pass like you are doing now
	// you do it in 2. nah not really. a bit. it means that you are binding materials in the gbuffer pass
	// not the lighting pass
	// you are also going to have to allow for mutiple render targets (MRT).
	// yes that is where I learnt it. okay.

	// Ok. got it. that will be a major refact holy shit
	// learn opengl has a chapter on deferred, should be good with that.Wanna take a look at my structure a bit? follow.
	// So that could be all done in 2 pass.
	// Second pass
	//yeah
	Renderer::m_Shader->Bind();
	m_Skybox->Push();
	Renderer::m_Shader->SetUniform1i("u_ShowNormal", 0);
	if (cam) 
	{
		Renderer::m_Shader->SetUniform1f("u_Exposure", cam->Exposure);

		auto view = m_Registry.view<TransformComponent, ModelComponent>();
		for (auto e : view) {
			auto [transform, model] = view.get<TransformComponent, ModelComponent>(e);
			Renderer::m_Shader->SetUniformMat4f("u_View", cam->GetTransform());
			Renderer::m_Shader->SetUniformMat4f("u_Projection", cam->GetPerspective());
			Renderer::m_Shader->SetUniformMat4f("u_Model", transform.GetTransform());
			model.Draw();
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
