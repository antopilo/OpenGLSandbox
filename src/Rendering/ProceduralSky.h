#pragma once
#include <glm/ext/vector_float3.hpp>
#include "Vertex.h"
class Camera;
class ProceduralSky {
public:
	float SurfaceRadius = 6360e3;
	float AtmosphereRadius = 6380e3;
	glm::vec3 RayleighScattering = glm::vec3(58e-7, 135e-7, 331e-7);
	glm::vec3 MieScattering = glm::vec3(2e-5);
	float SunIntensity = 10.0;
	glm::vec3 CenterPoint = glm::vec3(0, -SurfaceRadius, 0);
	glm::vec3 SunDirection = glm::vec3(0, 1, 0);
	unsigned int VAO;
	unsigned int VBO;
	ProceduralSky();
	void Draw(Camera* cam);


};