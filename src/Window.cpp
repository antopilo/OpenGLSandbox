
#include <GL\glew.h>
#include "Window.h"
#include <iostream>

#include "Rendering/Shaders/Shader.h"
#include <imgui\imgui.h>
#include "Rendering/Renderer.h"
#include "Scene/Entities/Entity.h"
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>

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
unsigned int captureFBO, captureRBO;
Window* Window::s_Instance;
unsigned int texture;
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

    // create viewport
   

    glGenFramebuffers(1, &m_Framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Framebuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &m_RenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    ImGui::CreateContext();
    //
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //
    //// Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ////ImGui::StyleColorsClassic();
    //
    //// Setup Platform/Renderer bindings
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
   

    // TODO: Move to separate UI layer.
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();


    Camera* cam = m_Scene->GetCurrentCamera();

	ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetWorkPos());
    ImGui::SetNextWindowSize(viewport->GetWorkSize());
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    //ImGui::DockSpace
    ImGui::DockSpaceOverViewport(viewport, dockspace_flags);
    //if (ImGui::Begin("Master Window"/*, nullptr, ImGuiWindowFlags_MenuBar*/))
    //{
    //    ImGui::TextUnformatted("DockSpace below");
    //
    //    // Declare Central dockspace
    //    int dockspaceID = ImGui::GetID("HUB_DockSpace");
    //    ImGui::DockSpace(dockspaceID, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode/*|ImGuiDockNodeFlags_NoResize*/);
    //}
    //ImGui::End();
	//{
	//	ImGui::Begin("Debugging!");                          // Create a window called "Hello, world!" and append into it.

	//	ImGui::Text("Camera:");
 //       std::string msg = "X: " + std::to_string(cam->GetTranslation().x) + " Y:" + std::to_string(cam->GetTranslation().y) + " Z:" + std::to_string(cam->GetTranslation().z);

	//	ImGui::Text("Position:");
 //       ImGui::Text(msg.c_str());
	//	// Direction
	//	ImGui::Text("Direction:");
 //       msg = "X: " + std::to_string(cam->GetDirection().x) + " Y:" + std::to_string(cam->GetDirection().y) + " Z:" + std::to_string(cam->GetDirection().z);
 //       ImGui::Text(msg.c_str());


	//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	//	ImGui::End();
	//} 

 //   {
 //       ImGui::Begin("Environment");
 //       ImGui::ColorEdit3("Ambient Color", (float*)&m_Scene->GetEnvironment()->m_AmbientColor);
 //       ImGui::End();
 //   }

    static int selected = 0;
    {
        //QuadEntity* selectedEntity = m_Scene->GetEntity(selected);
        ImGui::Begin("Scene");
        {
            ImGui::BeginChild("Buttons", ImVec2(300, 20), false);
                if (ImGui::Button("Add")) {
                    m_Scene->CreateEntity("Entity");
                }
                ImGui::SameLine();
                ImGui::Button("Remove");

            ImGui::EndChild();

            int idx = 0;
            for (Entity e : m_Scene->GetAllEntities()) {
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
           
        }
        

       
        ImGui::End();
    }

    bool show = true;
    int id = 0;
    //ImGui::ShowDemoWindow(&show);
    //ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    //ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
    glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_Scene->Draw();
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    ImGui::Begin("Viewport");
    {
        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        if (m_ViewportSize != (glm::vec2(viewportPanelSize.x, viewportPanelSize.y))) {
            m_ViewportSize = glm::vec2(viewportPanelSize.x, viewportPanelSize.y);
            ResizeFramebuffer(m_ViewportSize);
        }

        ImGui::Image((void*)texture, viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }
   

    ImGui::Begin("Materials");
    {
        ImGuiStyle& style = ImGui::GetStyle();
        int buttons_count = 20;
        float window_visible_x2 = ImGui::GetWindowPos().x + ImGui::GetWindowContentRegionMax().x;
        for (int n = 0; n < buttons_count; n++)
        {
            ImGui::PushID(n);
            ImGui::Button("Box", ImVec2(50, 50));
            float last_button_x2 = ImGui::GetItemRectMax().x;
            float next_button_x2 = last_button_x2 + style.ItemSpacing.x + 50; // Expected position if next button was on same line
            if (n + 1 < buttons_count && next_button_x2 < window_visible_x2)
                ImGui::SameLine();
            ImGui::PopID();
        }

        ImGui::End();
    }

    ImGui::Begin("Propreties");
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
        if (ImGui::Button("Add component"))
        {
            if (ImGui::BeginPopupContextItem())
            {
                // your popup code
                ImGui::EndPopup();
            }
        }

        ImGui::End();
    }

    //ImGui::Begin("Scene Window");
    //
    //ImVec2 pos = ImGui::GetCursorScreenPos();
    //
    //ImGui::GetWindowDrawList()->AddImage(
    //    (void*)m_Scene->m_Skybox->m_brdLut, ImVec2(ImGui::GetCursorScreenPos()),
    //    ImVec2(ImGui::GetCursorScreenPos().x + 200 / 2, ImGui::GetCursorScreenPos().y + 200 / 2), ImVec2(0, 1), ImVec2(1, 0));
    //
    //ImGui::End();

   


    ImGui::Render();
    Renderer::EndDraw();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //m_Shader->Bind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

}

void Window::ResizeFramebuffer(glm::vec2 size)
{
    glDeleteFramebuffers(1, &m_Framebuffer);
    glDeleteRenderbuffers(1, &m_RenderBuffer);
    glDeleteTextures(1, &texture);

    glGenFramebuffers(1, &m_Framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_Framebuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &m_RenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBuffer);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glViewport(0, 0, size.x, size.y);
}