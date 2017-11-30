#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "glm\glm.hpp"
#include "ShaderInfo.h"
#include "Texture.h"

enum M_PropertyType {
	M_Texture2D = 1,
	M_float,
	M_vec2,
	M_vec3
};

class M_Property {
protected:
	char* name;
	M_PropertyType type;
	Texture* tex = nullptr;
	glm::vec2 vec2 = glm::vec2();
	glm::vec3 vec3 = glm::vec3();
	float Float = 0.0;;
public:
	M_Property(char* Name, M_PropertyType Type, Texture* Tex) {
		name = Name;
		type = Type;
		tex = Tex;
	}
	M_Property(char* Name, M_PropertyType Type, glm::vec2 value) {
		name = Name;
		type = Type;
		vec2 = value;
	}
	M_Property(char* Name, M_PropertyType Type, glm::vec3 value) {
		name = Name;
		type = Type;
		vec3 = value;
	}
	M_Property(char* Name, M_PropertyType Type, float value) {
		name = Name;
		type = Type;
		Float = value;
	}
	char* getName() const { return name; }
	M_PropertyType getType() const { return type; }
	Texture* getTexture() const { return tex; }
	glm::vec2 getVec2() const { return vec2; }
	glm::vec3 getVec3() const { return vec3; }
	float getFloat() const { return Float; }
	void setTexture(Texture* texture) { tex = texture; }
};

class Material {
protected:
	char* name;
	char* VshaderFileName;
	char* FshaderFileName;
	ShaderInfo shaderinfo;
	std::vector<M_Property*> PropertyArray;
//	std::vector<Texture*> TextureArray;
//	std::vector<glm::vec2> Vec2Array;
//	std::vector<glm::vec3> Vec3Array;
//	std::vector<float> FloatArray;
	

public:
	Material(char* Materialname = "DefaultMaterial",char* Vshaderfilename = nullptr, char* Fshaderfilename = nullptr) :
		name(Materialname),VshaderFileName(Vshaderfilename), FshaderFileName(Fshaderfilename),Model2WorldMatrix(glm::mat4()),shaderinfo(ShaderInfo()) {};

	char* getName() const { return name; }
	ShaderInfo getShaderInfo() const { return shaderinfo; }
	bool checkPropertyNoExist(char* P_name);
	M_Property* FindPropertyByName(char* P_name);
	bool checkShaderStatus(GLuint ShaderID);
	bool checkProgramStatus(GLuint ProgramID);
	std::string ReadShaderCode(const char* file);
	bool CompileShader(char* VshaderFileName, char* FshaderFileName);
	void setVertexShader(char* vShaderFileName);
	void setFragmentShader(char* fShaderFileName);
	void AddProperty(M_Property* property) { PropertyArray.push_back(property); }
	void AddAllPropertyUniform();
	glm::mat4 Model2WorldMatrix;
//	void AddTexture(Texture* tex) { TextureArray.push_back(tex); }
//	void AddFloat(float f) { FloatArray.push_back(f); }
//	void AddVec2(glm::vec2 value) { Vec2Array.push_back(value); }
//	void AddVec3(glm::vec3 value) { Vec3Array.push_back(value); }
};


