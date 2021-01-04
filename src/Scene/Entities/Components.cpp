#pragma once
#include "Components.h"
#include <string>
#include "../../Rendering/Vertex.h"
#include <GL\glew.h>
#include "../../Rendering/Camera.h"
#include "../../Rendering/Renderer.h"
#include "ImGuiHelper.h"



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

    albedo = glm::vec3(1.0f, 0.0f, 0.0f);
    metallic = 1.0f;
    roughness = 0.0f;
    ao = 0.0f;
}

void CubeComponent::Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform) {

   
    Renderer::m_Shader->SetUniformMat4f("u_Model", transform);
    //Renderer::m_Shader->SetUniform1f("u_Shininess", Shininess);
    Renderer::m_Shader->SetUniform3f("albedo", albedo.r, albedo.g, albedo.b);
    Renderer::m_Shader->SetUniform1f("metallic", metallic);
    Renderer::m_Shader->SetUniform1f("roughness", roughness);
    Renderer::m_Shader->SetUniform1f("ao", ao);
    //Renderer::m_Shader->SetUniform1i("u_Skybox", 3);
    //Renderer::m_Shader->SetUniform4f("u_AmbientColor", 1.0f, 1.0f, 1.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeComponent::DrawEditor() {
    ImGui::Text("Material");
    ImGui::ColorEdit3("Albedo", &albedo.r);
    ImGui::SliderFloat("Metallic", &metallic, 0.0f, 1.0f, "", 1.0f);
    ImGui::SliderFloat("Roughness", &roughness, 0.0f, 1.0f, "", 1.0f);
    ImGui::SliderFloat("AO", &ao, 0.0f, 1.0f, "", 1.0f);
}

