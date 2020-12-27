#pragma once
#include <glm\ext\vector_float4.hpp>

class Environment
{
public:
	Environment();

	void SetAmbientColor(glm::vec4 color);
	glm::vec4 GetAmbientColor();
	glm::vec4 m_AmbientColor;
};
