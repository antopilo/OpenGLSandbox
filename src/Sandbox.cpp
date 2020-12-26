#include "Window.h"

int main()
{
	Window window = Window();

	while (!glfwWindowShouldClose(Window::Get()->GetHandle())) {
		Window::Get()->Draw();
	}
	glfwTerminate();
}
