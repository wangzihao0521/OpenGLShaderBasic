#include "Renderer.h"
#include "GL\glew.h"

Renderer* Renderer::renderer = new Renderer();

Object * Renderer::CreateObject(Shapedata geometry)
{
	Object* obj = new Object(geometry);
	return obj;
}

void Renderer::ExecutePass(Pass* pass)
{
	glUseProgram(pass->getObject()->getShaderInfo()->getProgramID());
	glBindVertexArray(pass->getObject()->getObjectID());
	glDrawElements(GL_TRIANGLES, pass->getObject()->getGeometry().numIndices, GL_UNSIGNED_SHORT, (void*)pass->getObject()->getIndicesBufferOffset());
}

void Renderer::init()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

}

void Renderer::start()
{
	PushAllGeoDataIntoGLBuffer();
	SetAllGeoAttriAndID();
}

void Renderer::BindShader2Object(const char* VshaderFileName, const char* FshaderFileName, Object * obj)
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	std::string temp = ReadShaderCode(VshaderFileName);
	adapter[0] = temp.c_str();
	glShaderSource(VertexShaderID, 1, adapter, 0);
	temp = ReadShaderCode(FshaderFileName);
	adapter[0] = temp.c_str();
	glShaderSource(FragmentShaderID, 1, adapter, 0);

	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	if (!checkShaderStatus(VertexShaderID) || !checkShaderStatus(FragmentShaderID))
		return;
	else
		obj->setShaderID(VertexShaderID, FragmentShaderID);

	GLuint programID = glCreateProgram();
	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;
	else
		obj->setProgramID(programID);

//	glDeleteShader(VertexShaderID);
//	glDeleteShader(FragmentShaderID);

}

Pass * Renderer::AddPass()
{
	Pass* pass = new Pass();
	PassArray.push_back(pass);
	return pass;
}

void Renderer::AddGeometry(Shapedata geometry)
{
	GeometryArray.push_back(geometry);
}

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
		delete[] buffer;
		return false;
	}
	return true;
}

bool Renderer::checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool Renderer::checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string Renderer::ReadShaderCode(const char* fileName)
{
	std::ifstream meInput(fileName);
	if (!meInput.good())
	{
		std::cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}
