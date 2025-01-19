#pragma once
#include<cstdio>
#include <GLFW/glfw3.h>

// header files
#include "Utilities.h"

static void glfw_error_callback(int error, const char* description) {
	
	loginfo(description);
	throw("glfw error");
}

static void glfw_window_close_callback(GLFWwindow* window) {
	loginfo("Window closed");
	printf("Window closed \n");
}