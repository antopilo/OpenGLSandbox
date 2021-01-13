#pragma once
#include "Shaders/Shader.h"
#include "../Scene/Entities/Components.h"


// DTO for light data.
struct Light {
	TransformComponent transform;
	LightComponent light;
};

class Renderer {
public:
	static Shader* m_Shader;
	static Shader* m_ShadowmapShader;
	static Shader* m_SkyboxShader;
	static Shader* m_BRDShader;
	static Shader* m_GBufferShader;
	static Shader* m_DeferredShader;

	static void Init();

	// Drawing states
	static void BeginDraw(Camera* camera);
	static void EndDraw();

	// Lights
	static std::vector<Light> m_Lights;
	static void RegisterLight(TransformComponent transform, LightComponent light, Camera* cam);
	static void RegisterDeferredLight(TransformComponent transform, LightComponent light, Camera* cam);
};