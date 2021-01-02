#include "Skybox.h"
#include <GL\glew.h>
#include "Renderer.h"
#include "Textures/Cubemap.h"
glm::vec3 Skybox::vertices[36] {
       glm::vec3(-0.5f, -0.5f, -0.5f),
       glm::vec3(0.5f,  -0.5f, -0.5f),
       glm::vec3(0.5f,   0.5f, -0.5f),
       glm::vec3(0.5f,   0.5f, -0.5f),
       glm::vec3(-0.5f,  0.5f, -0.5f),
       glm::vec3(-0.5f, -0.5f, -0.5f),

       glm::vec3(-0.5f, -0.5f,  0.5f),
       glm::vec3(0.5f,  -0.5f,  0.5f),
       glm::vec3(0.5f,   0.5f,  0.5f),
       glm::vec3(0.5f,   0.5f,  0.5f),
       glm::vec3(-0.5f,  0.5f,  0.5f),
       glm::vec3(-0.5f, -0.5f,  0.5f),
                                     
       glm::vec3(-0.5f,  0.5f,  0.5f),
       glm::vec3(-0.5f,  0.5f, -0.5f),
       glm::vec3(-0.5f, -0.5f, -0.5f),
       glm::vec3(-0.5f, -0.5f, -0.5f),
       glm::vec3(-0.5f, -0.5f,  0.5f),
       glm::vec3(-0.5f,  0.5f,  0.5f),

       glm::vec3(0.5f,  0.5f,  0.5f),
       glm::vec3(0.5f,  0.5f, -0.5f),
       glm::vec3(0.5f, -0.5f, -0.5f),
       glm::vec3(0.5f, -0.5f, -0.5f),
       glm::vec3(0.5f, -0.5f,  0.5f),
       glm::vec3(0.5f,  0.5f,  0.5f),

       glm::vec3(-0.5f, -0.5f, -0.5f),
       glm::vec3(0.5f,  -0.5f, -0.5f),
       glm::vec3(0.5f,  -0.5f,  0.5f),
       glm::vec3(0.5f,  -0.5f,  0.5f),
       glm::vec3(-0.5f, -0.5f,  0.5f),
       glm::vec3(-0.5f, -0.5f, -0.5f),

       glm::vec3(-0.5f, 0.5f, -0.5f) ,
       glm::vec3(0.5f,  0.5f, -0.5f) ,
       glm::vec3(0.5f,  0.5f,  0.5f) ,
       glm::vec3(0.5f,  0.5f,  0.5f) ,
       glm::vec3(-0.5f, 0.5f,  0.5f) ,
       glm::vec3(-0.5f, 0.5f, -0.5f)
};

Skybox::Skybox(){
    // Setup buffers
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    // TODO: mem leak.
    m_Texture = new CubemapTexture("Res/Textures/Skyboxes/1/japan");
}

void Skybox::Draw(glm::mat4 projection, glm::mat4 view) {
    
    glDepthMask(GL_FALSE);
    m_Texture->Bind(3);

    Renderer::m_SkyboxShader->Bind();

    Renderer::m_SkyboxShader->SetUniformMat4f("projection", projection);
    Renderer::m_SkyboxShader->SetUniformMat4f("view", view);

    Renderer::m_SkyboxShader->SetUniform1i("skybox", 3);
    
    // ... set view and projection matrix
    glBindVertexArray(VAO);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(GL_TRUE);
    //Renderer::m_Shader->SetUniform4f("u_AmbientColor", 1.0f, 1.0f, 1.0f, 1.0f);
}

