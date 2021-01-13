
#include <GL\glew.h>
#include "Window.h"
#include <iostream>

#include "Rendering/Shaders/Shader.h"
#include <imgui\imgui.h>
#include "Rendering/Renderer.h"
#include "Scene/Entities/Entity.h"
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>
unsigned int vbo;
unsigned int vao;

float vertices[] = {
       1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
       1.0f, -1.0f, 0.0f,   1.0f, 0.0f,
      -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,

       1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
      -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
      -1.0f,  1.0f, 0.0f,  0.0f, 1.0f
};
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

    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    glClearColor(0.019f, 0.501f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_CULL_FACE);
    // create viewport
   
    m_DeferredFrambuffer = new FrameBuffer(false, glm::vec2(1920, 1080), GL_COLOR_ATTACHMENT0);
    m_DeferredFrambuffer->SetTexture(new Texture(glm::vec2(1920, 1080), GL_RGB));

    m_Framebuffer = new FrameBuffer(true, glm::vec2(1920, 1080), GL_COLOR_ATTACHMENT0);
    m_Framebuffer->SetTexture(new Texture(glm::vec2(1920, 1080), GL_RGB));

    m_GBuffer = new GBuffer(glm::vec2(1920, 1080));

    // Temporary quad vbo for deferred.
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);


    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    m_Scene = new Scene();

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
    if (!init) 
    {
        selectedEntity = m_Scene->GetAllEntities().at(0);
        init = true;
    }
        
    Camera* cam = m_Scene->GetCurrentCamera();
    Renderer::BeginDraw(cam);

    // TODO: Move to separate UI layer.
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();

	ImGui::NewFrame();

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->GetWorkPos());
    ImGui::SetNextWindowSize(viewport->GetWorkSize());
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    ImGui::DockSpaceOverViewport(viewport, dockspace_flags);

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
            if (ImGui::Button("Remove"))
            {
                m_Scene->DestroyEntity(selectedEntity);
                selectedEntity = m_Scene->GetAllEntities().at(0);
            };

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

	//glCullFace(GL_FRONT);
    m_Scene->DrawShadows();
    //glCullFace(GL_BACK);
    // Drawing to texture.

   
    
    ImGui::Begin("ShadowMap");
    {

        ImVec2 regionAvail = ImGui::GetContentRegionAvail();
        glm::vec2 viewportPanelSize = glm::vec2(regionAvail.x, regionAvail.y);

        if (selectedEntity.HasComponent<LightComponent>())
            ImGui::Image((void*)selectedEntity.GetComponent<LightComponent>().m_Framebuffer->GetTexture()->GetID(), regionAvail, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
        
    }



    m_GBuffer->Bind();
        m_Scene->DrawGBuffer();
    m_GBuffer->Unbind();

    DrawQuad();

    ImGui::Begin("Deferred output");
    {

        ImVec2 regionAvail = ImGui::GetContentRegionAvail();
        glm::vec2 viewportPanelSize = glm::vec2(regionAvail.x, regionAvail.y);


        ImGui::Image((void*)m_DeferredFrambuffer->GetTexture()->GetID(), regionAvail, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();

    }

    // Draw rect
    Renderer::m_DeferredShader->Bind();

    ImGui::Begin("depth");
    {
        ImVec2 regionAvail = ImGui::GetContentRegionAvail();
        glm::vec2 viewportPanelSize = glm::vec2(regionAvail.x, regionAvail.y);

    
        ImGui::Image((void*)m_GBuffer->gDepth, regionAvail, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    ImGui::Begin("Albedo");
    {
        ImVec2 regionAvail = ImGui::GetContentRegionAvail();
        glm::vec2 viewportPanelSize = glm::vec2(regionAvail.x, regionAvail.y);

        // If viewport is resized
        if (m_GBuffer->GetSize() != viewportPanelSize)
        {
            // Update FBO size and camera aspect ratio.
            //m_Framebuffer->UpdateSize(viewportPanelSize);
            //cam->OnWindowResize(viewportPanelSize.x, viewportPanelSize.y);
        }

        ImGui::Image((void*)m_GBuffer->gAlbedo, regionAvail, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    ImGui::Begin("Material");
    {
        ImVec2 regionAvail = ImGui::GetContentRegionAvail();
        glm::vec2 viewportPanelSize = glm::vec2(regionAvail.x, regionAvail.y);
    
        // If viewport is resized
        if (m_GBuffer->GetSize() != viewportPanelSize)
        {
            // Update FBO size and camera aspect ratio.
            //m_Framebuffer->UpdateSize(viewportPanelSize);
            //cam->OnWindowResize(viewportPanelSize.x, viewportPanelSize.y);
        }
    
        ImGui::Image((void*)m_GBuffer->gMaterial, regionAvail, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    ImGui::Begin("Normal");
    {
        ImVec2 regionAvail = ImGui::GetContentRegionAvail();
        glm::vec2 viewportPanelSize = glm::vec2(regionAvail.x, regionAvail.y);

        // If viewport is resized
        if (m_GBuffer->GetSize() != viewportPanelSize)
        {
            // Update FBO size and camera aspect ratio.
            //m_Framebuffer->UpdateSize(viewportPanelSize);
            //cam->OnWindowResize(viewportPanelSize.x, viewportPanelSize.y);
        }

        ImGui::Image((void*)m_GBuffer->gNormal, regionAvail, ImVec2(0, 1), ImVec2(1, 0));
        ImGui::End();
    }

    m_Framebuffer->Bind();
    m_Scene->Draw();
    m_Framebuffer->Unbind();
    ImGui::Begin("Viewport");
    {
        ImVec2 regionAvail = ImGui::GetContentRegionAvail();
        glm::vec2 viewportPanelSize = glm::vec2(regionAvail.x, regionAvail.y);

        // If viewport is resized
        if (m_Framebuffer->GetSize() != viewportPanelSize)
        {
            // Update FBO size and camera aspect ratio.
            m_Framebuffer->UpdateSize(viewportPanelSize);
            cam->OnWindowResize(viewportPanelSize.x, viewportPanelSize.y);
        }

        ImGui::Image((void*)m_Framebuffer->GetTexture()->GetID(), regionAvail, ImVec2(0, 1), ImVec2(1, 0));
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

        if (selectedEntity.HasComponent<NameComponent>()) {
            selectedEntity.GetComponent<NameComponent>().DrawEditor();
            ImGui::Separator();
        }

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
            ImGui::OpenPopup("add_component_popup");
            
        }
        if (ImGui::BeginPopup("add_component_popup"))
        {
            if (ImGui::MenuItem("Light Component"))
                selectedEntity.AddComponent<LightComponent>();
            if (ImGui::MenuItem("Mesh Component"))
                selectedEntity.AddComponent<MeshComponent>();
            if (ImGui::MenuItem("Camera Component"))
                selectedEntity.AddComponent<CameraComponent>();
            // your popup code
            ImGui::EndPopup();
        }
        ImGui::End();
    }

    ImGui::Render();
    Renderer::EndDraw();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    //m_Shader->Bind();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();

}



void Window::DrawQuad()
{
    Renderer::m_DeferredShader->Bind();

    m_DeferredFrambuffer->Bind();
    
    m_Scene->DrawDeferred();

    glActiveTexture(GL_TEXTURE0 + 5);
    glBindTexture(GL_TEXTURE_2D, m_GBuffer->gAlbedo);

    glActiveTexture(GL_TEXTURE0 + 6);
    glBindTexture(GL_TEXTURE_2D, m_GBuffer->gNormal);

    glActiveTexture(GL_TEXTURE0 + 7);
    glBindTexture(GL_TEXTURE_2D, m_GBuffer->gMaterial);

    glActiveTexture(GL_TEXTURE0 + 8);
    glBindTexture(GL_TEXTURE_2D, m_GBuffer->gDepth);

    Renderer::m_DeferredShader->SetUniform1i("m_Albedo", 5);
    Renderer::m_DeferredShader->SetUniform1i("m_Depth", 8);
    Renderer::m_DeferredShader->SetUniform1i("m_Normal", 6);
    Renderer::m_DeferredShader->SetUniform1i("m_Material", 7);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    m_DeferredFrambuffer->Unbind();
}
