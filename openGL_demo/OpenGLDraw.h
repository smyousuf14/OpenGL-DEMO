#pragma once

#include<vector>
#include "Vertex.h"

// use OpenGL to render a series of objects described by a collection of DrawDetails. This function takes a std::vector of DrawDetails 
// objects, each likely containing the information necessary to draw a specific mesh or part of a scene.
static void Draw(const std::vector<DrawDetails>&  details) {

	for (const auto& d : details) {
		
		glBindVertexArray(d.vao); // binds the vertex array object (VAO) associated with the current object d. Binding a VAO sets it as the current vertex array to be used by subsequent OpenGL drawing calls.
		glDrawElements(GL_TRIANGLES, d.numElements, GL_UNSIGNED_INT, nullptr); // render primitives from array data.
	}
	glBindVertexArray(0); // unbinds the current vertex array object. This is a good practice to clean up by unbinding the VAO, thereby preventing subsequent OpenGL calls from accidentally modifying or using this VAO
}