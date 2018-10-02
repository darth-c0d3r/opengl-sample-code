#include "VertexBuffer.h"
#include <iostream>

void VertexBufferInit(GLuint & vboID, unsigned int size) {
	glGenBuffers(1, &vboID); 
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);
}

void VertexBufferSubData(const void * data, unsigned int offset, unsigned int size) {
	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void VertexBufferBind(GLuint vboID) {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}
void VertexBufferUnbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}