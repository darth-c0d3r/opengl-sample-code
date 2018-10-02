#include "TextureBuffer.h"
#include <iostream>

void TextureBufferInit(const char * path, GLuint & texID, TextureVars & tv) {

	stbi_set_flip_vertically_on_load(1);
	tv.buffer = stbi_load(path, & tv.width, & tv.height, & tv.bpp, 4);

	std::cout << "b: " << tv.buffer << "\n";

	glGenTextures(1, &texID); 
	glBindTexture(GL_TEXTURE_2D, texID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tv.width, tv.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tv.buffer);	
	glBindTexture(GL_TEXTURE_2D, 0);

	if(tv.buffer)
		stbi_image_free(tv.buffer);
}

void TextureBufferBind(GLuint texID, unsigned int slot = 0) {
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, texID);	
}

void TextureBufferUnbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}