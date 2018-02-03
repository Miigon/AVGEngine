#define _CRT_SECURE_NO_WARNINGS
#include "Texture.h"
#include <stdexcept>

TextureObj Texture::loadTexturePng(const char* fileName)
{
	/*TextureObj texture(new Texture());

	const auto file = fopen(fileName, "rb");
	auto pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
	auto infoPtr = png_create_info_struct(pngPtr);
	setjmp(png_jmpbuf(pngPtr));
	png_init_io(pngPtr, file);
	png_read_png(pngPtr, infoPtr, PNG_TRANSFORM_EXPAND, nullptr);

	const int width = png_get_image_width(pngPtr, infoPtr);
	const int height = png_get_image_height(pngPtr, infoPtr);
	const int colorType = png_get_color_type(pngPtr, infoPtr);

	const auto rowPointers = png_get_rows(pngPtr, infoPtr);
	unsigned char* imageData;
	GLuint textureFormat;
	size_t imageDataSize;
	auto pos = 0;

	switch (colorType)
	{
	case PNG_COLOR_TYPE_RGB:
		textureFormat = GL_RGB;
		imageDataSize = height * width * 3;
		imageData = new unsigned char[imageDataSize];

		for (auto i = height - 1; i >= 0; i--)
			for (auto j = 0; j < (3 * width); j += 3)
			{
				imageData[pos++] = rowPointers[i][j + 0];
				imageData[pos++] = rowPointers[i][j + 1];
				imageData[pos++] = rowPointers[i][j + 2];
			}

		break;
	case PNG_COLOR_TYPE_RGBA:
		textureFormat = GL_RGBA;
		imageDataSize = height * width * 4;
		imageData = new unsigned char[imageDataSize];

		for (auto i = height - 1; i >= 0; i--)
			for (auto j = 0; j < (4 * width); j += 4)
			{
				imageData[pos++] = rowPointers[i][j + 0];
				imageData[pos++] = rowPointers[i][j + 1];
				imageData[pos++] = rowPointers[i][j + 2];
				imageData[pos++] = rowPointers[i][j + 3];
			}

		break;
	default:
		throw std::invalid_argument(std::string("Wrong png file:") + fileName);
	}

	glGenTextures(1, &texture->mTextureId);
	glBindTexture(GL_TEXTURE_2D, texture->mTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, textureFormat, width, height, 0, textureFormat, GL_UNSIGNED_BYTE, imageData);

	png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
	fclose(file);
	delete[] imageData;

	return texture;*/
	return nullptr;
}

Texture::~Texture()
{
	glDeleteTextures(1, &mTextureId);
}