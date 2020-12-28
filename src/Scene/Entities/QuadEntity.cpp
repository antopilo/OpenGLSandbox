#include "QuadEntity.h"
#include <GL\glew.h>
#include <wtypes.h>
#include "../../Rendering/Shaders/Texture.h"
#include "../Scene.h"
#include "../../Rendering/Vertex.h"
QuadEntity::QuadEntity(Scene* scene)
{
    m_Scene = scene;

    Vertex vertices[] = {
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2( 0.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2( 1.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2( 1.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2( 1.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2( 0.0f, 1.0f), glm::vec3(0, 0, -1), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2( 0.0f, 0.0f), glm::vec3(0, 0, -1), 1.0f },
                                           
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2( 0.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2( 1.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2( 1.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2( 1.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2( 0.0f, 1.0f), glm::vec3(0, 0, 1), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2( 0.0f, 0.0f), glm::vec3(0, 0, 1), 1.0f },
                                           
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2( 1.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2( 1.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2( 0.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2( 0.0f, 1.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2( 0.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2( 1.0f, 0.0f), glm::vec3(-1, 0, 0), 1.0f },
                                           
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2( 1.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2( 1.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2( 0.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2( 0.0f, 1.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2( 0.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2( 1.0f, 0.0f), glm::vec3(1, 0, 0), 1.0f },
                                           
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2( 0.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f, -0.5f),  glm::vec2( 1.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2( 1.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f, -0.5f,  0.5f),  glm::vec2( 1.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec2( 0.0f, 0.0f), glm::vec3(0, -1, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2( 0.0f, 1.0f), glm::vec3(0, -1, 0), 1.0f },
                                           
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2( 0.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f, -0.5f),  glm::vec2( 1.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2( 1.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(0.5f,  0.5f,  0.5f),  glm::vec2( 1.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec2( 0.0f, 0.0f), glm::vec3(0, 1, 0), 1.0f },
        Vertex{ glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec2( 0.0f, 1.0f), glm::vec3(0, 1, 0), 1.0f },
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

    Translation = glm::vec3(0, 0, 0);
    Rotation    = glm::vec3(0, 0, 0);
    Scale       = glm::vec3(1, 1, 1);
}

glm::mat4 QuadEntity::GetTransform()
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, Translation);
    transform = glm::rotate(transform, Rotation.x, glm::vec3(1, 0 ,0));
    transform = glm::rotate(transform, Rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, Rotation.z, glm::vec3(0, 0, 1));
    transform = glm::scale(transform, Scale);
   
    return transform;
}

glm::mat3 QuadEntity::GetNormalTransform() {
    glm::mat4 transform = glm::mat3(1.0f);
    transform = glm::rotate(transform, Rotation.x, glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, Rotation.y, glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, Rotation.z, glm::vec3(0, 0, 1));
    return transform;
}

QuadEntity::~QuadEntity()
{
    delete m_Shader;
}

void QuadEntity::Update(Timestep ts)
{
    //...
}

void QuadEntity::Draw(glm::mat4 projection, glm::mat4 transform)
{
    m_Shader->Bind();
    m_Shader->SetUniformMat4f("u_Projection", projection);
    m_Shader->SetUniformMat4f("u_View", transform);
    m_Shader->SetUniformMat4f("u_Model", GetTransform());

    glm::vec4 ambientColor = m_Scene->GetEnvironment()->GetAmbientColor();
    m_Shader->SetUniform4f("u_AmbientColor", ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);

    glm::vec4 lightColor = m_Scene->GetEnvironment()->GetDirectionalLightColor();
    m_Shader->SetUniform4f("u_LightColor", lightColor.r, lightColor.g, lightColor.b, 1.0f);

    glm::vec3 lightDir = m_Scene->GetEnvironment()->GetDirectionalLight();
    m_Shader->SetUniform3f("u_LightDirection", lightDir.x, lightDir.y, lightDir.z);

    m_Shader->SetUniform1f("u_Strength", m_Scene->GetEnvironment()->GetDirectionalStrength());
    m_Shader->SetUniform1f("u_Shininess", Shininess);
    glm::vec3 eyePos = m_Scene->GetCurrentCamera()->GetTranslation();
    m_Shader->SetUniform3f("u_EyePosition", eyePos.x, eyePos.y, eyePos.z);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
