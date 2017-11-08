#include "Renderer.h"
#include "GL\glew.h"

Renderer* Renderer::renderer = new Renderer();

GLuint Renderer::bindandfillvertexbuffer(Shapedata geometry)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, geometry.VertexBufferSize(), geometry.vertices, GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindandfillindicesbuffer(Shapedata geometry)
{
	GLuint bufferID;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, geometry.IndicesBufferSize(), geometry.Indices, GL_STATIC_DRAW);
	return bufferID;
}

GLuint Renderer::bindvertexarray(GLuint vbufferID, GLuint ibufferID)
{
	GLuint GeometryID;
	glGenVertexArrays(1, &GeometryID);
	glBindVertexArray(GeometryID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER , vbufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(6 * sizeof(float)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float)));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(11 * sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibufferID);

	return GeometryID;
}

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

void Renderer::CreateCubeInScene()
{
	Shapedata CubeGeometry = ShapeFactory::MakeCube();
//	if(!CheckGeometryExist(CubeGeometry))
	Mesh m = CompleteMeshWithGeo(CubeGeometry);
	AddMesh(m);
	Object*  cube = new Object(m);
	BindShader2Object("Test_Vertexshader.glsl", "Test_Fragmentshader.glsl", cube);
	cube->Setposition(glm::vec3(0.0, 0.0, -5.0));
	Pass* p = AddPass();
	p->setObject(cube);


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

Mesh Renderer::CompleteMeshWithGeo(Shapedata geometry)
{
	Mesh m(geometry) ;
	m.VertexBufferID = bindandfillvertexbuffer(geometry);
	m.indicesBufferID = bindandfillindicesbuffer(geometry);
	m.GeometryID = bindvertexarray(m.VertexBufferID, m.indicesBufferID);

	return m;
}

void Renderer::AddMesh(Mesh mesh)
{
	MeshArray.push_back(mesh);
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
