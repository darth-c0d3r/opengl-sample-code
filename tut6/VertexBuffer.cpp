#include "VertexBuffer.h"
#include <iostream>

void VertexBufferInit(GLuint & vboID, const void * data, unsigned int size) {
	glGenBuffers(1, &vboID); 
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBufferBind(GLuint vboID) {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}
void VertexBufferUnbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}