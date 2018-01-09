#include "Material.h"
#include "GL\glew.h"

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

bool Material::checkPropertyNoExist(char * P_name)
{
	for (auto iter = PropertyArray.begin(); iter != PropertyArray.end(); ++iter)
	{
		if ((*iter)->getName() == P_name)
		{
			printf("Property already exists");
			return false;
		}
	}
	return true;
}

M_Property * Material::FindPropertyByName(char * P_name)
{
	for (auto iter = PropertyArray.begin(); iter != PropertyArray.end(); ++iter)
	{
		if (strcmp((*iter)->getName(),P_name) == 0)
		{
			return *iter;
		}
	}
	printf("Cannot find the property");
	return nullptr;
}

bool Material::checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool Material::checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string Material::ReadShaderCode(const char* fileName)
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

bool Material::CompileShader(char * VshaderFileName, char * FshaderFileName)
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

	if (!checkShaderStatus(VertexShaderID) || !checkShaderStatus(FragmentShaderID)) {
		printf("shader compile failed");
		return false;
	}
	
	GLuint programID = glCreateProgram();
	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID)) {
		printf("program compile failed");
		return false;
	}
	else {
		shaderinfo.setVshaderID(VertexShaderID);
		shaderinfo.setFshaderID(FragmentShaderID);
		shaderinfo.setProgramID(programID);
	}

	return true;
}

void Material::setVertexShader(char * vShaderFileName)
{
	VshaderFileName = vShaderFileName;
}

void Material::setFragmentShader(char * fShaderFileName)
{
	FshaderFileName = fShaderFileName;
}

void Material::AddAllPropertyUniform()
{
	if (PropertyArray.empty())
	{
		return;
	}
	for (auto iter = PropertyArray.begin(); iter != PropertyArray.end(); iter++)
	{
		GLint UniformLocation = glGetUniformLocation(shaderinfo.getProgramID(), (*iter)->getName());
		switch ((*iter)->getType())
		{
		case M_Texture2D:
		{
			glUniform1i(UniformLocation, (*iter)->getTexture()->getBufferID());
		}
		case M_Texture3D:
		{
			glUniform1i(UniformLocation, (*iter)->getTexture()->getBufferID());
		}
		case M_vec3:
		{
			glUniform3fv(UniformLocation,1, &(*iter)->getVec3()[0]);
		}
		case M_vec2:
		{
			glUniform2fv(UniformLocation, 1, &(*iter)->getVec2()[0]);
		}
		case M_float:
		{
			glUniform1f(UniformLocation,(*iter)->getFloat());
		}
		default:
			break;
		}
	}
}
