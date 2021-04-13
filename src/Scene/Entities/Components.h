#pragma once
#include <glm\ext\matrix_float4x4.hpp>
#include <string>

#include "Components/TransformComponent.h"
#include "Components/LightComponent.h"
#include "Components/CameraComponent.h"
#include "Components/MeshComponent.h"
#include "Components/ModelComponent.h"
#include "Components/QuakeMap.h"
#include <imgui/imgui.h>


struct NameComponent {
    std::string Name = "Entity";

    void DrawEditor()
    {
        //ImGui::InputText("Name", &Name);
    }
};



