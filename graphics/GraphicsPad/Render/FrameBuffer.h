#pragma once

#include "GL\glew.h"

#include "Texture.h"

class FrameBuffer {
protected:
	void init_ColorTexture(GLuint i, GLsizei width, GLsizei height);
	void init_DepthTexture(GLuint i, GLsizei width, GLsizei height);

public:
	GLuint id;
	Texture* ColorTexture;
	Texture* DepthTexture;

	FrameBuffer():
		id(0),ColorTexture(nullptr),DepthTexture(nullptr){}

	void init(GLuint i, GLsizei width, GLsizei height);
};
