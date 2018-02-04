#pragma once

#include <memory>
#include "OpenGL.h"

class Texture;

using TextureObj = std::shared_ptr<Texture>;

class Texture
{
	GLuint mTextureId = 0;

	Texture() = default;

public:
	Texture(const Texture&) = delete;
	Texture(const Texture&&) = delete;
	Texture& operator=(const Texture&&) = delete;
	Texture& operator=(const Texture&) = delete;

	~Texture();

	static TextureObj loadTexture(const char* fileName);

	explicit operator GLuint() const { return mTextureId; }
};