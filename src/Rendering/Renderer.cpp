#include "Renderer.h"
#include <GL\glew.h>
#include "Camera.h"
#include "Textures/Texture.h"
#include "Textures/Cubemap.h"

unsigned int depthTexture;
unsigned int depthFBO;

Shader* Renderer::m_Shader;
Shader* Renderer::m_SkyboxShader;
Shader* Renderer::m_BRDShader;
Shader* Renderer::m_GBufferShader;
Shader* Renderer::m_DeferredShader;
Shader* Renderer::m_ProceduralSkyShader;
void Renderer::Init()
{
    m_ShadowmapShader = new Shader("Res/Shaders/shadowMap.shader");
    m_SkyboxShader    = new Shader("Res/Shaders/skybox.shader");
    m_BRDShader = new Shader("Res/Shaders/BRD.shader");
    m_GBufferShader = new Shader("Res/Shaders/gbuffer.shader");
    m_DeferredShader = new Shader("Res/Shaders/deferred.shader");
    m_ProceduralSkyShader = new Shader("Res/Shaders/atmospheric_sky.shader");
    m_Shader = new Shader("Res/Shaders/basic.shader");
    m_Shader->Bind();
}

Shader* Renderer::m_ShadowmapShader;

void Renderer::BeginDraw(Camera* camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->SetUniformMat4f("u_Projection", camera->GetPerspective());
    m_Shader->SetUniformMat4f("u_View", camera->GetTransform());
    m_Shader->SetUniform3f("u_EyePosition", camera->GetTranslation().x, camera->GetTranslation().y, camera->GetTranslation().z);

    m_Shader->Bind();
}

void Renderer::EndDraw() 
{
    m_Lights.clear(); // Clean up lights.
}

// List of all lights queued to be used for rendering this frame.
std::vector<Light> Renderer::m_Lights;

void Renderer::RegisterLight(TransformComponent transform, LightComponent light, Camera* cam)
{
    m_Lights.push_back({ transform , light });

    // What light idx is this?
    int idx = m_Lights.size();

    glm::vec3 direction = light.GetDirection();
	glm::vec3 pos = transform.Translation;
	glm::mat4 lightView = glm::lookAt(pos, pos - direction, glm::vec3(0.0f, 1.0f, 0.0f));

    light.m_Framebuffer->GetTexture()->Bind(11);

    m_Shader->SetUniform1i   ("LightCount", idx);
    m_Shader->SetUniform1i   ("Lights[" + std::to_string(idx - 1) + "].Type"          , light.Type);
    m_Shader->SetUniform1i   ("Lights[" + std::to_string(idx - 1) + "].ShadowMap"     , 11);
    m_Shader->SetUniformMat4f("Lights[" + std::to_string(idx - 1) + "].LightTransform", light.GetProjection() * lightView);
    m_Shader->SetUniform3f   ("Lights[" + std::to_string(idx - 1) + "].Position"      , transform.Translation.x, transform.Translation.y, transform.Translation.z);
    m_Shader->SetUniform3f   ("Lights[" + std::to_string(idx - 1) + "].Direction"     , direction.x, direction.y, direction.z);
    m_Shader->SetUniform3f   ("Lights[" + std::to_string(idx - 1) + "].Color"         , light.Color.r * light.Strength, light.Color.g * light.Strength, light.Color.b * light.Strength);
}

void Renderer::RegisterDeferredLight(TransformComponent transform, LightComponent light, Camera* cam)
{
    m_Lights.push_back({ transform , light });

    // What light idx is this?
    int idx = m_Lights.size();

    glm::vec3 direction = light.GetDirection();
    glm::vec3 pos = transform.Translation;
    glm::mat4 lightView = glm::lookAt(pos, pos - direction, glm::vec3(0.0f, 1.0f, 0.0f));

    light.m_Framebuffer->GetTexture()->Bind(11);

    m_DeferredShader->SetUniform1i("LightCount", idx);
    m_DeferredShader->SetUniform1i("Lights[" + std::to_string(idx - 1) + "].Type", light.Type);
    m_DeferredShader->SetUniform1i("Lights[" + std::to_string(idx - 1) + "].ShadowMap", 11);
    m_DeferredShader->SetUniformMat4f("Lights[" + std::to_string(idx - 1) + "].LightTransform", light.GetProjection() * lightView);
    m_DeferredShader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Position", transform.Translation.x, transform.Translation.y, transform.Translation.z);
    m_DeferredShader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Direction", direction.x, direction.y, direction.z);
    m_DeferredShader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Color", light.Color.r * light.Strength, light.Color.g * light.Strength, light.Color.b * light.Strength);
}
