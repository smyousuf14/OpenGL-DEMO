// libraries
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// header files
#include "callbacks.h"
#include "utilities.h"

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
	while (!glfwWindowShouldClose(window)) {
		glfwSwapBuffers(window);
		glfwPollEvents(); // picks up any KB+M movements

	}

	glfwTerminate();

	return 0;

}