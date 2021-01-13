#pragma once
#include "Core/Timestep.h"
#include "Rendering/Framebuffer.h"
#include <GLFW/glfw3.h>
#include "Scene/Scene.h"


class Window 
{
private:
	static Window* s_Instance;
	GLFWwindow* m_Window;

	FrameBuffer* m_Framebuffer;
	GBuffer* m_GBuffer;
	Scene* m_Scene;

	FrameBuffer* m_DeferredFrambuffer;

	int Width, Height;


public:
	Window();
	~Window();

	static Window* Get();

	int Init();
	void Update(Timestep ts);
	void Draw();

	void DrawQuad();

	GLFWwindow* GetHandle();
};
