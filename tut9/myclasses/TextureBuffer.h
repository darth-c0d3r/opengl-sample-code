#include "../helper/gl_framework.hpp"
#include "../helper/shader_util.hpp"
#include "vendor/stb_image.h"

struct TextureVars {
	int width, height, bpp;
	unsigned char * buffer;
};

void TextureBufferInit(const char * path, GLuint & texID, TextureVars & tv);
void TextureBufferBind(GLuint vboID, unsigned int slot);
void TextureBufferUnbind();