#include "VertexArray.h"

void VertexArrayInit(GLuint & vaoID) {
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
}

void VertexArrayBind(GLuint & vaoID) {
	glBindVertexArray(vaoID);	
}

void VertexArrayUnbind() {
	glBindVertexArray(0);
}

void VertexArrayAttrib(GLuint shader, const char * var_name, GLint size, GLenum type, GLboolean norm, GLsizei stride, uintptr_t offset) {
	GLuint index = glGetAttribLocation(shader, var_name);
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, norm, stride, (const void *) offset);
}