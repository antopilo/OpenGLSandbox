
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
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_MULTISAMPLE);

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

void Window::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glfwGetFramebufferSize(m_Window, &Width, &Height);
    glViewport(0, 0, Width, Height);

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Debugging!");                          // Create a window called "Hello, world!" and append into it.

		// CAMERA
		// position
		ImGui::Text("Camera:");

		ImGui::Text("Position:");
		

		// Direction
		ImGui::Text("Direction:");
		
		//ImGui::Text(d.c_str());

		// TYPE
		//ImGui::Text("Type:");
		//const char* items[] = { "Orthographic", "Perspective" };
		//static int item = 0;
		//ImGui::Combo("Type", &item, items, IM_ARRAYSIZE(items));

		//if (item == 0)
		//	m_Cam->SetType(ORTHO);
		//else if (item == 1)
		//	m_Cam->SetType(PERSPECTIVE);

		// FOV
		//ImGui::SliderFloat("FOV", &m_Scene->GetCamera()->Fov, 1.0f, 120.0f);


		//std::string drawcall = "Draw calls: " + std::to_string(Renderer::DrawCalls);
		//ImGui::Text(drawcall.c_str());
		// Edit 1 float using a slider from 0.0f to 1.0f

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	ImGui::Render();

	m_Scene->Draw();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //m_Shader->Bind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

}