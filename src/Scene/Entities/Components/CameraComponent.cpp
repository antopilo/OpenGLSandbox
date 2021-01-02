#pragma once
#include "CameraComponent.h"
#include "../ImGuiHelper.h"
void CameraComponent::DrawEditor() {
    ImGui::Text("Camera");
    ImGui::SliderFloat("FOV", &Camera.Fov, 1.0f, 180.0f, "%.2f", 1.0f);
}