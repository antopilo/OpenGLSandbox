#include "Material.h"

Material::Material(const std::string albedo) {
	m_Albedo = new Texture(albedo);
}

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

Material::~Material() {
	delete m_Albedo;
	delete m_AO;
	delete m_Metalness;
	delete m_Roughness;
	delete m_Normal;
}

void Material::Bind() {

	if(m_Albedo != nullptr)
		m_Albedo->Bind(0);
	if (m_AO != nullptr)
		m_AO->Bind(1);
	if (m_Metalness != nullptr)
		m_Metalness->Bind(2);
	if (m_Roughness != nullptr)
		m_Roughness->Bind(3);
}