#include <unistd.h>
#include <cstdlib>
	
#include "helper/gl_helper.h"
#include "myclasses/VertexBuffer.h"
#include "myclasses/IndexBuffer.h"
#include "myclasses/VertexArray.h"
#include "myclasses/TextureBuffer.h"

GLuint shader;

float positions1[] = {
	-0.75, -0.75, 0.0,
	-0.25, -0.75, 0.0,
	-0.25, -0.25, 0.0,
	-0.75, -0.25, 0.0
};

float mappings1[] = {
	0.0, 0.0,
	1.0, 0.0,
	1.0, 1.0,
	0.0, 1.0
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
	GLuint vb1, va1, ib1, tx1;

	VertexBufferInit(vb1, sizeof(positions1) + sizeof(mappings1) + sizeof(colors));
	VertexBufferSubData(positions1, 0, sizeof(positions1));
	VertexBufferSubData(mappings1, sizeof(positions1), sizeof(mappings1));
	VertexBufferSubData(colors, sizeof(positions1) + sizeof(mappings1), sizeof(colors));

	TextureVars tv;
	TextureBufferInit("images/pic1.png", tx1, tv);
	TextureBufferBind(tx1, 0);
	glUniform1i(glGetUniformLocation(shader, "uTexture"), 0);

	VertexArrayInit(va1);
	VertexArrayAttrib(shader, "vPosition", 3, GL_FLOAT, GL_FALSE, 0, 0);
	VertexArrayAttrib(shader, "vTexture",  2, GL_FLOAT, GL_FALSE, 0, sizeof(positions1));
	VertexArrayAttrib(shader, "vColor",    4, GL_FLOAT, GL_FALSE, 0, sizeof(positions1) + sizeof(mappings1));

 	// #original

	IndexBufferInit(ib1, indices, sizeof(indices));
}

void renderGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	initVertexBufferGL();
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
	shader = initShadersGL("shaders/vs.glsl", "shaders/fs.glsl");
	glUseProgram(shader);
	
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