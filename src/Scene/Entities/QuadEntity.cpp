#include "QuadEntity.h"
#include <GL\glew.h>
#include <wtypes.h>

QuadEntity::QuadEntity()
{
    float vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

	// Setup buffers
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    m_Shader = new Shader("Res/Shaders/basic.shader");
    m_Shader->Bind();

    Translation = glm::vec3(0, 0, 0);
    Rotation    = glm::vec3(0, 0, 0);
    Scale       = glm::vec3(1, 1, 1);
}

glm::mat4 QuadEntity::GetTransform()
{
    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::translate(transform, Translation);

    //transform = glm::rotate(transform, Rotation);
    //transform = glm::scale(transform, Scale);
   
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
    m_Shader->SetUniformMat4f("u_Model", glm::mat4(1.0f));
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
