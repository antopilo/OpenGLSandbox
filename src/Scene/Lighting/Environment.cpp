#pragma once
#include "Environment.h"

Environment::Environment() 
{
	m_AmbientColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

glm::vec4 Environment::GetAmbientColor() 
{
	return m_AmbientColor;
}

void Environment::SetAmbientColor(glm::vec4 color)
{
	m_AmbientColor = color;
}