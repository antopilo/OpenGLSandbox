#include <iostream>

#include <GL/glew.h>
#include "glfw3.h"
#include "Rendering/Shaders/Shader.h"

float vertices[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
};

int main()
{
    if (!glfwInit()) {
        std::cout << "glfw initialization failed." << std::endl;
        return -1;
    }
       


    int width, height;

    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Sandbox", NULL, NULL);

    if (!window) {
        std::cout << "Window creation failed." << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);
    std::cout << glGetString(GL_VERSION) << std::endl;

    if (glewInit() != GLEW_OK) {
        std::cout << "GLEW initialization failed!";
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glClearColor(0.019f, 0.501f, 1.0f, 1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_MULTISAMPLE);

    Shader shader = Shader("Res/Shaders/basic.shader");
    shader.Bind();

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);


 
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
  
        shader.Bind();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
