#include <iostream>

// GL libraries
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// Helper libraries
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "core/core.h"

// ------------------------------------------------------------------------------------------------------------ Custom Helper Methods
static bool LogError()
{
	GLenum e = glGetError();
	if (e)
	{
		while (e)
		{
			std::cout << "[OpenGL Error] (" << e << ")" << std::endl;
			e = glGetError();
		}
		__debugbreak();
		return false;
	}
	return true;
}

const int WIDTH = 800;
const int HEIGHT = 800;

// ---------------------------------------------------------------------------------------------------------------------- Main Method
int main(void)
{
	// GLFW initialization																						
	if (!glfwInit())
	{
		std::cout << "Fail to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window initialization
	GLFWwindow* m_Window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Example", NULL, NULL);
	if (m_Window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_Window);

	// GLAD initialization																						
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set viewport
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	//// Set refresh rate																						
	//glfwSwapInterval(1);	

	// Print out current OpenGL version																			
	std::cout << glGetString(GL_VERSION) << std::endl;

	{
		// Create camera																						
		Camera camera(45.0f, glm::uvec2(WIDTH, HEIGHT));
		camera.Translate(0.0f, 3.0f, 5.0f);

		// Render content initialization																		
		PointLight pointLight(glm::vec3(1.0f, 0.9f, 0.8f));
		pointLight.Translate(-1.0f, 1.0f, 1.0f);
		Model model = Model();

		// Create shader																						
		Shader shader(
			"res/shaders/TestVert.shader",
			"res/shaders/TestFrag.shader"
		);
		model.SetShader(shader);

		// Projection matrix																					
		glm::mat4 viewMatrix = camera.GetViewMatrix();
		glm::mat4 projMatrix = camera.GetProjMatrix();
		shader.SetUniformMat4f("u_Matrix_VP", projMatrix * viewMatrix);
		glm::mat4 modelMatrix = model.GetModelMatrix();
		shader.SetUniformMat4f("u_Matrix_M", modelMatrix);
		shader.SetUniformMat3f("u_Matrix_M_Normal", glm::mat3(glm::transpose(glm::inverse(modelMatrix))));

		// Create texture																						
		Texture texture("res/textures/TestTexture.png");
		// Assign texture to shader																				
		texture.Bind(0);
		// Set uniforms
		{
			shader.SetUniform1i("u_Texture", 0);

			// Light info																							
			shader.SetUniform3f("u_LightPos", pointLight.GetPosition());
			shader.SetUniform3f("u_LightColor", pointLight.GetColor());
			// Camera info																							
			shader.SetUniform3f("u_CamPos", camera.GetPosition());
			// Material info																						
			shader.SetUniform1f("material.smoothness", exp2(5.0f));
			shader.SetUniform1f("material.ambient", 0.2f);
		}

		// Enable blending																						
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// Enable culling																						
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		// Enable depth buffer																					
		glEnable(GL_DEPTH_TEST);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);															

		double currentTime = glfwGetTime();
		double deltaTime = 0.0f;

		float t = 0.0f;
		// ---------------------------------------------------------------------------------------------------------------- Main Loop
		while (!glfwWindowShouldClose(m_Window))
		{
			// Calculate delta time																				
			deltaTime = glfwGetTime() - currentTime;
			currentTime = glfwGetTime();

			// Clear																							
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);																

			model.Rotate(0.0f, 60.0f * deltaTime, 0.0f);

			modelMatrix = model.GetModelMatrix();
			shader.SetUniformMat4f("u_Matrix_M", modelMatrix);
			shader.SetUniformMat3f("u_Matrix_M_Normal", glm::mat3(glm::transpose(glm::inverse(modelMatrix))));

			model.Draw();

			// Poll events
			glfwPollEvents();

			// Handle input
			{
				if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				{
					glfwSetWindowShouldClose(m_Window, true);
				}
				//if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
				//{
				//	camera.Translate(0.0f, 0.0f, 1.0f * deltaTime);
				//}
				//if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
				//{
				//	camera.Translate(0.0f, 0.0f, -1.0f * deltaTime);
				//}
				if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
				{
					t -= 2.0f * deltaTime;
					camera.SetPosition(sin(t) * 5.0f, 3.0f, cos(t) * 5.0f);
				}
				if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
				{
					t += 2.0f * deltaTime;
					camera.SetPosition(sin(t) * 5.0f, 3.0f, cos(t) * 5.0f);
				}
				// VP matrix
				glm::mat4 viewMatrix = camera.GetViewMatrix();
				shader.SetUniformMat4f("u_Matrix_VP", projMatrix * viewMatrix);
				// Camera info																							
				shader.SetUniform3f("u_CamPos", camera.GetPosition());
			}

			// Swap buffer
			glfwSwapBuffers(m_Window);

			LogError();
		}
	}

	glfwTerminate();
	return 0;
}