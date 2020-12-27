
#include <GL\glew.h>
#include "Window.h"
#include <iostream>

#include "Rendering/Shaders/Shader.h"
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>




Window::Window() 
{
    s_Instance = this;

    Init();
}

Window::~Window()
{
    delete m_Scene; 
}

Window* Window::Get() 
{
    return s_Instance;
}

GLFWwindow* Window::GetHandle() 
{ 
    return m_Window; 
}

Window* Window::s_Instance;
int Window::Init() 
{
    if (!glfwInit()) {
        std::cout << "glfw initialization failed." << std::endl;
        return -1;
    }

    int width, height;

    // Create window
    m_Window = glfwCreateWindow(1280, 720, "Sandbox", NULL, NULL);

    if (!m_Window) {
        std::cout << "Window creation failed." << std::endl;
        return -1;
    }
    glfwMakeContextCurrent(m_Window);
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

    glEnable(GL_DEPTH_TEST);

    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");


    m_Scene = new Scene();
    // TODO MOVE THIS TO SOMEWHERE APPROPRIATE

    
    return 0;
}


void Window::Update(Timestep ts) 
{
    m_Scene->Update(ts);
}

glm::vec4 m_Color;

float x = 0.0f;
float y = 0.0f;
float z = 0.0f;

void Window::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwGetFramebufferSize(m_Window, &Width, &Height);
    glViewport(0, 0, Width, Height);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

    Camera* cam = m_Scene->GetCurrentCamera();

	ImGui::NewFrame();
	{
		ImGui::Begin("Debugging!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Camera:");
        std::string msg = "X: " + std::to_string(cam->GetTranslation().x) + " Y:" + std::to_string(cam->GetTranslation().y) + " Z:" + std::to_string(cam->GetTranslation().z);

		ImGui::Text("Position:");
        ImGui::Text(msg.c_str());
		// Direction
		ImGui::Text("Direction:");
        msg = "X: " + std::to_string(cam->GetDirection().x) + " Y:" + std::to_string(cam->GetDirection().y) + " Z:" + std::to_string(cam->GetDirection().z);
        ImGui::Text(msg.c_str());


		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	} 

    {
        ImGui::Begin("Lighting");
        ImGui::ColorEdit4("Ambient Color", (float*)&m_Scene->GetEnvironment()->m_AmbientColor);
        ImGui::Text("Directional Light:");
        ImGui::SliderFloat("Strength", &m_Scene->GetEnvironment()->m_DirectionalStrength, 0.0f, 100.0f);
        ImGui::ColorEdit4("Directional Color", (float*)&m_Scene->GetEnvironment()->m_DirectionalLightColor);
        ImGui::Text("Directional direction:");
        ImGui::SliderFloat("X", &x, -1.0f, 1.0f);
        ImGui::SliderFloat("Y", &y, -1.0f, 1.0f);
        ImGui::SliderFloat("Z", &z, -1.0f, 1.0f);
        m_Scene->GetEnvironment()->SetDirectionalLight(x, y, z);
        ImGui::Text("Material");
        ImGui::SliderFloat("Shininess", &m_Scene->m_Entity->Shininess, 0.0f, 100.0f);
        ImGui::End();
    }

    m_Scene->GetEnvironment()->SetDirectionalLight(x, y, z);

	ImGui::Render();

	m_Scene->Draw();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //m_Shader->Bind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

}