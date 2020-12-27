#pragma once
#include "../../Core/Timestep.h"
#include <glm\ext\vector_float3.hpp>

#include <glm\ext\matrix_float4x4.hpp>
#include "../../Rendering/Shaders/Shader.h"

class Scene;
class QuadEntity
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	Shader* m_Shader;
	Scene* m_Scene;
	
public:
	QuadEntity(Scene* scene);
	~QuadEntity();

	void Update(Timestep ts);
	void Draw(glm::mat4 projection, glm::mat4 transform);

	glm::vec3 Translation;
	glm::vec3 Rotation;
	glm::vec3 Scale;


	glm::mat4 GetTransform();

};