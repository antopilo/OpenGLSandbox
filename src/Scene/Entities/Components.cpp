#pragma once
#include "Components.h"
#include <string>
#include "../../Rendering/Vertex.h"
#include <GL\glew.h>
#include "../../Rendering/Camera.h"
#include "imgui/imgui.h"
#include "../../Rendering/Renderer.h"
#include "ImGuiHelper.h"
TransformComponent::TransformComponent() {
    Translation = glm::vec3(0, 0, 0);
    Rotation = glm::vec3(0, 0, 0);
    Scale = glm::vec3(1, 1, 1);
}

glm::mat4 TransformComponent::GetTransform() {
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, Translation);
    transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
    transform = glm::scale(transform, Scale);
    return transform;
}

void TransformComponent::DrawEditor()
{
    ImGuiHelper::DrawVec3("Translation", &Translation);
    ImGuiHelper::DrawVec3("Rotation", &Rotation);
    ImGuiHelper::DrawVec3("Scale", &Scale);
}

void CameraComponent::DrawEditor() {
    ImGui::Text("Camera");
    ImGui::SliderFloat("FOV", &Camera.Fov, 1.0f, 180.0f, "%.2f", 1.0f);
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
    Renderer::m_Shader->SetUniform1f("u_Shininess", Shininess);

    //Renderer::m_Shader->SetUniform4f("u_AmbientColor", 1.0f, 1.0f, 1.0f, 1.0f);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void CubeComponent::DrawEditor() {
    ImGui::Text("Material");
    ImGui::SliderFloat("Shininess", &Shininess, 0.0f, 2.0f, "", 1.0f);
}

LightComponent::LightComponent()
{
    Color = glm::vec3(1, 1, 1);
    Strength = 10.0f;
    Direction = glm::vec3(0.1f, 1, 0);
}

glm::vec3 LightComponent::GetDirection()
{
    glm::mat4 start = glm::mat4(1.0f);
    glm::vec3 defaultDirection(0, 0, 1); // forward

    start = glm::rotate(start, glm::radians(Direction.x), glm::vec3(1, 0, 0));
    start = glm::rotate(start, glm::radians(Direction.y), glm::vec3(0, 1, 0));
    start = glm::rotate(start, glm::radians(Direction.z), glm::vec3(0, 0, 1));

    return glm::vec3(start * glm::vec4(defaultDirection, 1.0f));
}

void LightComponent::Draw(TransformComponent transformComponent)
{
    Renderer::RegisterLight(transformComponent, *this);
}

void LightComponent::DrawEditor() {
    ImGui::TextColored(ImGui::GetStyleColorVec4(1),"Light properties");
    ImGui::ColorEdit4("Light Color", &Color.r);
    ImGui::SliderFloat("Strength", &Strength, 0.0f, 10.0f);

    const char* types[] = { "Directional", "Point", "Spot"};
    static const char* current_item = types[Type];

    if (ImGui::BeginCombo("Type", current_item)) // The second parameter is the label previewed before opening the combo.
    {
        for (int n = 0; n < IM_ARRAYSIZE(types); n++)
        {
            bool is_selected = (current_item == types[n]); // You can store your selection however you want, outside or inside your objects
            if (ImGui::Selectable(types[n], is_selected)) {
                current_item = types[n];
                Type = (LightType)n;
            }
            if (is_selected)
                ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
        }
        ImGui::EndCombo();
    }

    if (Type == 1) {
        ImGui::SliderFloat("Attenuation", &Attenuation, 0.0f, 1.0f);
        ImGui::SliderFloat("Linear attenuation", &LinearAttenuation, 0.0f, 1.0f);
        ImGui::SliderFloat("Quadratic attenuation", &QuadraticAttenuation, 0.0f, 1.0f);
    }
    ImGuiHelper::DrawVec3("Direction", &Direction);
    //Direction = glm::normalize(Direction);
}
