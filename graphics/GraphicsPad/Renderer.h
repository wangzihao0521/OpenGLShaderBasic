#pragma once
#include <vector>
#include <string>
#include "Pass.h"
#include <iostream>
#include <fstream>

class Renderer {
protected:
	std::vector<Pass*> PassArray;
	std::vector<Shapedata> GeometryArray;
	static Renderer* renderer;
public:
	Renderer() {};
	Object* CreateObject(Shapedata geo);
	void ExecutePass(Pass* pass);
	void init();
	void start();
	void BindShader2Object(const char* VshaderFileName,const char* FshaderFileName, Object* obj);
	Pass* AddPass();
	void AddGeometry(Shapedata geometry);
	bool checkShaderStatus(GLuint ShaderID);
	bool checkProgramStatus(GLuint ProgramID);
	std::string ReadShaderCode(const char* file);
	Renderer* getInstatnce() { return renderer; }
};
