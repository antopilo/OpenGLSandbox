#pragma once
#include "Components.h"
#include <string>
#include "../../Rendering/Vertex.h"
#include <GL\glew.h>
#include "../../Rendering/Renderer.h"
#include "../../Rendering/Camera.h"

TransformComponent::TransformComponent() {
    Translation = glm::vec3(0, 0, 0);
    Rotation = glm::vec3(0, 0, 0);
    Scale = glm::vec3(1, 1, 1);
}

glm::mat4 TransformComponent::GetTransform() {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, Translation);
    transform = glm::rotate(transform, Rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, Rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, Rotation.z, glm::vec3(0, 0, 1));
    transform = glm::scale(transform, Scale);
    return transform;
}



CubeComponent::CubeComponent() {
    Vertex vertices[] = {
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },

        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },

        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },

        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },

        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },

        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
    };

    // Setup buffers
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GL_FLOAT) * 3));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GL_FLOAT) * 5));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GL_FLOAT) * 8));
    glEnableVertexAttribArray(3);
}

void CubeComponent::Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform) {

    Renderer::m_Shader->Bind();

    Renderer::m_Shader->SetUniformMat4f("u_Model", transform);

    //glm::vec4 ambientColor = m_Scene->GetEnvironment()->GetAmbientColor();
    Renderer::m_Shader->SetUniform4f("u_AmbientColor", 0.1f, 0.1f, 0.1f, 1.0f);

    //glm::vec4 lightColor = m_Scene->GetEnvironment()->GetDirectionalLightColor();
    //Renderer::m_Shader->SetUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);

    //glm::vec3 lightDir = m_Scene->GetEnvironment()->GetDirectionalLight();
    //Renderer::m_Shader->SetUniform3f("u_LightDirection", 0.1f, -0.8f, 0.0f);

    //Renderer::m_Shader->SetUniform1f("u_Strength", 10);
    Renderer::m_Shader->SetUniform1f("u_Shininess", 10);

    //glm::vec3 eyePos = m_Scene->GetCurrentCamera()->GetTranslation();
    Renderer::m_Shader->SetUniform3f("u_EyePosition", 0.0f, 0.0f, 0.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

LightComponent::LightComponent()
{
    Color = glm::vec3(1, 1, 1);
    Strength = 10.0f;
    Direction = glm::vec3(10, 0, 0);
}

glm::vec3 LightComponent::GetDirection()
{
    glm::mat4 start;
    glm::vec3 defaultDirection(1, 0, 0);

    glm::rotate(start, Direction.x, glm::vec3(1, 0, 0));
    glm::rotate(start, Direction.y, glm::vec3(1, 0, 0));
    glm::rotate(start, Direction.z, glm::vec3(1, 0, 0));

    return start * glm::vec4(defaultDirection, 1.0f);
}

void LightComponent::Draw(TransformComponent transformComponent)
{
    Renderer::RegisterLight(transformComponent, *this);
}
