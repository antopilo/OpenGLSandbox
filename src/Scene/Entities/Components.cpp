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
}

void CubeComponent::Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform) {

    Renderer::m_Shader->Bind();
    Renderer::m_Shader->SetUniformMat4f("u_Model", transform);
    Renderer::m_Shader->SetUniform1f("u_Shininess", Shininess);

    //Renderer::m_Shader->SetUniform4f("u_AmbientColor", 1.0f, 1.0f, 1.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeComponent::DrawEditor() {
    ImGui::Text("Material");
    ImGui::SliderFloat("Shininess", &Shininess, 0.0f, 2.0f, "", 1.0f);
}

