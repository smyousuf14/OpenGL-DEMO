#pragma once

#include<vector>
#include "vertex.h"


// Responsible for uploading mesh data (vertices and elements) to the GPU using OpenGL. The function prepares and initializes the necessary 
// OpenGL objects for rendering a mesh. It returns a DrawDetails object containing details needed to draw the mesh
static DrawDetails UploadMesh(const std::vector<Vertex>& verts, const std::vector<uint32_t> elem){
	
	if (verts.empty() || elem.empty()) {
		throw "Empty vector";
	}

	uint32_t VAO; // Vertex  Array Object (VAO) stores all of the state needed to supply vertex data to the graphics pipeline.
	uint32_t VBO, EBO; // Vertex and Element Buffer object 

	glGenVertexArrays(1, &VAO); // Initializes and binds VAO.
	glBindVertexArray(VAO);

	// Prepare the Vertex Buffer Object (VBO)
	glGenBuffers(1, &VBO); //  Generate a vertex buffer object
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //  Bind a vertex buffer object
	glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW); // Uploads the actual vertex data from the verts vector to the GPU. NOTE: GL_STATIC_DRAW hints that the data will not change (or will change infrequently), optimizing GPU memory usage
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Pos)); // Configures how OpenGL interprets the vertex buffer data. Here, it assumes that the position data of the vertex are the first three floating-point numbers in the Vertex structure.
	glEnableVertexAttribArray(0);

	// Similar to the VBO but for the element array (index array), which tells OpenGL the order of the vertices to use when drawing.
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, elem.size() * sizeof(uint32_t), elem.data(), GL_STATIC_DRAW);

	glBindVertexArray(0); // Unbind VAO when done to prevent accidental modification.
	glDeleteBuffers(1, &VBO); // Optionally delete the VBO
	glDeleteBuffers(1, &EBO); // Optionally delete the EBO. We only really need VAO.

	return DrawDetails(VAO, elem.size()); // Returns an instance of DrawDetails configured with the VAO identifier and the number of elements, which are necessary to draw the mesh later on


}
// Intended to clean up resources associated with a vector of DrawDetails objects, specifically by deleting OpenGL buffer objects
static void UnloadMesh(std::vector<DrawDetails>& details) {
	for (auto& d : details) {
	
		glDeleteVertexArrays(1, &d.vao); // delete the VAO 
	}
	details.clear(); // Clear the vector of details
}

