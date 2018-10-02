#include <unistd.h>
#include <cstdlib>
	
#include "helper/gl_helper.h"
#include "myclasses/VertexBuffer.h"
#include "myclasses/IndexBuffer.h"
#include "myclasses/VertexArray.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GLuint shader;

float positions1[] = {
	-0.5, -0.5, -0.5,
	 0.5, -0.5, -0.5,
	 0.5,  0.5, -0.5,
	-0.5,  0.5, -0.5,
	-0.5, -0.5,  0.5,
	 0.5, -0.5,  0.5,
	 0.5,  0.5,  0.5,
	-0.5,  0.5,  0.5,
};

float colors[] = {
	0.2, 0.2, 0.2, 1.0,
	0.2, 0.2, 1.0, 1.0,
	0.2, 1.0, 0.2, 1.0,
	0.2, 1.0, 1.0, 1.0,
	1.0, 0.2, 0.2, 1.0,
	1.0, 0.2, 1.0, 1.0,
	1.0, 1.0, 0.2, 1.0,
	1.0, 1.0, 1.0, 1.0
};

unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0,
	1, 5, 6,
	6, 2, 1,
	5, 6, 7,
	7, 4, 5,
	7, 3, 0,
	0, 4, 7,
	2, 6, 7,
	7, 3, 2,
	0, 1, 5,
	5, 4, 0
};
int num_indices = 12 * 3;

glm::mat4 model = glm::mat4(1.0f);

void initVertexBufferGL()
{
	GLuint vb1, va1, ib1;

	VertexBufferInit(vb1, sizeof(positions1) + sizeof(colors));
	VertexBufferSubData(positions1, 0, sizeof(positions1));
	VertexBufferSubData(colors, sizeof(positions1), sizeof(colors));

	VertexArrayInit(va1);
	VertexArrayAttrib(shader, "vPosition", 3, GL_FLOAT, GL_FALSE, 0, 0);
	VertexArrayAttrib(shader, "vColor",    4, GL_FLOAT, GL_FALSE, 0, sizeof(positions1));
 
	IndexBufferInit(ib1, indices, sizeof(indices));

	glm::mat4 proj = glm::ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	model = glm::rotate(model, glm::radians(0.52f), glm::vec3(1.0f,1.0f,1.0f));
	glm::mat4 mvp = proj * model;

	glUniformMatrix4fv(glGetUniformLocation(shader, "vMVP"), 1, GL_FALSE, & mvp[0][0]);
}

void renderGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	initVertexBufferGL();
	glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, NULL);
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