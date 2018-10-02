#include "gl_framework.hpp"
#include "shader_util.hpp"
#include <unistd.h>
#include <cstdlib>

#include "VertexBuffer.h"
#include "IndexBuffer.h"


GLuint shader;

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
GLuint initShadersGL(const std::string & vs, const std::string & fs)
{
	std::string vertex_shader_file(vs);
	std::string fragment_shader_file(fs);

	std::vector<GLuint> shaderList;
	shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
	shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

	shader = csX75::CreateProgramGL(shaderList);

	glUseProgram(shader);
}

GLuint vbo, vao;

float positions1[] = {
	-0.75, -0.75, 0.0,
	-0.25, -0.75, 0.0,
	-0.25, -0.25, 0.0,
	-0.75, -0.25, 0.0
};

float positions2[] = {
	 0.75,  0.75, 0.0,
	 0.25,  0.75, 0.0,
	 0.25,  0.25, 0.0,
	 0.75,  0.25, 0.0
};

float colors[] = {
	1.0, 1.0, 1.0, 1.0,
	1.0, 1.0, 0.0, 1.0,
	1.0, 0.0, 1.0, 1.0,
	0.0, 1.0, 1.0, 1.0
};

int num_vertices = 4;

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0	
};
int num_indices = 6;

void initVertexBufferGL()
{
	GLuint vb1;
	VertexBufferInit(vb1, sizeof(positions1) + sizeof(colors));
	VertexBufferSubData(positions1, 0, sizeof(positions1));
	VertexBufferSubData(colors, sizeof(positions1), sizeof(colors));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	GLuint vPosition = glGetAttribLocation(shader, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	GLuint vColor = glGetAttribLocation(shader, "vColor"); 
	glEnableVertexAttribArray(vColor);
	glVertexAttribPointer(vColor, 4, GL_FLOAT, GL_FALSE, 0, (const void*)sizeof(positions1));

	// index array
	GLuint ib1;
	IndexBufferInit(ib1, indices, sizeof(indices));
}

void renderGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	initVertexBufferGL();
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
}

int main(int argc, char** argv)
{
	GLFWwindow* window;
	glfwSetErrorCallback(csX75::error_callback);

	if (!glfwInit())
		return -1;
	setGLversion();

	window = glfwCreateWindow(640, 480, "Tutorial", NULL, NULL);
	glfwMakeContextCurrent(window);

	// glfwSwapInterval(1);

	glewExperimental = GL_TRUE;
	glewInit();

	glfwSetKeyCallback(window, csX75::key_callback);
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	csX75::initGL();
	initShadersGL("vs.glsl", "fs.glsl");
	// initVertexBufferGL();

	// glfwSwapInterval(50);
	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{	
		renderGL();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}

