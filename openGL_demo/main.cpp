// libraries
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<vector>


// header files
#include "callbacks.h"
#include "utilities.h"
#include "vertex.h"
#include "OpenGLLoader.h"
#include "OpenGLDraw.h"
#include "Input.h"

int main(int argc, char** argv) {
	
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6); // version 4.6

	GLFWwindow* window = glfwCreateWindow(800,600, extract_version(argv[0]), nullptr, nullptr); // Create window
	glfwMakeContextCurrent(window); // Make it the current context
	
	// Load openGL functions using GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {          
		throw "Failed to initialize GLAD";
	}

	glfwSetWindowCloseCallback(window, glfw_window_close_callback);
	glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback); // adjust the size of our viewport

	glClearColor(.2f, .2f, .6f, 0.f); // Sets the background to something other than black
	
	std::vector<DrawDetails> ourDrawDetails;
	{
		// Create object to display (points) C++
		std::vector<Vertex> obj_ptr;
		obj_ptr.emplace_back(.5f, -.5f, 0.f);
		obj_ptr.emplace_back(-.5f, -.5f, 0.f);
		obj_ptr.emplace_back(0.f, .5f, 0.f);

		std::vector<uint32_t> elem = {0, 1, 2};

		// Update data to the graphics card.
		ourDrawDetails.push_back(UploadMesh(obj_ptr, elem));
	}

	// Main loop.
	while (!glfwWindowShouldClose(window)) {
		
		// Handle Keypresses.
		ProcessInput(window);
		glClear(GL_COLOR_BUFFER_BIT); // sets the background everything the window is drawn.

		// RENDER OUR OBJECT
		Draw(ourDrawDetails);
		glfwSwapBuffers(window); // swaps whatever you are drawing to the front.
		glfwPollEvents(); // picks up any KB+M movements (glfw)


	}

	// Unload data from the graphcis card.
	UnloadMesh(ourDrawDetails);

	glfwTerminate();

	return 0;

}