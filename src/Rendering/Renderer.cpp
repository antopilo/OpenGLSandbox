#include "Renderer.h"
#include <GL\glew.h>
#include "Shaders/Texture.h"
#include "Camera.h"

Shader* Renderer::m_Shader;
void Renderer::Init()
{
    m_Shader = new Shader("Res/Shaders/basic.shader");
    m_Shader->Bind();

    int samplers[2] = { 0, 1 };
    m_Shader->SetUniform1iv("u_Textures", 2, samplers);

    // Todo mem leak.
    Texture* texture = new Texture("Res/Textures/0.png");
    texture->Bind(0);
    Texture* texture2 = new Texture("Res/Textures/1.png");
    texture->Bind(1);
}

void Renderer::BeginDraw(Camera* camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_Shader->SetUniformMat4f("u_Projection", camera->GetPerspective());
    m_Shader->SetUniformMat4f("u_View", camera->GetTransform());
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
}