#include "Material.h"
#include <glm\ext\vector_float4.hpp>
#include "../Renderer.h"

Material::Material(const std::string albedo) 
{
	m_Albedo = new Texture(albedo);
}

//Material::Material()
//{
//}

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
	delete m_Displacement;
}

void Material::Bind() 
{
	if (m_Albedo != nullptr) {
		m_Albedo->Bind(4);
		Renderer::m_Shader->SetUniform1i("m_HasAlbedo", 1);
		Renderer::m_Shader->SetUniform1i("m_Albedo", 4);
	}
	else {
		Renderer::m_Shader->SetUniform1i("m_HasAlbedo", 0);
	}
		
	if (m_AO != nullptr) {
		m_AO->Bind(5);
		Renderer::m_Shader->SetUniform1i("m_HasAO", 1);
		Renderer::m_Shader->SetUniform1i("m_AO", 5);
	}
	else {
		Renderer::m_Shader->SetUniform1f("ao", 1.0f);
		Renderer::m_Shader->SetUniform1i("m_HasAO", 0);
	}
		
	if (m_Metalness != nullptr) {
		m_Metalness->Bind(6);
		Renderer::m_Shader->SetUniform1i("m_HasMetalness", 1);
		Renderer::m_Shader->SetUniform1i("m_Metalness", 6);
	}
	else {
		Renderer::m_Shader->SetUniform1f("metallic", 0.1f);
		Renderer::m_Shader->SetUniform1i("m_HasMetalness", 0);
	}
		
	if (m_Roughness != nullptr) {
		m_Roughness->Bind(7);
		Renderer::m_Shader->SetUniform1i("m_HasRoughness", 1);
		Renderer::m_Shader->SetUniform1i("m_Roughness", 7);
	}
	else {
		Renderer::m_Shader->SetUniform1f("roughness", 0.9f);
		Renderer::m_Shader->SetUniform1i("m_HasRoughness", 0);
	}

	if (m_Normal != nullptr) {
		m_Normal->Bind(8);
		Renderer::m_Shader->SetUniform1i("m_HasNormal", 1);
		Renderer::m_Shader->SetUniform1i("m_Normal", 8);
	}
	else {
		Renderer::m_Shader->SetUniform1i("m_HasNormal", 0);
	}

	if (m_Displacement != nullptr) {
		m_Displacement->Bind(9);
		Renderer::m_Shader->SetUniform1i("m_HasDisplacement", 0);
		Renderer::m_Shader->SetUniform1i("m_Displacement", 9);
	}
	else {
		Renderer::m_Shader->SetUniform1i("m_HasDisplacement", 0);
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

void Material::SetDisplacement(const std::string displacement)
{
	m_Displacement = new Texture(displacement);
}


