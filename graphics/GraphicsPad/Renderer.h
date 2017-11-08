#pragma once
#include <vector>
#include <string>
#include "Pass.h"
#include <iostream>
#include <fstream>
#include <ShapeFactory.h>
#include "Material.h"

class Renderer {
protected:
	std::vector<Pass*> PassArray;
	std::vector<Mesh> MeshArray;
	static Renderer* renderer;
private:
	GLuint bindandfillvertexbuffer(Shapedata geometry);
	GLuint bindandfillindicesbuffer(Shapedata geometry);
	GLuint bindvertexarray(GLuint vbufferID, GLuint ibufferID);
public:
	Renderer() {};
	Object* CreateObject(Shapedata geo);
	void ExecutePass(Pass* pass);
	void init();
	void CreateCubeInScene();
	void BindShader2Object(const char* VshaderFileName,const char* FshaderFileName, Object* obj);
	Pass* AddPass();

	Mesh CompleteMeshWithGeo(Shapedata geometry);
	void AddMesh(Mesh mesh);
	bool checkShaderStatus(GLuint ShaderID);
	bool checkProgramStatus(GLuint ProgramID);
	std::string ReadShaderCode(const char* file);
	Renderer* getInstatnce() { return renderer; }
};
