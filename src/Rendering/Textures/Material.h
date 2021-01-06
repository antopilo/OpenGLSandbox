#pragma once
#include "Texture.h"
#include <glm\ext\vector_float3.hpp>

class Material 
{
private:
	std::string m_Name;

public:
	Texture* m_Albedo;
	Texture* m_AO;
	Texture* m_Metalness;
	Texture* m_Roughness;
	Texture* m_Normal;

	glm::vec3 m_AlbedoColor;

	Material(const std::string albedo);
	Material(const glm::vec3 albedoColor);
	~Material();

	void SetAO(const std::string albedo);
	void SetMetalness(const std::string albedo);
	void SetRoughness(const std::string albedo);
	void SetNormal(const std::string albedo);
	void SetName(const std::string name);

	std::string GetName();

	void Bind();
};