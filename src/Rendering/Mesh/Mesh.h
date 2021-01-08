#pragma once
#include <vector>
#include "../Textures/Texture.h"
#include "../Vertex.h"
#include <glm\ext\matrix_float4x4.hpp>
#include "../Textures/Material.h"
struct MeshVertex
{

};


class Mesh
{
public:
	std::vector<Texture> m_Textures;
	std::vector<unsigned int> m_Indices;
	std::vector<Vertex> m_Vertices;
	Material* m_Material;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material* material);
	void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform);
private:
	//  render data
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};