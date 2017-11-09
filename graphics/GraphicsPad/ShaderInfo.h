#pragma once
#include "GL\glew.h"

class ShaderInfo {
protected:
	GLuint programID;
	GLuint VshaderID;
	GLuint FshaderID;
public:
	ShaderInfo() :
		programID(0), VshaderID(0), FshaderID(0) {}

	GLuint getProgramID() const { return programID; }
	GLuint getVshaderID() const { return VshaderID; }
	GLuint getFshaderID() const { return FshaderID; }
	void setProgramID(GLuint id) { programID = id; }
	void setVshaderID(GLuint id) { VshaderID = id; }
	void setFshaderID(GLuint id) { FshaderID = id; }
};
