#pragma once

#include "Render/Mesh.h"
#include "Render/Material.h"
#include "Transform.h"


enum ObjectType {
	Non_Light = 1,
	Light
};

class Object {
protected:
	char* name;
	Mesh mesh;
	Transform transform;
	Material material;
	bool IsSkyBox;
	bool castShadow;
	bool receiveShadow;
	ObjectType type;
	
public:
	Object(char* ObjName,Mesh mesh, Transform trans = Transform(),ObjectType t = Non_Light) :
		name(ObjName),mesh(mesh), transform(trans),material(Material()),IsSkyBox(false),castShadow(false),receiveShadow(false),type(t){}
	void Setposition(glm::vec3 pos) { transform.setPosition(pos); }
	void Setrotation(glm::vec3 rot) { transform.setRotation(rot); }
	void Setscale(glm::vec3 scale) { transform.setScale(scale); }
	void translate(glm::vec3 Vec3) { transform.tranlate(Vec3); }
	void rotate(glm::vec3 Vec3) { transform.rotate(Vec3); }
	void scale(glm::vec3 Vec3) { transform.scale(Vec3); }
	void setType(ObjectType t) { type = t; }
	void bindMaterial(Material Material) { material = Material; }
	void toggleSkyBox() { IsSkyBox = !IsSkyBox; }
	void toggleCastShadow() { castShadow = !castShadow; }
	void toggleReceiveShadow() { receiveShadow = !receiveShadow; }
	bool Is_SkyBox() { return IsSkyBox; }
	bool Is_CastShadow() { return castShadow; }
	bool Is_ReceiveShadow() { return receiveShadow; }
//	ShaderInfo* getShaderInfo() const { return shader; }
	char* getName() const { return name; }
	Mesh getMesh() const { return mesh; }
	Transform getTransform() const { return transform; }
	Material getMaterial() const { return material; }
	GLuint getObjectID() const { return mesh.GeometryID; }
	Shapedata getGeometry() const { return mesh.geometry; }
	ObjectType getType() const { return type; }
};
