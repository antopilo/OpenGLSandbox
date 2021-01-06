#include "Material.h"
#include <glm\ext\vector_float4.hpp>
#include "../Renderer.h"

Material::Material(const std::string albedo) 
{
	m_Albedo = new Texture(albedo);
}

Material::Material(const glm::vec3 albedoColor)
{
	m_AlbedoColor = albedoColor;
}

Material::~Material() 
{
	delete m_Albedo;
	delete m_AO;
	delete m_Metalness;
	delete m_Roughness;
	delete m_Normal;
}

void Material::Bind() 
{
	if (m_Albedo != nullptr) {
		m_Albedo->Bind(1);
		Renderer::m_Shader->SetUniform1i("m_HasAlbedo", 1);
		Renderer::m_Shader->SetUniform1i("m_Albedo", 1);
	}
		
	if (m_AO != nullptr) {
		m_AO->Bind(2);
		Renderer::m_Shader->SetUniform1i("m_HasAO", 1);
		Renderer::m_Shader->SetUniform1i("m_AO", 2);
	}
		
	if (m_Metalness != nullptr) {
		m_Metalness->Bind(3);
		Renderer::m_Shader->SetUniform1i("m_HasMetalness", 1);
		Renderer::m_Shader->SetUniform1i("m_Metalness", 3);
	}
		
	if (m_Roughness != nullptr) {
		m_Roughness->Bind(4);
		Renderer::m_Shader->SetUniform1i("m_HasRoughness", 1);
		Renderer::m_Shader->SetUniform1i("m_Roughness", 4);
	}
}

void Material::SetName(const std::string name) 
{
	m_Name = name;
}

std::string Material::GetName() { return m_Name; }

void Material::SetAO(const std::string ao)
{
	m_AO = new Texture(ao);
}
void Material::SetMetalness(const std::string metalness)
{
	m_Metalness = new Texture(metalness);
}
void Material::SetRoughness(const std::string roughness)
{
	m_Roughness = new Texture(roughness);
}
void Material::SetNormal(const std::string normal)
{
	m_Normal = new Texture(normal);
}


