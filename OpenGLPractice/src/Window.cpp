#include "Window.h"

Window::Window()
{
	m_Window = NULL;
}

Window::~Window() {}

bool Window::Init(int width, int height)
{
	// OpenGL context and window initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window initialization
	m_Window = glfwCreateWindow(width, height, "LearnOpenGL", NULL, NULL);
	if (m_Window == NULL) {
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(m_Window);

	// Set viewport
	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});
	return true;
}

void Window::Update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}
