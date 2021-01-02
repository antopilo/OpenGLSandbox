#include "Renderer.h"
#include <GL\glew.h>
#include "Camera.h"
#include "Textures/Texture.h"
#include "Textures/Cubemap.h"

unsigned int depthTexture;
unsigned int depthFBO;

Shader* Renderer::m_Shader;
Shader* Renderer::m_SkyboxShader;

void Renderer::Init()
{
    m_ShadowmapShader = new Shader("Res/Shaders/shadowMap.shader");
    m_SkyboxShader    = new Shader("Res/Shaders/skybox.shader");
    m_Shader = new Shader("Res/Shaders/basic.shader");
    m_Shader->Bind();

    int samplers[2] = { 0, 1 };
    m_Shader->SetUniform1iv("u_Textures", 2, samplers);

    // Todo mem leak.
    Texture* texture = new Texture("Res/Textures/0.png");
    texture->Bind(0);
    Texture* texture2 = new Texture("Res/Textures/1.png");
    texture->Bind(1);

   


    // Shadow map.
    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 
        1280, 720, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenFramebuffers(1, &depthFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, depthTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glDrawBuffer(GL_NONE);
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

    // shadow map

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    //ConfigureShaderAndMatrices();
    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(glm::vec3(-2.0f, 4.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
    m_ShadowmapShader->Bind();
    //m_ShadowmapShader->SetUniformMat4f("lightSpaceMatrix", lightSpaceMatrix);

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //RenderScene();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);




    m_Shader->Bind();
}

void Renderer::EndDraw() {
    m_Lights.clear(); // Clean up lights.
}

// List of all lights queued to be used for rendering this frame.
std::vector<Light> Renderer::m_Lights;
void Renderer::RegisterLight(TransformComponent transform, LightComponent light)
{
    Light newLight{ transform , light };
    m_Lights.push_back(newLight);

    // What light idx is this?
    int idx = m_Lights.size();
    m_Shader->SetUniform1i("LightCount", idx);

    glm::vec3 direction = light.GetDirection();
    // Push uniforms in light array.
    m_Shader->SetUniform1i("Lights[" + std::to_string(idx - 1) + "].Type", light.Type);
    m_Shader->SetUniform1f("Lights[" + std::to_string(idx - 1) + "].ConstantAttenuation", light.Attenuation);
    m_Shader->SetUniform1f("Lights[" + std::to_string(idx - 1) + "].LinearAttenuation", light.LinearAttenuation);
    m_Shader->SetUniform1f("Lights[" + std::to_string(idx - 1) + "].QuadraticAttenuation", light.QuadraticAttenuation);
    m_Shader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Position", transform.Translation.x, transform.Translation.y, transform.Translation.z);
    m_Shader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Direction", direction.x, direction.y, direction.z);
    m_Shader->SetUniform3f("Lights[" + std::to_string(idx - 1) + "].Color", light.Color.r, light.Color.g, light.Color.b);
    m_Shader->SetUniform1f("Lights[" + std::to_string(idx - 1) + "].Strength", light.Strength);
}
