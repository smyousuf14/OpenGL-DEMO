#pragma once

static void ProcessInput(GLFWwindow* window) {


	// Just check if the escape key is pressed and close window if it is.
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		
		glfwSetWindowShouldClose(window, true); // sets the appropriate flag, which has to be handled elsewhere
	}

}