#include "Window.h"
float m_LastFrameTime = 0.0f;
int main()
{
	Window window = Window();

	while (!glfwWindowShouldClose(Window::Get()->GetHandle())) {
		float time = (float)glfwGetTime();
		Timestep timestep = time - m_LastFrameTime;
		m_LastFrameTime = time;
		Window::Get()->Update(timestep);
		Window::Get()->Draw();
	}
	glfwTerminate();
}
