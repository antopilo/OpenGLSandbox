#pragma once
#include <glm\ext\matrix_float4x4.hpp>
#include <glm\ext\matrix_clip_space.hpp>
#include "../Core/Timestep.h"

enum CAMERA_TYPE {
	ORTHO,
	PERSPECTIVE
};

class Camera
{
private:
	CAMERA_TYPE m_Type;

	glm::vec3 Translation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
	glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

	glm::mat4 m_Perspective;

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 1.0f);

	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection = glm::normalize(Translation - cameraTarget);

	bool controlled = true;
	float Speed = 10.0f;

	float Yaw = 0;
	float Pitch = 0;

	bool firstMouse = true;

	float mouseLastX = 0;
	float mouseLastY = 0;

public:
	float Fov = 90.0f;

	Camera(CAMERA_TYPE type, glm::vec3 position);

	void SetType(CAMERA_TYPE type);
	void Update(Timestep ts);

	glm::vec3 GetTranslation();
	glm::vec3 GetDirection();
	glm::mat4 GetPerspective();
	glm::mat4 GetTransform();
};
