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
	Texture* m_Displacement;

	glm::vec3 m_AlbedoColor;

	Material(const std::string albedo);
	Material(Texture* texture) { m_Albedo = texture; }
	Material(const glm::vec3 albedoColor);
	~Material();

	void Bind();

	void SetName(const std::string name);
	std::string GetName();

	void SetAlbedo(const std::string path) { m_Albedo = new Texture(path); }
	void SetAlbedo(Texture* texture) { m_Albedo = texture; }

	void SetAO(const std::string albedo);
	void SetAO(Texture* texture) { m_AO = texture; }

	void SetMetalness(const std::string albedo);
	void SetMetalness(Texture* texture) { m_Metalness = texture; }

	void SetRoughness(const std::string albedo);
	void SetRoughness(Texture* texture) { m_Roughness = texture; }

	void SetNormal(const std::string albedo);
	void SetNormal(Texture* texture) { m_Normal = texture; }

	void SetDisplacement(const std::string displacement);
	void SetDisplacement(Texture* texture) { m_Displacement = texture; }
};