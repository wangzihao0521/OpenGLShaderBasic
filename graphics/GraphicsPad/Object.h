#pragma once
#include "Mesh.h"
#include "Material.h"
#include "Transform.h"

class Object {
protected:
	char* name;
	Mesh mesh;
	Transform transform;
	Material material;
	
public:
	Object(char* ObjName,Mesh mesh, Transform trans = Transform()) :
		name(ObjName),mesh(mesh), transform(trans),material(Material()){}
	void Setposition(glm::vec3 pos) { transform.setPosition(pos); }
	void Setrotaion(glm::vec3 rot) { transform.setRotation(rot); }
	void Setscale(glm::vec3 scale) { transform.setScale(scale); }
	void translate(glm::vec3 Vec3) { transform.tranlate(Vec3); }
	void rotate(glm::vec3 Vec3) { transform.rotate(Vec3); }
	void scale(glm::vec3 Vec3) { transform.scale(Vec3); }
	void setShaderID(GLuint VshaderID, GLuint FshaderID);
	void setProgramID(GLuint programID);
	void bindMaterial(Material Material) { material = Material; }
//	ShaderInfo* getShaderInfo() const { return shader; }
	char* getName() const { return name; }
	Transform getTransform() const { return transform; }
	Material getMaterial() const { return material; }
	GLuint getObjectID() const { return mesh.GeometryID; }
	Shapedata getGeometry() const { return mesh.geometry; }
};
