#include "Texture.h"
#include <string>
#ifdef _WIN32
#include <SDL2/SDL_image.h>
#else
#include <SDL_image.h>
#endif
#include <stdexcept>

TextureObj Texture::loadTexture(const char* fileName)
{
	TextureObj texture(new Texture());

	//load image
	const auto surface = IMG_Load(fileName);
	glGenTextures(1, &texture->mTextureId);
	glBindTexture(GL_TEXTURE_2D, texture->mTextureId);

	//create ogl texture
	const auto bytes = surface->format->BytesPerPixel;
	const auto bits = surface->format->BitsPerPixel;

	GLuint glTextureFormat;

	if (bytes == 3) glTextureFormat = GL_RGB;
	else if (bytes == 4) glTextureFormat = GL_RGBA;
	else
		throw(std::invalid_argument(std::string("Wrong image format ") + fileName));

	const auto bitPerColor = bits / bytes;

	GLuint dataType;

	if (bitPerColor == 8) dataType = GL_UNSIGNED_BYTE;
	else
		throw(std::invalid_argument(std::string("Wrong image bit ") + fileName));

	glTexImage2D(GL_TEXTURE_2D, 0, glTextureFormat, surface->w, surface->h, 0, glTextureFormat, dataType,
	             surface->pixels);
	
	SDL_FreeSurface(surface);

	return texture;
}

Texture::~Texture()
{
	glDeleteTextures(1, &mTextureId);
}