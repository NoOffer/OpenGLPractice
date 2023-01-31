#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Window.h"

const int WIDTH = 800, HEIGHT = 600;

int main()
{
	// OpenGL context and window initialization
	Window window;
	if (!window.Init(WIDTH, HEIGHT)) {
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// GLAD initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Main loop
	while (true) {
		window.Update();
	}

	glfwTerminate();
	return 0;
}