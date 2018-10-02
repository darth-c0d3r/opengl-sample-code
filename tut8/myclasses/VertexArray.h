#include "../helper/gl_framework.hpp"
#include "../helper/shader_util.hpp"
#include "stdint.h"

void VertexArrayInit(GLuint & vaoID);
void VertexArrayBind(GLuint & vaoID);
void VertexArrayUnbind();
void VertexArrayAttrib(GLuint shader, const char * var_name, GLint size, 
			GLenum type, GLboolean norm, GLsizei stride, uintptr_t offset);