#include "../helper/gl_framework.hpp"
#include "../helper/shader_util.hpp"

void IndexBufferInit(GLuint & iboID, const void * data, unsigned int size);
void IndexBufferBind(GLuint iboID);
void IndexBufferUnbind();