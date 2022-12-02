#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define ASSERT(x) if(!(x)) __debugbreak();

// -------------------------------------------------------------------------------------- Custom Helper Methods
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


//static void ParseShader(std::string& filepath)
//{
//	std::ifstream stream(filepath);
//
//	enum class ShaderType
//	{
//		NONE = -1, VERTEX = 0, FRAGMENT = 1
//	};
//
//	std::string line;
//	std::stringstream ss[2];
//	ShaderType shaderType = ShaderType::NONE;
//	while (getline(stream, line)) {
//		if (line.find("#shader") != std::string::npos) {
//			if (line.find("vertex") != std::string::npos) {
//				shaderType = ShaderType::VERTEX;
//			}
//			else if (line.find("fragment") != std::string::npos) {
//				shaderType = ShaderType::FRAGMENT;
//			}
//		}
//		else {
//			ss[(int)shaderType] << line << '\n';
//		}
//	}
//
//	stream.close();
//}

static std::string ReadShader(std::string filepath)
{
	std::ifstream fileStream(filepath);
	if (!fileStream.is_open()) {
		std::cout << "Failed to load shader at " << filepath << std::endl;
		return "";
	}
	std::stringstream ss;
	ss << fileStream.rdbuf();
	fileStream.close();

	return ss.str();
}

static unsigned int ComplieShader(const std::string& source, unsigned int type)
{
	// Create a shader object
	unsigned int shaderId = glCreateShader(type);
	// Pass in the shader code
	const char* src = source.c_str();
	glShaderSource(shaderId, 1, &src, nullptr);
	// Compile
	glCompileShader(shaderId);

	// Error handling
	int status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE) {
		// Retrieve the length of the error message
		int msgLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &msgLength);
		// Message string
		char* msg = (char*)malloc(msgLength * sizeof(char));
		glGetShaderInfoLog(shaderId, msgLength, &msgLength, msg);
		std::cout << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << "Shader Compilation Failure: "
			<< msg << std::endl;
		// Free the space for the message string
		free(msg);

		// Delete the unsuccessfully compiled shader
		glDeleteShader(shaderId);

		return 0;
	}

	return shaderId;
}

static int CreateShaderProgram(const std::string& vertShader, const std::string& fragShader)
{
	// Create a program object that holds the shaders
	unsigned int programId = glCreateProgram();
	// Get the references of the shaders after compilation
	unsigned int vs = ComplieShader(vertShader, GL_VERTEX_SHADER);
	unsigned int fs = ComplieShader(fragShader, GL_FRAGMENT_SHADER);

	// Attach the shaders and activate the program
	glAttachShader(programId, vs);
	glAttachShader(programId, fs);
	glLinkProgram(programId);
	glValidateProgram(programId);

	// Destroy the shaders since they have been linked to the program
	glDeleteShader(vs);
	glDeleteShader(fs);

	return programId;
}

// ------------------------------------------------------------------------------------------------ Main Method
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

	// Vertices
	float vertPos[8] = {
		-0.5f, 0.5,
		-0.5f, -0.5,
		0.5f, -0.5f,
		0.5f, 0.5f
	};
	// Vertext buffer declaration
	unsigned int vertBufferId;
	glGenBuffers(1, &vertBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, vertBufferId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, vertPos, GL_STATIC_DRAW);
	// Specify vertex data structure
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// Setup vertex layout (bind current buffer to vertex array 0)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);


	// Indices
	unsigned int vertIdx[6] = {
		0, 1, 2,
		0, 2, 3
	};
	// Index buffer declaration
	unsigned int idxBufferId;
	glGenBuffers(1, &idxBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idxBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, vertIdx, GL_STATIC_DRAW);

	// Create shaders
	unsigned int shaderId = CreateShaderProgram(
		ReadShader("res/shaders/TestVert.shader"),
		ReadShader("res/shaders/TestFrag.shader")
	);
	glUseProgram(shaderId);

	// Uniform example
	int location = glGetUniformLocation(shaderId, "u_Color");
	ASSERT(location != -1);
	glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f);

	// ---------------------------------------------------------------------------------------------- Main Loop
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();

		/* Log error */
		LogError();
	}

	glDeleteProgram(shaderId);

	glfwTerminate();
	return 0;
}