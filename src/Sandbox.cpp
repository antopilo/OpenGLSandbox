#include <iostream>
#include "glfw3.h"
int main()
{
    if (!glfwInit())
        std::cout << "glfw initialization failed." << std::endl;


    int width, height;

    // Create window
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Sandbox", NULL, NULL);

    if (!window) 
        std::cout << "Window creation failed." << std::endl;

    glfwMakeContextCurrent(window);

    // Loop
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);

        glfwSwapBuffers(window);
    }

    glfwTerminate();
}
