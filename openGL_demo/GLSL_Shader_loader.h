#pragma once

#include <glad/glad.h>
#include<vector>


// A comprehensive routine in C++ using OpenGL for compiling vertex and fragment shaders, and then linking them into a shader program
// This is a common task in OpenGL applications where shaders are used for rendering graphics.
// @param: vertexshader: pointer to a string containing the source code for the vertex shader.
// @param: fragmentshader: pointer to a string containing the source code for the fragment shader
static GLuint loadShader(const char* vertexshader, const char* fragmentshader) {

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER); // generates a shader object for the given type
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER); // generates a shader object for the given type

	//// Read the Vertex Shader code from the file
	//std::string VertexShaderCode;
	//std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	//if(VertexShaderStream.is_open()){
	//	std::stringstream sstr;
	//	sstr << VertexShaderStream.rdbuf();
	//	VertexShaderCode = sstr.str();
	//	VertexShaderStream.close();
	//}else{
	//	printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
	//	getchar();
	//	return 0;
	//}

	//// Read the Fragment Shader code from the file
	//std::string FragmentShaderCode;
	//std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	//if(FragmentShaderStream.is_open()){
	//	std::stringstream sstr;
	//	sstr << FragmentShaderStream.rdbuf();
	//	FragmentShaderCode = sstr.str();
	//	FragmentShaderStream.close();
	//}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	//printf("Compiling shader : %s\n", vertex_file_path);
	//char const * VertexSourcePointer = VertexShaderCode.c_str();
	//glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glShaderSource(VertexShaderID, 1, &vertexshader, NULL); // sets the source code in the shader object. Here, it's taking the source code directly from the input arguments
	glCompileShader(VertexShaderID); // compiles the shader source code currently stored in the shader object

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result); // checks if the compilation was successful and also retrieves the length of the log produced by the compilation process.
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength); // retrieves the actual log message, which is printed out. This log contains errors or warnings that occurred during compilation.
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}

	// Compile Fragment Shader
	//printf("Compiling shader : %s\n", fragment_file_path);
	//char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	//glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glShaderSource(FragmentShaderID, 1, &fragmentshader, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram(); // creates a program object.
	glAttachShader(ProgramID, VertexShaderID); // attaches the compiled vertex and fragment shaders to the program.
	glAttachShader(ProgramID, FragmentShaderID); 
	glLinkProgram(ProgramID);  // links all the attached shaders together into the program, making it ready for use in rendering.

	// Check the program to check if the linking was successful
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	// Cleanup
	glDetachShader(ProgramID, VertexShaderID); // detaches the shaders from the program after linking because they are no longer needed.
	glDetachShader(ProgramID, FragmentShaderID); // detaches the shaders from the program after linking because they are no longer needed.

	glDeleteShader(VertexShaderID); // deletes the shader objects to free up memory, as the shaders are now embedded in the program.
	glDeleteShader(FragmentShaderID); // deletes the shader objects to free up memory, as the shaders are now embedded in the program.

	return ProgramID;
}