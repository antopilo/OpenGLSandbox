#pragma once
#include <glm\ext\vector_float3.hpp>
#include <glm\mat4x4.hpp>
class CubemapTexture;

class Skybox {

    static glm::vec3 vertices[]; 
	CubemapTexture* m_Texture;
	unsigned int VBO;
	unsigned int VAO;
public:
	Skybox();
	void Draw(glm::mat4 projection, glm::mat4 view);

};