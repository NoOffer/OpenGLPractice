#include <iostream>

// GL libraries
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// Helper libraries
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Custom abstractions
#include "Window.h"
#include "Model.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

// ---------------------------------------------------------------------------------------------------------------------------- Custom Helper Methods
static bool LogError()
{
	GLenum e = glGetError();
	if (e) {
		while (e) {
			std::cout << "[OpenGL Error] (" << e << ")" << std::endl;
			e = glGetError();
		}
		__debugbreak();
		return false;
	}
	return true;
}

// -------------------------------------------------------------------------------------------------------------------------------------- Main Method
int main(void)
{

	// GLFW initialization
	if (!glfwInit()) {
		std::cout << "Fail to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	Window window;
	if (!window.Init(640, 480)) {
		glfwTerminate();
		return -1;
	}

	// Set refresh rate
	glfwSwapInterval(1);

	// GLAD initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Print out current OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		// Render content initialization
		Model model = Model();
		model.Scale(10.0f, 10.0f, 10.0f);

		// Create shader
		Shader shader(
			"res/shaders/TestVert.shader",
			"res/shaders/TestFrag.shader"
		);
		model.SetShader(shader);

		// Projection matrix
		glm::mat4 projMatrix = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 100.0f);
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -100.0f));
		glm::mat4 modelMatrix = model.GetModelMatrix();
		shader.SetUniformMat4f("u_MVP", projMatrix * viewMatrix * modelMatrix);

		// Create texture
		Texture texture("res/textures/TestTexture.png");
		// Assign texture to shader
		//texture.Bind(0);
		//shader.SetUniform1i("u_Texture", 0);

		// Enable blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// ------------------------------------------------------------------------------------------------------------------------------------ Main Loop
		while (!window.Alive()) {
			// Clear
			glClear(GL_COLOR_BUFFER_BIT);
			//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

			model.Draw();

			window.Update();

			LogError();
		}
	}

	glfwTerminate();
	return 0;
}