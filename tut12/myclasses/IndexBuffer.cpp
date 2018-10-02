#include "IndexBuffer.h"

void IndexBufferInit(GLuint & iboID, const void * data, unsigned int size) {
	glGenBuffers(1, &iboID); 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void IndexBufferBind(GLuint iboID) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
}
void IndexBufferUnbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}