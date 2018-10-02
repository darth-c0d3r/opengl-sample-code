#include "gl_framework.hpp"
#include "shader_util.hpp"
#include <unistd.h>

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
}

GLuint vbo, vao;
float vertices[] = {
	-0.75, -0.50, 0.0,
	 0.75, -0.50, 0.0,
	 0.75,  0.50, 0.0,
	-0.75,  0.50, 0.0
};
int num_vertices = 4;

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0	
};
int num_indices = 6;

void initVertexBufferGL()
{
	for(int i=0; i < num_vertices; i++) {
		float temp = vertices[3*i+0];
		vertices[3*i+0] = vertices[3*i+1];
		vertices[3*i+1] = temp;
	}

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num_vertices * 3 * sizeof (float), vertices, GL_STATIC_DRAW);	

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// index array
	unsigned int ia;
	glGenBuffers(1, &ia);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ia);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof (unsigned int), indices, GL_STATIC_DRAW);	


}

void renderGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(shader);
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

	glewExperimental = GL_TRUE;
	glewInit();

	glfwSetKeyCallback(window, csX75::key_callback);
	glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	csX75::initGL();
	initShadersGL("vs.glsl", "fs.glsl");
	// initVertexBufferGL();

	int i = 0;
	// Loop until the user closes the window
	while (glfwWindowShouldClose(window) == 0)
	{
		renderGL();
		sleep(1);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}

