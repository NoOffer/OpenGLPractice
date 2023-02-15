#include <iostream>

// GL libraries
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// Helper libraries
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Custom abstractions
#include "Window.h"
#include "Camera.h"
#include "PointLight.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"

const int WIDTH = 800;
const int HEIGHT = 800;

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
	if (!window.Init(WIDTH, HEIGHT)) {
		glfwTerminate();
		return -1;
	}

	//// Set refresh rate
	//glfwSwapInterval(1);

	// GLAD initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Print out current OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		// Create camera
		Camera camera(45.0f, glm::uvec2(WIDTH, HEIGHT));
		camera.Translate(0.0f, 0.0f, -20.0f);

		// Render content initialization
		PointLight pointLight(glm::vec3(1.0f, 0.7f, 0.2f));
		Model model = Model();

		// Create shader
		Shader shader(
			"res/shaders/TestVert.shader",
			"res/shaders/TestFrag.shader"
		);
		model.SetShader(shader);

		// Projection matrix
		glm::mat4 projMatrix = camera.GetProjMatrix();
		glm::mat4 viewMatrix = camera.GetViewMatrix();
		glm::mat4 modelMatrix = model.GetModelMatrix();
		shader.SetUniformMat4f("u_MVP", projMatrix * viewMatrix * modelMatrix);

		// Create texture
		Texture texture("res/textures/TestTexture.png");
		// Assign texture to shader
		//texture.Bind(0);
		//shader.SetUniform1i("u_Texture", 0);

		// Light color
		shader.SetUniform3f("u_LightColor", pointLight.GetColor());

		// Enable blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Enable culling
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		// Enable depth buffer
		glEnable(GL_DEPTH_TEST);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		float currentFrame = glfwGetTime();
		float deltaTime = 0.0f;
		// ------------------------------------------------------------------------------------------------------------------------------------ Main Loop
		while (!window.Alive()) {
			// Calculate delta time
			deltaTime = glfwGetTime() - currentFrame;
			currentFrame = glfwGetTime();

			// Clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

			model.Rotate(0.2f, glm::vec3(0.0f, 1.0f, 0.0f));
			shader.SetUniformMat4f("u_MVP", projMatrix * viewMatrix * model.GetModelMatrix());
			model.Draw();

			window.Update();

			LogError();
		}
	}

	glfwTerminate();
	return 0;
}