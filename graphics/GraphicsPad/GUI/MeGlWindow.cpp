#include <gl\glew.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp>
#include <QtGui\qkeyevent>

#include "MeGlWindow.h"
#include "Core/Camera.h"
#include "Render/Vertex.h"

#include <iostream>
#include <fstream>

static GLuint   CubeElementArrayOffset;
static GLuint   PlaneElementArrayOffset;
static GLuint	CubenumIndices;
static GLuint	PlanenumIndices;
static GLuint	CubeObjectID;
static GLuint	PlaneObjectID;

GLuint programID;
GLuint LightProgramID;
GLuint CubeMapProgramID;
GLuint PlaneShadowProgramID;
GLuint TestProgramID;

GLuint FrameBufferID;
GLuint FrameTextureID;
GLuint FrameDepthID;

GLfloat AttenuationFactor = 0.03;

Camera MainCamera;
Camera LightCamera;

glm::vec3 LightPosition(0.0f, 2.5f, -5.0f);
float RotationAngle = 0.0f;

const char* MeGlWindow::TexFile[] = { "Data/Texture/right.png","Data/Texture/left.png","Data/Texture/bottom.png","Data/Texture/top.png","Data/Texture/back.png","Data/Texture/front.png" };
/*
void MeGlWindow::senddatatoRenderer()
{
	glClearColor(0, 0, 0, 1);

	Shapedata CubeGeometry = ShapeFactory::MakeCube();
	renderer()->AddGeometry(CubeGeometry);
	Shapedata PlaneGeometry = ShapeFactory::MakePlane();
	renderer()->AddGeometry(PlaneGeometry);

	Pass* pass = renderer()->AddPass();
	Object* Cube = renderer()->CreateObject(CubeGeometry);
	Cube->Setposition(glm::vec3(0.0, 0.0, -5.0));
	renderer()->BindShader2Object("Data/Shader/Test_Vertexshader.glsl","Data/Shader/Test_Fragmentshader.glsl",Cube);
	pass->setObject(Cube);


	GLuint BufferID;
	GLuint	currentbufferoffset = 0;

	glGenBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, Cube.VertexBufferSize()+Cube.IndicesBufferSize()+Plane.VertexBufferSize()+Plane.IndicesBufferSize(), 0, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, Cube.VertexBufferSize(), Cube.vertices);
	currentbufferoffset = Cube.VertexBufferSize();
	CubeElementArrayOffset = currentbufferoffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentbufferoffset, Cube.IndicesBufferSize(), Cube.Indices);
	currentbufferoffset += Cube.IndicesBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentbufferoffset, Plane.VertexBufferSize(),Plane.vertices);
	currentbufferoffset += Plane.VertexBufferSize();
	PlaneElementArrayOffset = currentbufferoffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentbufferoffset, Plane.IndicesBufferSize(), Plane.Indices);
	CubenumIndices = Cube.numIndices;
	PlanenumIndices = Plane.numIndices;

	glGenVertexArrays(1, &CubeObjectID);
	glGenVertexArrays(1, &PlaneObjectID);

	glBindVertexArray(CubeObjectID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(11 * sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);

	glBindVertexArray(PlaneObjectID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(Cube.VertexBufferSize()+Cube.IndicesBufferSize()));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(3 * sizeof(float) + Cube.VertexBufferSize() + Cube.IndicesBufferSize()));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(6 * sizeof(float) + Cube.VertexBufferSize() + Cube.IndicesBufferSize()));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(9 * sizeof(float) + Cube.VertexBufferSize() + Cube.IndicesBufferSize()));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 15 * sizeof(float), (void*)(11 * sizeof(float)+ Cube.VertexBufferSize() + Cube.IndicesBufferSize()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);

	const char* texName = "Data/Texture/MyTexture.png";
	QImage texture = QGLWidget::convertToGLFormat(QImage(texName, "PNG"));

	glActiveTexture(GL_TEXTURE0);

	GLuint TextureBufferID;
	glGenTextures(1, &TextureBufferID);
	glBindTexture(GL_TEXTURE_2D, TextureBufferID);
	//	int a = texture.height();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width(), texture.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	

	const char* normalMapName = "Data/Texture/Normal_map.png";
	QImage Normalmap = QGLWidget::convertToGLFormat(QImage(normalMapName, "PNG"));

	glActiveTexture(GL_TEXTURE1);

	GLuint NormalBufferID;
	glGenTextures(1,&NormalBufferID);
	glBindTexture(GL_TEXTURE_2D, NormalBufferID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Normalmap.width(), Normalmap.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Normalmap.bits());
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	LoadCubeMap();

	glActiveTexture(GL_TEXTURE3);

	glGenFramebuffers(1, &FrameBufferID);
	glBindBuffer(GL_FRAMEBUFFER, FrameBufferID);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_DEPTH_ATTACHMENT);

	glGenTextures(1, &FrameTextureID);
	glBindTexture(GL_TEXTURE_2D, FrameTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width(), height(), 0, GL_RGB, GL_FLOAT,NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, FrameTextureID, 0);

	glActiveTexture(GL_TEXTURE4);
	glGenTextures(1, &FrameDepthID);
	glBindTexture(GL_TEXTURE_2D, FrameDepthID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width(), height(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, FrameDepthID, 0);

	CubeGeometry.cleanup();
	PlaneGeometry.cleanup();
}*/
void MeGlWindow::LoadCubeMap() {
	glActiveTexture(GL_TEXTURE2);
	GLuint CubeBufferID;
	glGenTextures(1, &CubeBufferID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, CubeBufferID);
	
	for (int i = 0; i < 6; ++i) {
		QImage Texdata = QGLWidget::convertToGLFormat(QImage(TexFile[i], "PNG"));
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, Texdata.width(), Texdata.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, Texdata.bits());
	}
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
/*
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

bool MeGlWindow::checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool MeGlWindow::checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string MeGlWindow::ReadShaderCode(const char* fileName)
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

void MeGlWindow::installshaders()
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	std::string temp = ReadShaderCode("Data/Shader/VertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(VertexShaderID, 1, adapter, 0);
	temp = ReadShaderCode("Data/Shader/FragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(FragmentShaderID, 1, adapter, 0);

	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	if (!checkShaderStatus(VertexShaderID) || !checkShaderStatus(FragmentShaderID))
		return;

	programID = glCreateProgram();
	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID))
		return;

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	temp = ReadShaderCode("Data/Shader/CubeLightVertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(VertexShaderID, 1, adapter, 0);
	temp = ReadShaderCode("Data/Shader/CubeLightFragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(FragmentShaderID, 1, adapter, 0);

	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	if (!checkShaderStatus(VertexShaderID) || !checkShaderStatus(FragmentShaderID))
		return;

	LightProgramID = glCreateProgram();
	glAttachShader(LightProgramID, VertexShaderID);
	glAttachShader(LightProgramID, FragmentShaderID);
	glLinkProgram(LightProgramID);
	if (!checkProgramStatus(LightProgramID))
		return;

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	temp = ReadShaderCode("Data/Shader/CubeMapVertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(VertexShaderID, 1, adapter, 0);
	temp = ReadShaderCode("Data/Shader/CubeMapFragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(FragmentShaderID, 1, adapter, 0);

	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	if (!checkShaderStatus(VertexShaderID) || !checkShaderStatus(FragmentShaderID))
		return;

	CubeMapProgramID = glCreateProgram();
	glAttachShader(CubeMapProgramID, VertexShaderID);
	glAttachShader(CubeMapProgramID, FragmentShaderID);
	glLinkProgram(CubeMapProgramID);
	if (!checkProgramStatus(CubeMapProgramID))
		return;

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	temp = ReadShaderCode("Data/Shader/ShadowMapVertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(VertexShaderID, 1, adapter, 0);
	temp = ReadShaderCode("Data/Shader/ShadowMapFragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(FragmentShaderID, 1, adapter, 0);

	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	if (!checkShaderStatus(VertexShaderID) || !checkShaderStatus(FragmentShaderID))
		return;

	TestProgramID = glCreateProgram();
	glAttachShader(TestProgramID, VertexShaderID);
	glAttachShader(TestProgramID, FragmentShaderID);
	glLinkProgram(TestProgramID);
	if (!checkProgramStatus(TestProgramID))
		return;

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	temp = ReadShaderCode("Data/Shader/PlaneShadowVertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(VertexShaderID, 1, adapter, 0);
	temp = ReadShaderCode("Data/Shader/PlaneShadowFragmentShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(FragmentShaderID, 1, adapter, 0);

	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	if (!checkShaderStatus(VertexShaderID) || !checkShaderStatus(FragmentShaderID))
		return;

	PlaneShadowProgramID = glCreateProgram();
	glAttachShader(PlaneShadowProgramID, VertexShaderID);
	glAttachShader(PlaneShadowProgramID, FragmentShaderID);
	glLinkProgram(PlaneShadowProgramID);
	if (!checkProgramStatus(PlaneShadowProgramID))
		return;

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
}
*/
void MeGlWindow::initializeGL()
{
	setMinimumSize(1280, 720);
	glewInit();
	renderer()->init(width(),height());
	UserInput();
//	installshaders();
//	senddatatoOpenGL();
//	Mytimer = new QTimer(this);

//	connect(Mytimer, SIGNAL(timeout()), this, SLOT(update()));
//	Mytimer->setInterval(0);
//	Mytimer->start();
}

void MeGlWindow::paintGL()
{
	glViewport(0, 0, width(), height());
	renderer()->setScreenSize(width(),height());
	renderer()->RanderShadowMap();
	renderer()->RenderScene();
	/*
//	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
//	glViewport(0, 0, 320, 180);

	glViewport(0, 0, width(), height());

	//render to shadow map
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FrameBufferID);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, FrameTextureID, 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, FrameDepthID, 0);
	GLuint status = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);
	assert(status == GL_FRAMEBUFFER_COMPLETE);

	LightCamera.setPosition(LightPosition);
	DrawObjects(LightCamera);

	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	glm::mat4 CameraMatrix = MainCamera.getWorldToViewMatrix();
	glm::mat4 projectionMatrix = glm::perspective(60.0f, ((float)width() / height()), 0.3f, 100.0f);

	glm::mat4 World2ProjectionMatrix = projectionMatrix * CameraMatrix;

	glm::mat4 FullTransformMatrix;

	glUseProgram(programID);

	GLint TextureUniformLocation = glGetUniformLocation(programID, "MyTexture");
	glUniform1i(TextureUniformLocation, 0);
	GLint NormalmapUniformLocation = glGetUniformLocation(programID, "NormalMap");
	glUniform1i(NormalmapUniformLocation, 1);

	GLuint FullTransformMatrixUniformLocaiton;
	FullTransformMatrixUniformLocaiton = glGetUniformLocation(programID, "FullTransformMatrix");
	GLuint Model2WorldMatrixUniformLocaiton;
	Model2WorldMatrixUniformLocaiton = glGetUniformLocation(programID, "Model2WorldMatrix");
	glm::mat4 TransformMatrix;
	glm::mat4 RotationMatrix;
	//Light Begins Here
	glm::vec3 AmbientLight(0.2f, 0.2f, 0.2f);



	GLuint AmbientLightUniformLocation = glGetUniformLocation(programID, "AmbientLight");
	glUniform3fv(AmbientLightUniformLocation, 1, &AmbientLight[0]);

	GLuint LightPositionUniformLocation = glGetUniformLocation(programID, "LightPosition");
	glUniform3fv(LightPositionUniformLocation, 1, &LightPosition[0]);

	GLuint ViewPositionUniformLocation = glGetUniformLocation(programID, "ViewPosition");
	glUniform3fv(ViewPositionUniformLocation, 1, &MainCamera.getPosition()[0]);

	GLuint AttenuationUniformLocation = glGetUniformLocation(programID, "AttenuationFactor");
	glUniform1f(AttenuationUniformLocation, AttenuationFactor);

	//Cube1
	glBindVertexArray(CubeObjectID);
	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(+3.0f, 0.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), RotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));

	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;
	glm::mat4 Cube1Model2WorldMatrix = TransformMatrix * RotationMatrix;


	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);
	glUniformMatrix4fv(Model2WorldMatrixUniformLocaiton, 1, GL_FALSE, &Cube1Model2WorldMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)(CubeElementArrayOffset));

	//Cube2
	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), 66.0f, glm::vec3(1.0f, -1.0f, 0.0f));

	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;
	glm::mat4 Cube2Model2WorldMatrix = TransformMatrix * RotationMatrix;

	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);
	glUniformMatrix4fv(Model2WorldMatrixUniformLocaiton, 1, GL_FALSE, &Cube2Model2WorldMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)(CubeElementArrayOffset));

	//plane
	glUseProgram(PlaneShadowProgramID);
	glBindVertexArray(PlaneObjectID);

	TextureUniformLocation = glGetUniformLocation(PlaneShadowProgramID, "MyTexture");
	glUniform1i(TextureUniformLocation, 0);
	NormalmapUniformLocation = glGetUniformLocation(PlaneShadowProgramID, "NormalMap");
	glUniform1i(NormalmapUniformLocation, 1);

	GLint ShadowMapUniformLocation = glGetUniformLocation(PlaneShadowProgramID, "ShadowMap");
	glUniform1i(ShadowMapUniformLocation, 4);

	glm::mat4 LightWorld2ProjectionMatrix = projectionMatrix * LightCamera.getWorldToViewMatrix();
	GLint LightFullTransformMatrixUniformLocaiton = glGetUniformLocation(PlaneShadowProgramID, "LightFullTransformMatrix");
	glUniformMatrix4fv(LightFullTransformMatrixUniformLocaiton, 1, GL_FALSE, &LightWorld2ProjectionMatrix[0][0]);

	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(-0.0f, -2.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;
	glm::mat4 PlaneModel2WorldMatrix = TransformMatrix * RotationMatrix;

	AmbientLightUniformLocation = glGetUniformLocation(PlaneShadowProgramID, "AmbientLight");
	glUniform3fv(AmbientLightUniformLocation, 1, &AmbientLight[0]);

	LightPositionUniformLocation = glGetUniformLocation(PlaneShadowProgramID, "LightPosition");
	glUniform3fv(LightPositionUniformLocation, 1, &LightPosition[0]);

	ViewPositionUniformLocation = glGetUniformLocation(PlaneShadowProgramID, "ViewPosition");
	glUniform3fv(ViewPositionUniformLocation, 1, &MainCamera.getPosition()[0]);

	AttenuationUniformLocation = glGetUniformLocation(PlaneShadowProgramID, "AttenuationFactor");
	glUniform1f(AttenuationUniformLocation, AttenuationFactor);
	FullTransformMatrixUniformLocaiton = glGetUniformLocation(PlaneShadowProgramID, "FullTransformMatrix");
	Model2WorldMatrixUniformLocaiton = glGetUniformLocation(PlaneShadowProgramID, "Model2WorldMatrix");
	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);
	glUniformMatrix4fv(Model2WorldMatrixUniformLocaiton, 1, GL_FALSE, &PlaneModel2WorldMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, PlanenumIndices, GL_UNSIGNED_SHORT, (void*)(PlaneElementArrayOffset));

	//CubeLight
	glUseProgram(LightProgramID);
	glBindVertexArray(CubeObjectID);
	TransformMatrix = glm::translate(glm::mat4(), LightPosition);
	RotationMatrix = glm::rotate(glm::mat4(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(0.08f, 0.08f, 0.08f));

	GLuint LightTransformMatrixUniformLocation = glGetUniformLocation(LightProgramID, "LightTransformMatrix");
	FullTransformMatrix = World2ProjectionMatrix  *  TransformMatrix * ScaleMatrix * RotationMatrix;
	glUniformMatrix4fv(LightTransformMatrixUniformLocation, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)CubeElementArrayOffset);

	RotationAngle += 5.0f;
	if (RotationAngle > 360.0f) RotationAngle -= 360.0f;

	//CubeMap
	glUseProgram(CubeMapProgramID);

	GLint CubeMapUniformLocation = glGetUniformLocation(CubeMapProgramID, "CubeMap");
	glUniform1i(CubeMapUniformLocation, 2);

	glBindVertexArray(CubeObjectID);
	ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(50.0f, 50.0f, 50.0f));

	GLuint SkyboxTransformMatrixUniformLocation = glGetUniformLocation(CubeMapProgramID, "SkyboxTransformMatrix");
	CameraMatrix[3][0] = 0.0;
	CameraMatrix[3][1] = 0.0;
	CameraMatrix[3][2] = 0.0;
	FullTransformMatrix = projectionMatrix * CameraMatrix * ScaleMatrix;
	glUniformMatrix4fv(SkyboxTransformMatrixUniformLocation, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)CubeElementArrayOffset);
	
	glUseProgram(TestProgramID);

	TextureUniformLocation = glGetUniformLocation(TestProgramID, "MyTexture");
	glUniform1i(TextureUniformLocation, 4);
	glBindVertexArray(CubeObjectID);
	CameraMatrix = MainCamera.getWorldToViewMatrix();
	projectionMatrix = glm::perspective(60.0f, ((float)width() / height()), 0.1f, 100.0f);

	World2ProjectionMatrix = projectionMatrix * CameraMatrix;

	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f,0.0f,-5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));

	GLuint FullTransformMatrixUniformLocation = glGetUniformLocation(TestProgramID, "FullTransformMatrix");
	FullTransformMatrix = World2ProjectionMatrix  *  TransformMatrix * ScaleMatrix * RotationMatrix;
	glUniformMatrix4fv(FullTransformMatrixUniformLocation, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)CubeElementArrayOffset);*/

	//test my renderer
	
	
}
void MeGlWindow::DrawObjects(Camera & camera){

	glm::mat4 CameraMatrix = camera.getWorldToViewMatrix();
	glm::mat4 projectionMatrix = glm::perspective(60.0f, ((float)width() / height()), 0.3f, 100.0f);

	glm::mat4 World2ProjectionMatrix = projectionMatrix * CameraMatrix;

	glm::mat4 FullTransformMatrix;

	glUseProgram(programID);

	GLint TextureUniformLocation = glGetUniformLocation(programID, "MyTexture");
	glUniform1i(TextureUniformLocation, 0);
	GLint NormalmapUniformLocation = glGetUniformLocation(programID, "NormalMap");
	glUniform1i(NormalmapUniformLocation, 1);
	
	GLuint FullTransformMatrixUniformLocaiton;
	FullTransformMatrixUniformLocaiton = glGetUniformLocation(programID, "FullTransformMatrix");
	GLuint Model2WorldMatrixUniformLocaiton;
	Model2WorldMatrixUniformLocaiton = glGetUniformLocation(programID, "Model2WorldMatrix");
	glm::mat4 TransformMatrix;
	glm::mat4 RotationMatrix;
	//Light Begins Here
	glm::vec3 AmbientLight(0.2f, 0.2f, 0.2f);

	

	GLuint AmbientLightUniformLocation = glGetUniformLocation(programID, "AmbientLight");
	glUniform3fv(AmbientLightUniformLocation, 1, &AmbientLight[0]);

	GLuint LightPositionUniformLocation = glGetUniformLocation(programID, "LightPosition");
	glUniform3fv(LightPositionUniformLocation, 1, &LightPosition[0]);

	GLuint ViewPositionUniformLocation = glGetUniformLocation(programID, "ViewPosition");
	glUniform3fv(ViewPositionUniformLocation, 1, &camera.getPosition()[0]);

	GLuint AttenuationUniformLocation = glGetUniformLocation(programID, "AttenuationFactor");
	glUniform1f(AttenuationUniformLocation,AttenuationFactor);

	//Cube1
	glBindVertexArray(CubeObjectID);
	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(+3.0f, 0.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), RotationAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	
	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;
	glm::mat4 Cube1Model2WorldMatrix = TransformMatrix * RotationMatrix;


	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);
	glUniformMatrix4fv(Model2WorldMatrixUniformLocaiton, 1, GL_FALSE, &Cube1Model2WorldMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)(CubeElementArrayOffset));

	//Cube2
	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), 66.0f, glm::vec3(1.0f, -1.0f, 0.0f));

	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;
	glm::mat4 Cube2Model2WorldMatrix = TransformMatrix * RotationMatrix;

	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);
	glUniformMatrix4fv(Model2WorldMatrixUniformLocaiton, 1, GL_FALSE, &Cube2Model2WorldMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)(CubeElementArrayOffset));

	//plane
	glBindVertexArray(PlaneObjectID);
	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(-0.0f, -2.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;
	glm::mat4 PlaneModel2WorldMatrix = TransformMatrix * RotationMatrix;

	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);
	glUniformMatrix4fv(Model2WorldMatrixUniformLocaiton, 1, GL_FALSE, &PlaneModel2WorldMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, PlanenumIndices, GL_UNSIGNED_SHORT, (void*)(PlaneElementArrayOffset));

	//CubeLight
	glUseProgram(LightProgramID);
	glBindVertexArray(CubeObjectID);
	TransformMatrix = glm::translate(glm::mat4(),LightPosition);
	RotationMatrix = glm::rotate(glm::mat4(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(0.08f, 0.08f, 0.08f));

	GLuint LightTransformMatrixUniformLocation = glGetUniformLocation(LightProgramID, "LightTransformMatrix");
	FullTransformMatrix = World2ProjectionMatrix  *  TransformMatrix * ScaleMatrix * RotationMatrix;
	glUniformMatrix4fv(LightTransformMatrixUniformLocation, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)CubeElementArrayOffset);

	RotationAngle += 5.0f;
	if (RotationAngle > 360.0f) RotationAngle -= 360.0f;

	//CubeMap
	glUseProgram(CubeMapProgramID);

	GLint CubeMapUniformLocation = glGetUniformLocation(CubeMapProgramID, "CubeMap");
	glUniform1i(CubeMapUniformLocation, 2);

	glBindVertexArray(CubeObjectID);
	ScaleMatrix = glm::scale(glm::mat4(), glm::vec3(50.0f, 50.0f, 50.0f));

	GLuint SkyboxTransformMatrixUniformLocation = glGetUniformLocation(CubeMapProgramID, "SkyboxTransformMatrix");
	CameraMatrix[3][0] = 0.0;
	CameraMatrix[3][1] = 0.0;
	CameraMatrix[3][2] = 0.0;
	FullTransformMatrix = projectionMatrix * CameraMatrix * ScaleMatrix;
	glUniformMatrix4fv(SkyboxTransformMatrixUniformLocation, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)CubeElementArrayOffset);
}

void MeGlWindow::UserInput()
{
//	renderer()->CreateCubeInScene("Cube1");
//	renderer()->CreateCubeInScene("Cube2");
//	renderer()->setPositionforObject(glm::vec3(-3, 0, -5), "Cube1");
//	renderer()->setPositionforObject(glm::vec3(3, 0, -5), "Cube2");
//	renderer()->CreatePlaneInScene("Plane1");
//	renderer()->setPositionforObject(glm::vec3(0, -2, -5), "Plane1");
//	renderer()->CreatePointLight("PL1", glm::vec3(0.0f, 3.0f, -5.0f));
//	renderer()->ImportTexture("Data/Texture/MyTexture.png");
	
}

void MeGlWindow::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key::Key_W:
		renderer()->getCurrentCamera()->move_forward();
		break;
	case Qt::Key::Key_S:
		renderer()->getCurrentCamera()->move_backward();
		break;
	case Qt::Key::Key_A:
		renderer()->getCurrentCamera()->move_leftward();
		break;
	case Qt::Key::Key_D:
		renderer()->getCurrentCamera()->move_rightward();
		break;
	case Qt::Key::Key_R:
		renderer()->getCurrentCamera()->move_upward();
		break;
	case Qt::Key::Key_F:
		renderer()->getCurrentCamera()->move_downward();
		break;
	case Qt::Key::Key_Q:
		renderer()->getCurrentCamera()->rotate_left();
		break;
	case Qt::Key::Key_E:
		renderer()->getCurrentCamera()->rotate_right();
		break;
	case Qt::Key::Key_Z:
		renderer()->getCurrentCamera()->rotate_up();
		break;
	case Qt::Key::Key_C:
		renderer()->getCurrentCamera()->rotate_down();
		break;
	case Qt::Key::Key_T:
		renderer()->getLightCamera()->rotate_left();
		break;
	case Qt::Key::Key_Y:
		renderer()->getLightCamera()->rotate_right();
		break;
	case Qt::Key::Key_G:
		renderer()->getLightCamera()->rotate_up();
		break;
	case Qt::Key::Key_H:
		renderer()->getLightCamera()->rotate_down();
		break;
	case Qt::Key::Key_I:
		if (PointLight* p = renderer()->getCurrentPLight())		
			p->Move_forward();
		break;	
	case Qt::Key::Key_K:
		if (PointLight* p = renderer()->getCurrentPLight())
			p->Move_backward();
		break;
	case Qt::Key::Key_J:
		if (PointLight* p = renderer()->getCurrentPLight())
			p->Move_leftward();
		break;
	case Qt::Key::Key_L:
		if (PointLight* p = renderer()->getCurrentPLight())
			p->Move_rightward();
		break;
	case Qt::Key::Key_U:
		if (PointLight* p = renderer()->getCurrentPLight())
			p->Move_upward();
		break;
	case Qt::Key::Key_O:
		if (PointLight* p = renderer()->getCurrentPLight())
			p->Move_downward();
		break;
	}
	repaint();
}