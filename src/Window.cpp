
#include <GL\glew.h>
#include "Window.h"
#include <iostream>

#include "Rendering/Shaders/Shader.h"
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
#include "Rendering/Renderer.h"
#include "Scene/Entities/Entity.h"

Window::Window() 
{
    s_Instance = this;

    Init();
    Renderer::Init();

    m_Scene->Init();
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

    glEnable(GL_MULTISAMPLE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glClearColor(0.019f, 0.501f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
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
Entity selectedEntity;
bool init = false;
void Window::Draw()
{
    if (!init) {
        selectedEntity = m_Scene->GetAllEntities().at(0);
        init = true;
    }
        
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
        ImGui::Begin("Environment");
        ImGui::ColorEdit3("Ambient Color", (float*)&m_Scene->GetEnvironment()->m_AmbientColor);
        ImGui::End();
    }

    std::vector<Entity> entities = m_Scene->GetAllEntities();
    
    static int selected = 0;
    {
        //QuadEntity* selectedEntity = m_Scene->GetEntity(selected);
        ImGui::Begin("Scene");
        {
            ImGui::BeginChild("Buttons", ImVec2(150, 20), false);
            if (ImGui::Button("Add")) {
                m_Scene->CreateEntity("Entity");
            }
            ImGui::SameLine();
            ImGui::Button("Remove");

            ImGui::EndChild();

            ImGui::BeginChild("left pane", ImVec2(150, 0), true);

            int idx = 0;
            for (Entity e : entities) {
                std::string name = e.GetComponent<NameComponent>().Name;
                if (ImGui::Selectable(name.c_str(), selected == idx)) {
                    selected = idx;
                    selectedEntity = e;
                }
                if (ImGui::BeginPopupContextItem())
                {
                    // your popup code
                    ImGui::EndPopup();
                }
                idx++;
            }
            ImGui::EndChild();
            
           
        }

        float test = 0.0f;
        ImGui::SameLine();
        ImGui::BeginGroup();
        ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
        ImGui::Text("MyObject: %d", selected);
        ImGui::Separator();
        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Properties"))
            {
                //ImGui::InputText("Name:", selectedEntity->m_Name.data(), 12);
                TransformComponent& component = selectedEntity.GetComponent<TransformComponent>();
                component.DrawEditor();
                ImGui::Separator();

                if (selectedEntity.HasComponent<LightComponent>()) {
                    selectedEntity.GetComponent<LightComponent>().DrawEditor();
                    ImGui::Separator();
                }

                if (selectedEntity.HasComponent<CameraComponent>()) {
                    selectedEntity.GetComponent<CameraComponent>().DrawEditor();
                    ImGui::Separator();
                }
                    
                if (selectedEntity.HasComponent<MeshComponent>()) {
                    selectedEntity.GetComponent<MeshComponent>().DrawEditor();
                    ImGui::Separator();
                }
                if(ImGui::Button("Add component"))
                { 
                    if (ImGui::BeginPopupContextItem())
                    {
                        // your popup code
                        ImGui::EndPopup();
                    }
                }

                ImGui::EndTabItem();
            }
            //if (ImGui::BeginTabItem("Material"))
            //{
            //    ImGui::SliderFloat("Shininess", &selectedEntity->Shininess, 0.0f, 100.0f);
            //    ImGui::EndTabItem();
            //}
            ImGui::EndTabBar();
        }
        ImGui::EndChild();
        ImGui::EndGroup();
        

       
        ImGui::End();
    }

	

	m_Scene->Draw();


    ImGui::Begin("Scene Window");

    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage(
        (void*)m_Scene->m_Skybox->m_brdLut, ImVec2(ImGui::GetCursorScreenPos()),
        ImVec2(ImGui::GetCursorScreenPos().x + 200 / 2, ImGui::GetCursorScreenPos().y + 200 / 2), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();

    ImGui::Render();
    Renderer::EndDraw();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //m_Shader->Bind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

}