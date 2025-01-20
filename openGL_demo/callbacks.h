#pragma once
#include<cstdio>

// header files
#include "Utilities.h"

static void glfw_error_callback(int error, const char* description) {
	
	loginfo(description);
	throw("glfw error");
}

static void glfw_framebuffer_size_callback(GLFWwindow* window, int height, int width) {

	loginfo("Frame buffer size has changed");

	// update the OpenGL viewport to fit the new windows dimensions.
	glViewport(0, 0, width, height);

}

static void glfw_window_close_callback(GLFWwindow* window) {
	loginfo("Window closed");
	printf("Window closed \n");
}

