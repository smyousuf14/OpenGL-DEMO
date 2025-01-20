// libraries
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>
#include<iostream>
#include<random>


// header files
#include "callbacks.h"
#include "utilities.h"
#include "vertex.h"
#include "OpenGLLoader.h"
#include "OpenGLDraw.h"
#include "Input.h"
#include "GLSL_Shader_loader.h"

int main(int argc, char** argv) {
	
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // version 4.5

	GLFWwindow* window = glfwCreateWindow(800,600, extract_version(argv[0]), nullptr, nullptr); // Create window
	glfwMakeContextCurrent(window); // Make it the current context
	
	// Load openGL functions using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {          
		throw "Failed to initialize GLAD";
	}

	glfwSetWindowCloseCallback(window, glfw_window_close_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback); // adjust the size of our viewport

	// Our vertex and fragment Shaders
	// -------------------------------------------------------------------------------------------------------->
	const char* vertshader =
		"#version 450 core                                                  \n"
		"layout(location = 0) in vec3 vertexPosition_modelspace;            \n"
		//"uniform mat4 modelmatrix;                                          \n"
		"void main(){                                                       \n"
		//"  gl_Position = modelmatrix * vec4(vertexPosition_modelspace, 1.0);\n"
		"  gl_Position = vec4(vertexPosition_modelspace, 1.0);\n"
		"}";
	const char* fragshader =
		"#version 450 core   \n"
		"out vec3 color;     \n"
		"uniform vec3 ucolor = vec3(.3,.5,.5);\n"
		"void main() {       \n"
		"  color = ucolor;   \n"
		"}";
	// -------------------------------------------------------------------------------------------------------->

	unsigned int mainShader = loadShader(vertshader, fragshader);
	loginfo("Shader loaded successfully");

	glClearColor(.2f, .2f, .6f, 0.f); // Sets the background to something other than black
	
	std::vector<DrawDetails> ourDrawDetails;
	{
		// Create object to display (points) C++
		std::vector<Vertex> obj_ptr;
		obj_ptr.emplace_back(.5f, -.5f, 0.f);
		obj_ptr.emplace_back(-.5f, -.5f, 0.f);
		obj_ptr.emplace_back(0.5f, .5f, 0.f);
		obj_ptr.emplace_back(-.5f, .5f, 0.f);

		std::vector<uint32_t> elem = {1, 3, 2, 0, 1, 2};

		// Update data to the graphics card.
		ourDrawDetails.push_back(UploadMesh(obj_ptr, elem));
	}

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.f, 1.f);

	// Main loop.
	while (!glfwWindowShouldClose(window)) {
		
		// Handle Keypresses.
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT); // sets the background everything the window is drawn.

		// RENDER OUR OBJECT
		glUseProgram(mainShader); // set the currently active shader program. telling OpenGL to use the shader program identified by the specified handle for all rendering operations until a different program is set or until the program is cleared by passing 0 to glUseProgram.
		
		float c1 = distribution(generator);
		float c2 = distribution(generator);
		float c3 = distribution(generator);

		uint32_t var = glGetUniformLocation(mainShader, "ucolor");
		glUniform3f(var, c1, c2, c3);

		Draw(ourDrawDetails);
		glfwSwapBuffers(window); // swaps whatever you are drawing to the front.
		glfwPollEvents(); // picks up any KB+M movements (glfw)


	}

	// Unload data from the graphcis card.
	UnloadMesh(ourDrawDetails);

	glfwTerminate();

	return 0;

}