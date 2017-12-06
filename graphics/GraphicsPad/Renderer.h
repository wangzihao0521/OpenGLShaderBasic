#pragma once
#include "Pass.h"
#include <ShapeFactory.h>
#include "Material.h"
#include <glm\gtc\matrix_transform.hpp>
#include <QtOpenGL\qglwidget>
#include "PointLight.h"
#include "FrameBuffer.h"


class Renderer {
protected:
	static Renderer* renderer;
	std::vector<Object*> ObjectArray;
	std::vector<Mesh> MeshArray;
	std::vector<Material> MaterialArray;	
	std::vector<Camera> CameraArray;
	static Camera CurrentCamera;
	static PointLight* CurrentPointLight;
	static Object* CurrentObject;
	static Object* P_light_obj;
	std::vector<Pass*> PassArray;
	std::vector<Texture*> TextureArray;
	FrameBuffer ShadowFrameBuffer;
	Camera LightCamera = Camera("LightCamera");
	bool castingShadow = false;

private:
	GLuint bindandfillvertexbuffer(Shapedata geometry);
	GLuint bindandfillindicesbuffer(Shapedata geometry);
	GLuint bindvertexarray(GLuint vbufferID, GLuint ibufferID);
	void PushCameraInVector(Camera cam);
	void PushTexture2Array(Texture* tex);
	void setCurrentCamera(char* camName);
	void init_Pointlight();
	void init_SkyBox();
	void init_ShadowFrameBuffer();
	GLsizei ScreenWidth;
	GLsizei ScreenHeight;
	glm::vec3 AmbientLightIntense;
	void Add_LightUniform(Pass* pass);
	void Add_AllMaterialProperty(Material* mat);
	void ExecutePass(Pass* pass);
	Texture* FindTextureByName(char* TexName);
	Material FindMaterialByName(char* MatName);

public:
	Renderer() {};
	Object* CreateObject(char* ObjName,Shapedata geo);	
	void init(GLsizei width,GLsizei height);
	void setScreenSize(GLsizei width, GLsizei height);
	void RanderShadowMap();
	void RenderScene();
	void CreateCubeInScene(char* CubeName);
	void CreatePlaneInScene(char* PlaneName);
	void CreatePointLight(char* LightName, glm::vec3 pos = glm::vec3());
	void ImportTexture(char* FileName);
	void Renderer::Import3DTexture(char * TextureName,char* rightImage, char* leftImage, char* topImage, char* bottomImage, char* frontImage, char* backImage);
	void setPositionforObject(glm::vec3 position, char* ObjName);
	void setRotationforObject(glm::vec3 rotation, char* ObjName);
	void setScaleforObject(glm::vec3 scale, char* ObjName);
	void BindShader2Material(char* VshaderFileName,char* FshaderFileName, Material& material);
	void BindMaterial2Object(char* MaterialName, Object* obj);
	void  BindMaterial2Object(char* MaterialName, char* objName);
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
	void ToggleSkyboxforObject(char* objName);
	Camera* getCurrentCamera() { return &CurrentCamera; }
	Camera* getLightCamera() { return &LightCamera; }
	PointLight* getCurrentPLight() { return  CurrentPointLight ; }
	Object* getCurrentObject() { return CurrentObject; }
	Renderer* getInstatnce() { return renderer; }

	
	
};
