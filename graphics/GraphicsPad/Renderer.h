#pragma once
#include "Pass.h"
#include <ShapeFactory.h>
#include "Material.h"
#include <glm\gtc\matrix_transform.hpp>
#include <QtOpenGL\qglwidget>
#include "PointLight.h"


class Renderer {
protected:
	std::vector<Object*> ObjectArray;
	std::vector<Mesh> MeshArray;
	std::vector<Material> MaterialArray;
	static Renderer* renderer;
	std::vector<Camera> CameraArray;
	static Camera CurrentCamera;
	static PointLight* CurrentPointLight;
	static Object* P_light_obj;
	std::vector<Pass*> PassArray;
	std::vector<Texture*> TextureArray;

private:
	GLuint bindandfillvertexbuffer(Shapedata geometry);
	GLuint bindandfillindicesbuffer(Shapedata geometry);
	GLuint bindvertexarray(GLuint vbufferID, GLuint ibufferID);
	void PushCameraInVector(Camera cam);
	void setCurrentCamera(char* camName);
	void init_Pointlight();
	GLsizei ScreenWidth;
	GLsizei ScreenHeight;
	glm::vec3 AmbientLightIntense;
	void Add_LightUniform(Pass* pass);
	void Add_AllMaterialProperty(Material* mat);
	void ExecutePass(Pass* pass);
	Texture* FindTextureByName(char* TexName);

public:
	Renderer() {};
	Object* CreateObject(char* ObjName,Shapedata geo);	
	void init(GLsizei width,GLsizei height);
	void RenderScene();
	void CreateCubeInScene(char* CubeName);
	void CreatePlaneInScene(char* PlaneName);
	void CreatePointLight(char* LightName, glm::vec3 pos = glm::vec3());
	void ImportTexture(char* FileName);
	void setPositionforObject(glm::vec3 position, char* ObjName);
	void BindShader2Material(char* VshaderFileName,char* FshaderFileName, Material& material);
	void BindMaterial2Object(char* MaterialName, Object* obj);
	Pass* AddPass();
	Material CreateMaterial(char* Materialname, char* VshaderFileName = "Test_Vertexshader.glsl", char* FshaderFileName = "Test_Fragmentshader.glsl");
	Mesh CompleteMeshWithGeo(Shapedata geometry);
	void AddMesh(Mesh mesh);
	void AddObject(Object* obj);
	void Add_Zihao_MVP(Pass* pass);
	void Add_Property_Material(char* MaterialName,char* PropertyName, M_PropertyType PropertyType,char* TexName);
	void Add_Property_Material(char* MaterialName, char* PropertyName, M_PropertyType PropertyType, glm::vec2 DefaultValue);
	void Add_Property_Material(char* MaterialName, char* PropertyName, M_PropertyType PropertyType, glm::vec3 DefaultValue);
	void Add_Property_Material(char* MaterialName, char* PropertyName, M_PropertyType PropertyType, float DefaultValue);
	void Bind_Property_Material(char* MaterialName, char* PropertyName, char* TexName);
	Camera* getCurrentCamera() { return &CurrentCamera; }
	PointLight* getCurrentPLight() { return  CurrentPointLight ; }
	Renderer* getInstatnce() { return renderer; }

	
	
};
