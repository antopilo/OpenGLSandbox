#pragma once
//#include <imgui\imgui.h>
#include "LightComponent.h"
#include "../../../Rendering/Renderer.h"
#include "../ImGuiHelper.h"
#include <GL\glew.h>
LightComponent::LightComponent()
{
    Color = glm::vec3(1, 1, 1);
    Strength = 10.0f;
    Direction = glm::vec3(0.1f, 1, 0);

	// Create FBO
	glGenFramebuffers(1, &m_Framebuffer);

	// Create shadow map texture...
	glGenTextures(1, &m_Shadowmap);
	glBindTexture(GL_TEXTURE_2D, m_Shadowmap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        4096, 4096, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Attach texture to frame buffer 
	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Shadowmap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

glm::mat4 LightComponent::GetProjection()
{
    return glm::ortho(-25.0f, 25.0f, -25.0f, 25.0f, -50.0f, 50.0f);
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

void LightComponent::BeginDrawShadow()
{
    glViewport(0, 0, 4096, 4096);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glClear(GL_DEPTH_BUFFER_BIT);
    Renderer::m_ShadowmapShader->Bind();
    // Render scene...

}

void LightComponent::EndDrawShadow()
{
    glViewport(0, 0, 1280, 720);
}

void LightComponent::DrawShadow()
{
    if (Type != Directional)
        return;

    Renderer::m_ShadowmapShader->Bind();
}

void LightComponent::Draw(TransformComponent transformComponent, Camera* cam)
{
    Renderer::RegisterLight(transformComponent, *this, cam);


}

void LightComponent::DrawEditor() {
    ImGui::TextColored(ImGui::GetStyleColorVec4(1), "Light properties");
    ImGui::ColorEdit4("Light Color", &Color.r);
    ImGui::SliderFloat("Strength", &Strength, 0.0f, 50.0f);
    
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
    
    //if (Type == 1) {
    //    ImGui::SliderFloat("Attenuation", &Attenuation, 0.0f, 1.0f);
    //    ImGui::SliderFloat("Linear attenuation", &LinearAttenuation, 0.0f, 1.0f);
    //    ImGui::SliderFloat("Quadratic attenuation", &QuadraticAttenuation, 0.0f, 1.0f);
    //}
    ImGuiHelper::DrawVec3("Direction", &Direction);
    //Direction = glm::normalize(Direction);
}
