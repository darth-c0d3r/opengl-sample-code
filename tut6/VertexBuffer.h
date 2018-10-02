#include "gl_framework.hpp"
#include "shader_util.hpp"

void VertexBufferInit(GLuint & vboID, const void * data, unsigned int size);
void VertexBufferBind(GLuint vboID);
void VertexBufferUnbind();