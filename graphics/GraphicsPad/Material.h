#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include "glm\glm.hpp"
#include "ShaderInfo.h"

class Material {
protected:
	char* name;
	char* VshaderFileName;
	char* FshaderFileName;
	ShaderInfo shaderinfo;
	

public:
	Material(char* Materialname = "DefaultMaterial",char* Vshaderfilename = nullptr, char* Fshaderfilename = nullptr) :
		name(Materialname),VshaderFileName(Vshaderfilename), FshaderFileName(Fshaderfilename),Model2WorldMatrix(glm::mat4()),shaderinfo(ShaderInfo()) {};

	char* getName() const { return name; }
	ShaderInfo getShaderInfo() const { return shaderinfo; }
	bool checkShaderStatus(GLuint ShaderID);
	bool checkProgramStatus(GLuint ProgramID);
	std::string ReadShaderCode(const char* file);
	bool CompileShader(char* VshaderFileName, char* FshaderFileName);
	void setVertexShader(char* vShaderFileName);
	void setFragmentShader(char* fShaderFileName);
	glm::mat4 Model2WorldMatrix;
};
