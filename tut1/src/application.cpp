/*
#include <iostream>
#include <GL/glew.h> // to pull OpenGL specification from GPU
#include <GLFW/glfw3.h> // for creating a window
*/
// already included in the helper functions
#include "gl_framework.hpp"
#include "shader_util.hpp"

void setGLversion()
{
	//We want OpenGL 4.0
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//This is for MacOSX - can be omitted otherwise
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	//We don't want the old OpenGL 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

// initiate the shader program
GLuint initShadersGL(void)
{
	std::string vertex_shader_file("vs.glsl");
	std::string fragment_shader_file("fs.glsl");

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	return csX75::CreateProgramGL(shaderList);
}

int main(int argc, char const *argv[])
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	setGLversion();

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Tutorial1", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	// Needed for some extra functions. 
	glewExperimental = GL_TRUE;
	glewInit();

	float vertices[6] = {
		-0.5, -0.5,
		 0.5, -0.5,
		 0.0,  0.5
	};

	GLuint vbo, vao;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // current buffer in usage

	glBufferData(vbo, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); // for vertex positions

	GLuint shader = initShadersGL();
	glUseProgram(shader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shader);
		glBindVertexArray(vao);	

		glDrawArrays(GL_TRIANGLES, 0, 3); // using currently bound vbo and vao

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}