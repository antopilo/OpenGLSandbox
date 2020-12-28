#pragma once
#include <glm\ext\matrix_float4x4.hpp>
#include <glm\ext\matrix_transform.hpp>
#include <GL\glew.h>
#include "../../Rendering/Vertex.h"
#include "../../Rendering/Shaders/Shader.h"
#include "../../Rendering/Shaders/Texture.h"

struct TransformComponent {
	glm::vec3 Translation;
	glm::vec3 Rotation;
	glm::vec3 Scale;

	TransformComponent() {
		Translation = glm::vec3(0, 0, 0);
		Rotation = glm::vec3(0, 0, 0);
		Scale = glm::vec3(1, 1, 1);
	}

	glm::mat4 GetTransform() {
		glm::mat4 transform = glm::mat4(1.0f);
		transform = glm::translate(transform, Translation);
		transform = glm::rotate(transform, Rotation.x, glm::vec3(1, 0, 0));
		transform = glm::rotate(transform, Rotation.y, glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, Rotation.z, glm::vec3(0, 0, 1));
		transform = glm::scale(transform, Scale);
		return transform;
	}
};

struct CubeComponent {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
	Shader* m_Shader;

	CubeComponent() {
        Vertex vertices[] = {
       Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },
       Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
       Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
       Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },

       Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },
       Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
       Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
       Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },

       Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(1.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(1.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },

       Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
       Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
       Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(0.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
       Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(0.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },

       Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },
       Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },
       Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
       Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },

       Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2(1.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
       Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2(1.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2(0.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
       Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2(0.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
        };

        // Setup buffers
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        //glGenBuffers(1, &EBO);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GL_FLOAT) * 3));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GL_FLOAT) * 5));
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GL_FLOAT) * 8));
        glEnableVertexAttribArray(3);

        m_Shader = new Shader("Res/Shaders/basic.shader");
        m_Shader->Bind();

        int samplers[2] = { 0, 1 };
        m_Shader->SetUniform1iv("u_Textures", 2, samplers);
        Texture* texture = new Texture("Res/Textures/0.png");
        texture->Bind(0);
        Texture* texture2 = new Texture("Res/Textures/1.png");
        texture->Bind(1);

	}
	void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 transform) {
        m_Shader->Bind();
        m_Shader->SetUniformMat4f("u_Projection", projection);
        m_Shader->SetUniformMat4f("u_View", view);
        m_Shader->SetUniformMat4f("u_Model", transform);
        
        //glm::vec4 ambientColor = m_Scene->GetEnvironment()->GetAmbientColor();
        m_Shader->SetUniform4f("u_AmbientColor", 0.1f, 0.1f, 0.1f, 1.0f);
        
        //glm::vec4 lightColor = m_Scene->GetEnvironment()->GetDirectionalLightColor();
        m_Shader->SetUniform4f("u_LightColor", 1.0f, 1.0f, 1.0f, 1.0f);
        
        //glm::vec3 lightDir = m_Scene->GetEnvironment()->GetDirectionalLight();
        m_Shader->SetUniform3f("u_LightDirection", 0.1f, -0.8f, 0.0f);
        
        m_Shader->SetUniform1f("u_Strength",10);
        m_Shader->SetUniform1f("u_Shininess", 10);

        //glm::vec3 eyePos = m_Scene->GetCurrentCamera()->GetTranslation();
        m_Shader->SetUniform3f("u_EyePosition", 0.0f, 0.0f, 0.0f);
        
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
	}

    ~CubeComponent() {
        delete m_Shader;
    }
};

struct CameraComponent {
    Camera Camera;
};