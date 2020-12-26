#pragma once
#include "Core/Timestep.h"
#include <GLFW/glfw3.h>
#include "Scene/Scene.h"

class Window 
{
private:
	static Window* s_Instance;
	GLFWwindow* m_Window;

	Scene* m_Scene;

	int Width, Height;
public:
	Window();
	~Window();

	static Window* Get();

	int Init();
	void Update(Timestep ts);
	void Draw();

	GLFWwindow* GetHandle();
};
