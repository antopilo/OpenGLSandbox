
#include <GL\glew.h>
#include "Window.h"
#include <iostream>

#include "Rendering/Shaders/Shader.h"
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
#include "Rendering/Renderer.h"




Window::Window() 
{
    s_Instance = this;

    Init();
    Renderer::Init();
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
    Renderer::BeginDraw(m_Scene->GetCurrentCamera());

    // TODO: move to window event.
    glfwGetFramebufferSize(m_Window, &Width, &Height);
    glViewport(0, 0, Width, Height);

    // TODO: Move to separate UI layer.
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

        ImGui::End();
    }

    static int selected = 0;
    {
        //QuadEntity* selectedEntity = m_Scene->GetEntity(selected);
        ImGui::Begin("Scene");
        {
            ImGui::BeginChild("Buttons", ImVec2(150, 20), false);
            if (ImGui::Button("Add")) {
                //m_Scene->CreateEntity("Entity");
            }
            ImGui::SameLine();
            ImGui::Button("Remove");

            ImGui::EndChild();

            ImGui::BeginChild("left pane", ImVec2(150, 0), true);

            
            //for (int e = 0; e < m_Scene->GetEntityCount(); e++) {
            //    QuadEntity* entity = m_Scene->GetEntity(e);
            //    if (ImGui::Selectable((std::string(entity->m_Name.data())).c_str(), selected == e)) {
            //        selected = e;
            //        selectedEntity = m_Scene->GetEntity(e);
            //    }
            //        
            //}
            ImGui::EndChild();
            
           
        }
        
        float test = 0.0f;
        //ImGui::SameLine();
        //{
        //    ImGui::BeginGroup();
        //    ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
        //    ImGui::Text("MyObject: %d", selected);
        //    ImGui::Separator();
        //    if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        //    {
        //        if (ImGui::BeginTabItem("Properties"))
        //        {
        //            //ImGui::InputText("Name:", selectedEntity->m_Name.data(), 12);
        //            ImGui::Text("Translation");
        //            {
        //                //X
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.16f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        //                if (ImGui::Button("X", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##X", &selectedEntity->Translation.x, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //                ImGui::SameLine();
        //                // Y
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        //                if (ImGui::Button("Y", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##Y", &selectedEntity->Translation.y, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //                ImGui::SameLine();
        //                // Z
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        //                if (ImGui::Button("Z", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##Z", &selectedEntity->Translation.z, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //            }
        //            ImGui::Text("Rotation");
        //            {
        //                //X
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.16f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        //                if (ImGui::Button("X", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##RX", &selectedEntity->Rotation.x, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //                ImGui::SameLine();
        //                // Y
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        //                if (ImGui::Button("Y", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##RY", &selectedEntity->Rotation.y, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //                ImGui::SameLine();
        //                // Z
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        //                if (ImGui::Button("Z", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##RZ", &selectedEntity->Rotation.z, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //            }
        //            ImGui::Text("Scale");
        //            {
        //                //X
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.16f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        //                if (ImGui::Button("X", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##SX", &selectedEntity->Scale.x, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //                ImGui::SameLine();
        //                // Y
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        //                if (ImGui::Button("Y", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##SY", &selectedEntity->Scale.y, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //                ImGui::SameLine();
        //                // Z
        //                ImGui::PushItemWidth(50);
        //                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        //                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        //                if (ImGui::Button("Z", ImVec2(20, 20))) {
        //                    // reset value
        //                }
        //                ImGui::PopStyleColor(3);
        //                ImGui::SameLine();
        //                ImGui::DragFloat("##SZ", &selectedEntity->Scale.z, 0.1f, 0.0f, 0.0f, "%.2f");
        //                ImGui::PopItemWidth();
        //            }
        //            // Components.

        //            ImGui::EndTabItem();
        //        }
        //        if (ImGui::BeginTabItem("Material"))
        //        {
        //            ImGui::SliderFloat("Shininess", &selectedEntity->Shininess, 0.0f, 100.0f);
        //            ImGui::EndTabItem();
        //        }
        //        ImGui::EndTabBar();
        //    }
        //    ImGui::EndChild();
        //    ImGui::EndGroup();
        //}

       
        ImGui::End();
    }

    m_Scene->GetEnvironment()->SetDirectionalLight(x, y, z);

	ImGui::Render();

	m_Scene->Draw();

    Renderer::EndDraw();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //m_Shader->Bind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

}