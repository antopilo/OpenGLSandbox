#pragma once
//#include <imgui\imgui.h>
#include "LightComponent.h"
#include "../../../Rendering/Renderer.h"
#include "../ImGuiHelper.h"
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
    ImGui::TextColored(ImGui::GetStyleColorVec4(1), "Light properties");
    ImGui::ColorEdit4("Light Color", &Color.r);
    ImGui::SliderFloat("Strength", &Strength, 0.0f, 10.0f);
    
    const char* types[] = { "Directional", "Point", "Spot" };
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
    Direction = glm::normalize(Direction);
}
