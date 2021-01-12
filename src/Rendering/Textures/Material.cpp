#include "Material.h"
#include <glm\ext\vector_float4.hpp>
#include "../Renderer.h"

Texture* Material::m_DefaultAlbedo;
Texture* Material::m_DefaultAO;
Texture* Material::m_DefaultNormal;
Texture* Material::m_DefaultRoughness;
Texture* Material::m_DefaultMetalness;
Texture* Material::m_DefaultDisplacement;

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

	if (m_DefaultAlbedo == nullptr)
		m_DefaultAlbedo = TextureManager::Get()->GetTexture("Res/Textures/default/Default.png");
	if (m_DefaultAO == nullptr)
		m_DefaultAO = TextureManager::Get()->GetTexture("Res/Textures/default/Default.png");
	if (m_DefaultNormal == nullptr)
		m_DefaultNormal = TextureManager::Get()->GetTexture("Res/Textures/default/defaultNormal.png");
	if (m_DefaultDisplacement == nullptr)
		m_DefaultDisplacement = TextureManager::Get()->GetTexture("Res/Textures/default/Default.png");
	if (m_DefaultRoughness == nullptr)
		m_DefaultRoughness = TextureManager::Get()->GetTexture("Res/Textures/default/Default.png");
	if (m_DefaultMetalness == nullptr)
		m_DefaultMetalness = TextureManager::Get()->GetTexture("Res/Textures/default/Default.png");
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
	// Albedo
	if (m_Albedo != nullptr)
		m_Albedo->Bind(4);
	else
		m_DefaultAlbedo->Bind(4);
	Renderer::m_Shader->SetUniform1i("m_Albedo", 4);
	Renderer::m_GBufferShader->SetUniform1i("m_Albedo", 4);
	// AO
	if (m_AO != nullptr)
		m_AO->Bind(5);
	else
		m_DefaultAO->Bind(5);
	Renderer::m_Shader->SetUniform1i("m_AO", 5);
	Renderer::m_GBufferShader->SetUniform1i("m_AO", 5);
	// Metallic
	if (m_Metalness != nullptr) 
		m_Metalness->Bind(6);
	else 
		m_DefaultMetalness->Bind(6);
	Renderer::m_Shader->SetUniform1i("m_Metalness", 6);
	Renderer::m_GBufferShader->SetUniform1i("m_Metalness", 6);
	// Roughness
	if (m_Roughness != nullptr)
		m_Roughness->Bind(7);
	else
		m_DefaultRoughness->Bind(7);
	Renderer::m_Shader->SetUniform1i("m_Roughness", 7);
	Renderer::m_GBufferShader->SetUniform1i("m_Roughness", 7);
	// Normal
	if (m_Normal != nullptr)
		m_Normal->Bind(8);
	else
		m_DefaultNormal->Bind(8);
	Renderer::m_Shader->SetUniform1i("m_Normal", 8);
	Renderer::m_GBufferShader->SetUniform1i("m_Normal", 8);
	// Displacement
	if (m_Displacement != nullptr)
		m_Displacement->Bind(9);
	else
		m_DefaultDisplacement->Bind(9);
	Renderer::m_Shader->SetUniform1i("m_Displacement", 9);
	//Renderer::m_Shader->SetUniform1i("m_Displacement", 9);
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


