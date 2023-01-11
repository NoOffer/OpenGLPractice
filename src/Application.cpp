// Stream control
#include <iostream>
#include <fstream>
#include <sstream>

// GL libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Helper libraries
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Custom abstractions
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "GUI.h"

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
			-1.0f, -1.0f, 0.0f, 0.0f,  // 0
			 1.0f, -1.0f, 1.0f, 0.0f,  // 1
			 1.0f,  1.0f, 1.0f, 1.0f,  // 2
			-1.0f,  1.0f, 0.0f, 1.0f,  // 3
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

		// Projection matrix
		glm::mat4 projMatrix = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, 0.0f, 1.0f);
		glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
		glm::mat4 modelMatrix = glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(320.0f, 240.0f, 0.0f)), glm::vec3(200.0f, 200.0f, 1.0f));
		shader.SetUniformMat4f("u_MVP", projMatrix * viewMatrix * modelMatrix);

		Texture texture("res/textures/TestTexture.png");  // Create texture
		// Assign texture to shader
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		// GUI setup
		GUI::Init(window, "#version 330 core");

		float f = 0.0f;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

		// ------------------------------------------------------------------------------------------------------------------------------------ Main Loop
		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window)) {
			/* Render here */
			Renderer::Clear();

			// Drawcall
			Renderer::Draw(va, ib, shader);

			GUI::NewFrame();

			{
				ImGui::Begin("Sample Window");                          // Create a window called "Hello, world!" and append into it.

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

				ImGui::End();
			}

			GUI::Render();

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();

			///* Log error */
			//std::cout << "Test Breakpoint 1" << std::endl;
			//LogError();

			/* Log error */
			//std::cout << "Test Breakpoint 2" << std::endl;
			LogError();
		}
	}

	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}