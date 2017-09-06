#include <gl\glew.h>
#include <MeGlWindow.h>
#include <Vertex.h>
#include <ShapeFactory.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp>
#include <QtGui\qkeyevent>
#include <Camera.h>

static GLuint   CubeElementArrayOffset;
static GLuint   PlaneElementArrayOffset;
static GLuint	CubenumIndices;
static GLuint	PlanenumIndices;
static GLuint	CubeObjectID;
static GLuint	PlaneObjectID;
extern const char* vertexshader;
extern const char* fragmentshader;

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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);

	glBindVertexArray(PlaneObjectID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(Cube.VertexBufferSize()+Cube.IndicesBufferSize()));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)+ Cube.VertexBufferSize() + Cube.IndicesBufferSize()));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);

	Cube.cleanup();
	Plane.cleanup();
}

void MeGlWindow::installshaders()
{
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	//	const char* adapter[1];
	//	adapter[0] = vertexshader;
	glShaderSource(VertexShaderID, 1, &vertexshader, 0);
	//	adapter[0] = fragmentshader;
	glShaderSource(FragmentShaderID, 1, &fragmentshader, 0);

	glCompileShader(VertexShaderID);
	glCompileShader(FragmentShaderID);

	programID = glCreateProgram();
	glAttachShader(programID, VertexShaderID);
	glAttachShader(programID, FragmentShaderID);
	glLinkProgram(programID);
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