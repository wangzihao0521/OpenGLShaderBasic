#include "FrameBuffer.h"

void FrameBuffer::init_ColorTexture(GLuint i, GLsizei width, GLsizei height)
{
	glActiveTexture(GL_TEXTURE0 + i);
	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT,nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	ColorTexture = new Texture("ShadowMap_Color",i,TextureID);
}

void FrameBuffer::init_DepthTexture(GLuint i, GLsizei width, GLsizei height)
{
	glActiveTexture(GL_TEXTURE0 + i + 1);
	GLuint TextureID;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	DepthTexture = new Texture("ShadowMap_Depth", i + 1, TextureID);
}

void FrameBuffer::init(GLuint i, GLsizei width, GLsizei height)
{
	glGenFramebuffers(1, &id);
	glBindBuffer(GL_FRAMEBUFFER, id);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_DEPTH_ATTACHMENT);
	init_ColorTexture(i, width,height);
	init_DepthTexture(i, width, height);
	
}
