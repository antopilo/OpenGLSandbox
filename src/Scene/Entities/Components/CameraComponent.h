#pragma once
#include "../../../Rendering/Camera.h"
#include "TransformComponent.h"
struct CameraComponent {
	Camera Camera;
	TransformComponent* transformComponent;
	void DrawEditor();
};