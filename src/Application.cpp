// Stream control
#include <iostream>
#include <fstream>
#include <sstream>

// GL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Custom abstractions
#include "Renderer.h"
#include "VertexBuffer.h"
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
	GLFWwindow* window;

	// Initialize GLFW
	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	// Set refresh rate
	glfwSwapInterval(1);

	// Initialize GLEW
	if (glewInit() != GLEW_OK) {
		std::cout << "GLEW Error!" << std::endl;
		return -1;
	}

	// Print out current OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Render content initialization
	{
		// Vertices
		float vertPos[16] = {
			// Position   UV Coord
			-0.5f, -0.5,  0.0f, 0.0f,  // 0
			 0.5f, -0.5,  1.0f, 0.0f,  // 1
			 0.5f,  0.5f, 1.0f, 1.0f,  // 2
			-0.5f,  0.5f, 0.0f, 1.0f,  // 3
		};
		VertexBuffer vb(vertPos, sizeof(float) * 16);	  // Create vertext buffer
		VertexBufferLayout layout;						  // Create buffer layout
		// Setup layout
		layout.Push<float>(2);
		layout.Push<float>(2);
		VertexArray va;									  // Create vertex array
		// Bind vb and layout to va
		va.SetupArray(vb, layout);

		// Enable blending
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		// Indices
		unsigned int vertIdx[6] = {
			0, 1, 2,
			0, 2, 3
		};
		IndexBuffer ib(vertIdx, 6);						  // Create index buffer

		ShaderProgram shader(							  // Create shader
			"res/shaders/TestVert.shader",
			"res/shaders/TestFrag.shader"
		);

		Texture texture("res/textures/TestTexture.png");  // Create texture
		// Assign texture to shader
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		Renderer renderer;

		// ------------------------------------------------------------------------------------------------------------------------------------ Main Loop
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window)) {
			/* Render here */
			renderer.Clear();

			//// Uniform example
			//shader.Bind();
			//shader.SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

			// Drawcall
			renderer.Draw(va, ib, shader);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();

			/* Log error */
			//std::cout << "Test Breakpoint 1" << std::endl;
			LogError();

			/* Log error */
			//std::cout << "Test Breakpoint 2" << std::endl;
			LogError();
		}
		shader.~ShaderProgram();
	}

	glfwTerminate();
	return 0;
}