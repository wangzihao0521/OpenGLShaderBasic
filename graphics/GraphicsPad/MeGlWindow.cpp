#include <gl\glew.h>
#include <MeGlWindow.h>
#include <Vertex.h>
#include <ShapeFactory.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp>
#include <QtGui\qkeyevent>
#include <Camera.h>
#include <iostream>
#include <fstream>

static GLuint   CubeElementArrayOffset;
static GLuint   PlaneElementArrayOffset;
static GLuint	CubenumIndices;
static GLuint	PlanenumIndices;
static GLuint	CubeObjectID;
static GLuint	PlaneObjectID;

GLuint programID;

Camera camera;

void MeGlWindow::senddatatoOpenGL()
{
	glClearColor(0, 0, 0, 1);

	Shapedata Cube = ShapeFactory::MakeCube();
	Shapedata Plane = ShapeFactory::MakePlane();

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
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);

	glBindVertexArray(PlaneObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(Cube.VertexBufferSize()+Cube.IndicesBufferSize()));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float) + Cube.VertexBufferSize() + Cube.IndicesBufferSize()));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float) + Cube.VertexBufferSize() + Cube.IndicesBufferSize()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);

	Cube.cleanup();
	Plane.cleanup();
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
	std::string temp = ReadShaderCode("VertexShader.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(VertexShaderID, 1, adapter, 0);
	temp = ReadShaderCode("FragmentShader.glsl");
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

	glUseProgram(programID);
}

void MeGlWindow::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	senddatatoOpenGL();
	installshaders();
}

void MeGlWindow::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0,0,width(),height());
	glm::mat4 CameraMatrix = camera.getWorldToViewMatrix();
	glm::mat4 projectionMatrix = glm::perspective(60.0f, ((float)width() / height()), 0.1f, 20.0f);

	glm::mat4 World2ProjectionMatrix = projectionMatrix * CameraMatrix ;

	glm::mat4 FullTransformMatrix;
	GLuint FullTransformMatrixUniformLocaiton;
	glm::mat4 TransformMatrix;
	glm::mat4 RotationMatrix;
	//Light Begins Here
	glm::vec3 AmbientLight(0.2f, 0.2f, 0.2f);

	glm::vec3 LightPosition(0.0f, 3.0f, -3.0f);

	GLuint AmbientLightUniformLocation = glGetUniformLocation(programID, "AmbientLight");
	glUniform3fv(AmbientLightUniformLocation, 1, &AmbientLight[0]);

	GLuint LightPositionUniformLocation = glGetUniformLocation(programID, "LightPosition");
	glUniform3fv(LightPositionUniformLocation, 1, &LightPosition[0]);

	//Cube1
	glBindVertexArray(CubeObjectID);
	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(+3.0f, 0.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	
	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;

	FullTransformMatrixUniformLocaiton = glGetUniformLocation(programID, "FullTransformMatrix");
	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)(CubeElementArrayOffset));

	//Cube2
	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(-3.0f, 0.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), 66.0f, glm::vec3(1.0f, -1.0f, 0.0f));

	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;

	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, CubenumIndices, GL_UNSIGNED_SHORT, (void*)(CubeElementArrayOffset));

	//plane
	glBindVertexArray(PlaneObjectID);
	TransformMatrix = glm::translate(glm::mat4(), glm::vec3(-0.0f, -2.0f, -5.0f));
	RotationMatrix = glm::rotate(glm::mat4(), 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	FullTransformMatrix = World2ProjectionMatrix * TransformMatrix * RotationMatrix;

	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, PlanenumIndices, GL_UNSIGNED_SHORT, (void*)(PlaneElementArrayOffset));
}

void MeGlWindow::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key::Key_W:
		camera.move_forward();
		break;
	case Qt::Key::Key_S:
		camera.move_backward();
		break;
	case Qt::Key::Key_A:
		camera.move_leftward();
		break;
	case Qt::Key::Key_D:
		camera.move_rightward();
		break;
	case Qt::Key::Key_R:
		camera.move_upward();
		break;
	case Qt::Key::Key_F:
		camera.move_downward();
		break;
	case Qt::Key::Key_Q:
		camera.rotate_left();
		break;
	case Qt::Key::Key_E:
		camera.rotate_right();
		break;
	case Qt::Key::Key_Z:
		camera.rotate_up();
		break;
	case Qt::Key::Key_C:
		camera.rotate_down();
		break;
	}
	repaint();
}