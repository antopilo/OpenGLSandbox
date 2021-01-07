#pragma once
#include "CameraComponent.h"
#include "../ImGuiHelper.h"

void CameraComponent::DrawEditor() {
    ImGui::Text("Camera");
    ImGui::SliderFloat("Exposure", &Camera.Exposure, 0.0f, 2.0f, "%.2f", 1.0f);
    ImGui::SliderFloat("FOV", &Camera.Fov, 1.0f, 180.0f, "%.2f", 1.0f);
    ImGui::SliderFloat("Speed", &Camera.Speed, 0.1f, 5.0f, "%.2f", 1.0f);
}