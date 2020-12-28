#pragma once
#include "Environment.h"
#include <glm\detail\func_geometric.inl>

Environment::Environment() 
{
	m_AmbientColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

// Ambient Light
glm::vec4 Environment::GetAmbientColor() 
{
	return m_AmbientColor;
}

void Environment::SetAmbientColor(glm::vec4 color)
{
	m_AmbientColor = color;
}

// Directional light
// - Color
glm::vec4 Environment::GetDirectionalLightColor()
{
	return m_DirectionalLightColor;
}

void Environment::SetDirectionalLightColor(glm::vec4 color)
{
	m_DirectionalLightColor = color;

}
// - Direction
glm::vec3 Environment::GetDirectionalLight()
{
	return m_DirectionalLight;
}

void Environment::SetDirectionalLight(float x, float y, float z)
{
	m_DirectionalLight = glm::normalize(glm::vec3(x, y, z));
}


// Strength
float Environment::GetDirectionalStrength() {
	return m_DirectionalStrength;
}
