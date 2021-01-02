#pragma once
#include "Environment.h"
#include "../Rendering/Renderer.h"
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

void Environment::Push() {
	//Renderer::m_Shader->SetUniform3f("u_AmbientColor", m_AmbientColor.r, m_AmbientColor.g, m_AmbientColor.b);
	//Renderer::m_Shader->SetUniform4f("u_AmbientColor", 1.0f, 1.0f, 1.0f, 1.0f);
}