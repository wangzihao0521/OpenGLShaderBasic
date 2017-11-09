#pragma once
#include <vector>
#include "Pass.h"
#include <ShapeFactory.h>
#include "Material.h"
#include <glm\gtc\matrix_transform.hpp>

class Renderer {
protected:	
	std::vector<Mesh> MeshArray;
	std::vector<Material> MaterialArray;
	static Renderer* renderer;

private:
	GLuint bindandfillvertexbuffer(Shapedata geometry);
	GLuint bindandfillindicesbuffer(Shapedata geometry);
	GLuint bindvertexarray(GLuint vbufferID, GLuint ibufferID);
	GLsizei ScreenWidth;
	GLsizei ScreenHeight;
public:
	Renderer() {};
	Object* CreateObject(Shapedata geo);
	void ExecutePass(Pass* pass);
	void init(GLsizei width,GLsizei height);
	void CreateCubeInScene();
	void BindShader2Material(char* VshaderFileName,char* FshaderFileName, Material& material);
	void BindMaterial2Object(char* MaterialName, Object* obj);
	Pass* AddPass();
	Material CreateMaterial(char* Materialname, char* VshaderFileName = "Test_Vertexshader.glsl", char* FshaderFileName = "Test_Fragmentshader.glsl");
	Mesh CompleteMeshWithGeo(Shapedata geometry);
	void AddMesh(Mesh mesh);
	void Add_Zihao_MVP(Pass* pass);
	Renderer* getInstatnce() { return renderer; }

	std::vector<Pass*> PassArray;
};
