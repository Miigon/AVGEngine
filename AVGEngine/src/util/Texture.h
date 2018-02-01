#pragma once

#include <GL/glew.h>
#include <memory>
#include <boost/core/noncopyable.hpp>

class Texture;

using TextureObj = std::shared_ptr<Texture>;

class Texture :boost::noncopyable
{
	GLuint mTextureId = 0;

	Texture() = default;

public:
	~Texture();

	static TextureObj loadTexturePng(const char* fileName);

	explicit operator GLuint() const { return mTextureId; }
};