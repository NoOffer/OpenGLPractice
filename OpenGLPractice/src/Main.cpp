#include <iostream>

// GL libraries
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

// Helper libraries
//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"

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

const int WIN_WIDTH = 1100;
const int WIN_HEIGHT = 800;

const int VIEWPORT_WIDTH = 800;
const int VIEWPORT_HEIGHT = 800;

// Mouse callback helper variables
bool onMovingCenter = false;
bool onRotation = false;
double lastCursorPosX = 0, lastCursorPosY = 0;

void cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (onRotation)
	{
		float dx = xpos - lastCursorPosX, dy = ypos - lastCursorPosY;
		if (onMovingCenter)
		{
			MainCamera::MoveCenter(dx, dy);
		}
		else
		{
			MainCamera::Pitch(dy * 0.002f);
			MainCamera::Yaw(-dx * 0.002f);
		}
	}
	lastCursorPosX = xpos;
	lastCursorPosY = ypos;
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	MainCamera::DecreaseRadius(yoffset * 0.1f);
}

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
	GLFWwindow* m_Window = glfwCreateWindow(WIN_WIDTH, WIN_HEIGHT, "OpenGL Example", NULL, NULL);
	if (m_Window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowSizeLimits(m_Window, WIN_WIDTH, WIN_HEIGHT, WIN_WIDTH, WIN_HEIGHT);

	// GLAD initialization																						
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Set viewport (Origin at bottom left)
	glViewport(0, 0, VIEWPORT_WIDTH, VIEWPORT_HEIGHT);
	//glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
	//	{
	//		glViewport(0, height - HEIGHT, WIDTH, HEIGHT);
	//		//glfwSetWindowSize(window, WIDTH, HEIGHT);
	//	});

	// Set refresh rate																						
	glfwSwapInterval(1);

	// Print out current OpenGL version
	std::cout << glGetString(GL_VERSION) << std::endl;

	// Enable blending																						
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	//// Enable stencil test
	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_EQUAL, 1, 0xFF);

	// Render as wireframes
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Mouse callbacks
	glfwSetCursorPosCallback(m_Window, cursorPosCallback);
	glfwSetScrollCallback(m_Window, scrollCallback);

	// ImGui setup
	GUI::Init(m_Window, "#version 330 core");

	// Render contents & main loop
	{
		// Init camera
		MainCamera::Init(45.0f, vec2i(WIN_WIDTH, WIN_HEIGHT), vec3(0.0f, 30.0f, 50.0f));

		// Light																	
		DirectionalLight directionalLight{ vec3(-1.0f, -1.0f, -1.0f), vec3(1.0f, 0.85f, 0.6f) };
		vec3 ambient = vec3(0.12f, 0.18f, 0.3f);

		// Skybox cubemap
		CubeMap skyboxCubeMap(
			"res/textures/cube_maps/tut_skymap/right.jpg",
			"res/textures/cube_maps/tut_skymap/left.jpg",
			"res/textures/cube_maps/tut_skymap/top.jpg",
			"res/textures/cube_maps/tut_skymap/bottom.jpg",
			"res/textures/cube_maps/tut_skymap/front.jpg",
			"res/textures/cube_maps/tut_skymap/back.jpg"
		);

		// Create shader
		Shader skyboxShader(
			"res/shaders/SkyboxVert.shader",
			"res/shaders/SkyboxFrag.shader"
		);
		Shader renderModelShader(
			"res/shaders/BasicLitVert.shader",
			"res/shaders/BasicLitFrag.shader"
		);

		// Skybox
		Skybox skybox(skyboxShader, skyboxCubeMap);
		//Model box("res/models/simple-test-models/test_cube_model.obj", skyboxShader);
		Model renderModel(
			"res/models/snowy-mountain-v2-terrain/source/SnowyMountain_V2_SF/model/SnowyMountain_V2_Mesh.obj",
			renderModelShader
		);
		renderModel.SetScale(10.0f, 10.0f, 10.0f);

		// Projection matrix																					
		mat4 viewMatrix = MainCamera::GetViewMatrix();
		mat4 projMatrix = MainCamera::GetProjMatrix();
		renderModelShader.SetUniformMat4f("u_Matrix_VP", mul(projMatrix, viewMatrix));
		mat4 modelMatrix = renderModel.GetModelMatrix();
		renderModelShader.SetUniformMat4f("u_Matrix_M", modelMatrix);
		mat4 normalMatrix = renderModel.GetNormalMatrix();
		renderModelShader.SetUniformMat3f("u_Matrix_M_Normal", mat3(normalMatrix));

		//// Create texture																						
		//Texture texture("res/textures/TestTexture.png");
		//// Assign texture to shader																				
		//texture.Bind(0);
		//// Set uniforms
		//shader.SetUniform1i("u_Texture", 0);

		// Light info
		renderModelShader.SetUniform3f("u_LightDir", directionalLight.direction);
		renderModelShader.SetUniform3f("u_LightColor", directionalLight.color);
		renderModelShader.SetUniform3f("u_Ambient", ambient);
		// Camera info																							
		renderModelShader.SetUniform3f("u_CamPos", MainCamera::GetPosition());
		// Material info
		renderModelShader.SetUniform1f("u_Smoothness", 50.0f);

		float currentTime = glfwGetTime();
		float deltaTime = 0.0f;

		float smoothness = 0.0f;
		// ---------------------------------------------------------------------------------------------------------------- Main Loop
		while (!glfwWindowShouldClose(m_Window))
		{
			LogError();

			// Calculate delta time																				
			deltaTime = (float)glfwGetTime() - currentTime;
			currentTime = (float)glfwGetTime();

			// Clear																							
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

			// Poll events
			glfwPollEvents();

			// Handle input
			{
				if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				{
					glfwSetWindowShouldClose(m_Window, true);
				}
				if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
				{
					MainCamera::Pitch(0.01f);
				}
				if (glfwGetKey(m_Window, GLFW_KEY_S) == GLFW_PRESS)
				{
					MainCamera::Pitch(-0.01f);
				}
				if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
				{
					MainCamera::Yaw(-0.01f);
				}
				if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
				{
					MainCamera::Yaw(0.01f);
				}
				onMovingCenter = glfwGetKey(m_Window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
				onRotation = glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS;
				//if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS)
				//{
				//	onRotation = true;
				//}
				//else if (glfwGetMouseButton(m_Window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_RELEASE)
				//{
				//	onRotation = false;
				//}
			}

			// VP matrix
			viewMatrix = MainCamera::GetViewMatrix();
			renderModelShader.SetUniformMat4f("u_Matrix_VP", mul(projMatrix, viewMatrix));
			// Light info
			renderModelShader.SetUniform3f("u_LightColor", directionalLight.color);
			renderModelShader.SetUniform3f("u_Ambient", ambient);
			// Camera info																							
			renderModelShader.SetUniform3f("u_CamPos", MainCamera::GetPosition());
			// Material info
			renderModelShader.SetUniform1f("u_Smoothness", smoothness);

			// Render model
			renderModel.Draw();

			// Render skybox
			skybox.Render(projMatrix, viewMatrix);

			// GUI
			GUI::NewFrame();
			{
				// Origin at top left
				ImGui::SetNextWindowPos(ImVec2(VIEWPORT_WIDTH, 0), ImGuiCond_FirstUseEver);
				ImGui::SetNextWindowSize(ImVec2(300, WIN_HEIGHT), ImGuiCond_FirstUseEver);

				ImGui::Begin("Control Panel", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);

				ImGui::ColorEdit3("Light Color", (float*)&(directionalLight.color), 16777216);
				ImGui::ColorEdit3("Ambient Color", (float*)&(ambient), 16777216);
				ImGui::SliderFloat("Smoothness", &smoothness, 0.0f, 10.0f, "%.1f");
				ImGui::Text(
					"FPS: %.0f  (Avg %.2fms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate
				);

				ImGui::End();
			}
			GUI::Render();

			// Swap buffer
			glfwSwapBuffers(m_Window);
		}
	}

	GUI::Shutdown();
	glfwTerminate();

	return 0;
}