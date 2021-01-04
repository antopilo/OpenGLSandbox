#pragma once
#include "Texture.h"

class Material {

public:
	Texture* m_Albedo;
	Texture* m_AO;
	Texture* m_Metalness;
	Texture* m_Roughness;
	Texture* m_Normal;


	Material(const std::string albedo);
	~Material();
	void SetAO(const std::string albedo);
	void SetMetalness(const std::string albedo);
	void SetRoughness(const std::string albedo);
	void SetNormal(const std::string albedo);

	void Bind();
};