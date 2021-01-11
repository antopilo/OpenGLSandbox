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
void Renderer::Init()
{
    m_ShadowmapShader = new Shader("Res/Shaders/shadowMap.shader");
    m_SkyboxShader    = new Shader("Res/Shaders/skybox.shader");
    m_BRDShader = new Shader("Res/Shaders/BRD.shader");
    m_Shader = new Shader("Res/Shaders/basic.shader");
    m_Shader->Bind();

    int samplers[2] = { 0, 1 };
}

const int SHADOW_WIDTH = 1280;
const int SHADOW_HEIGHT = 720;
Shader* Renderer::m_ShadowmapShader;
void Renderer::BeginDraw(Camera* camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->SetUniformMat4f("u_Projection", camera->GetPerspective());
    m_Shader->SetUniformMat4f("u_View", camera->GetTransform());
    m_Shader->SetUniform3f("u_EyePosition", camera->GetTranslation().x, camera->GetTranslation().y, camera->GetTranslation().z);

    // oh jesus

    // its not done just speculation lmfao
    // shadow map

    // Shadow map init here....
    //glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    //glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    //glClear(GL_DEPTH_BUFFER_BIT);
    ////ConfigureShaderAndMatrices();
    //float near_plane = 1.0f, far_plane = 7.5f;
    //glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    //glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
    //    glm::vec3(0.0f, 0.0f, 0.0f),
    //    glm::vec3(0.0f, 1.0f, 0.0f));
    //glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    //m_ShadowmapShader->Bind();
    ////m_ShadowmapShader->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);
    //
    //glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    //glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    //glClear(GL_DEPTH_BUFFER_BIT);
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    ////RenderScene();
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);

    m_Shader->Bind();
}

void Renderer::EndDraw() {
    m_Lights.clear(); // Clean up lights.
}

// List of all lights queued to be used for rendering this frame.
std::vector<Light> Renderer::m_Lights;
void Renderer::RegisterLight(TransformComponent transform, LightComponent light, Camera* cam)
{
    Light newLight{ transform , light };
    m_Lights.push_back(newLight);

    // What light idx is this?
    int idx = m_Lights.size();
    m_Shader->SetUniform1i("LightCount", idx);

    glm::vec3 direction = light.GetDirection();
    
	glm::vec3 pos = transform.Translation;
	glm::mat4 lightView = glm::lookAt(pos, pos - direction, glm::vec3(0.0f, 1.0f, 0.0f));

    // Push uniforms in light array.
    m_Shader->SetUniform1i("Lights[" + std::to_string(idx - 1) + "].Type", light.Type);

	glActiveTexture(GL_TEXTURE0 + 11);
	glBindTexture(GL_TEXTURE_2D, light.m_Shadowmap);
    m_Shader->SetUniform1i("Lights[" + std::to_string(idx - 1) + "].ShadowMap", 11);
    m_Shader->SetUniformMat4f("Lights[" + std::to_string(idx - 1) + "].LightTransform", light.GetProjection() * lightView);
    m_Shader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Position", transform.Translation.x, transform.Translation.y, transform.Translation.z);
    m_Shader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Direction", direction.x, direction.y, direction.z);
    m_Shader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Color", light.Color.r * light.Strength, light.Color.g * light.Strength, light.Color.b * light.Strength);
    //m_Shader->SetUniform1f("Lights[" + std::to_string(idx - 1) + "].Strength", light.Strength);
}
