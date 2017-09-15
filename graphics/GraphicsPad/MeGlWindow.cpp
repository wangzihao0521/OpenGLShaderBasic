#include <gl\glew.h>
#include <MeGlWindow.h>
#include <Vertex.h>
#include <ShapeFactory.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <QtGui\qkeyevent>

static GLuint	arraybufferoffset;
static GLuint	numIndices;
extern const char* vertexshader;
extern const char* fragmentshader;
GLuint programID;
glm::mat3 TransformMatrix = glm::mat3();
glm::mat3 RotationMatrix = glm::mat3();
GLfloat TransformX = 0.0f;
GLfloat TransformY = 0.0f;
GLfloat RotationAngle= 0.0f;
const GLfloat TransformSpeed = 0.1;



void MeGlWindow::senddatatoOpenGL()
{
	glClearColor(0, 0, 0, 1);

	Shapedata renderShape = ShapeFactory::MakeTriangle();

	GLuint BufferID;

	glGenBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, renderShape.VertexBufferSize()+renderShape.IndicesBufferSize(), 0, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, renderShape.VertexBufferSize(), renderShape.vertices);
	arraybufferoffset = renderShape.VertexBufferSize();
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, renderShape.VertexBufferSize(), renderShape.IndicesBufferSize(), renderShape.Indices);
	numIndices = renderShape.numIndices;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
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
	senddatatoOpenGL();
	installshaders();
}

void MeGlWindow::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0,0,width(),height());

	TransformMatrix[2][0] = TransformX;
	TransformMatrix[2][1] = TransformY;
	RotationMatrix = glm::mat3(glm::rotate(RotationAngle, glm::vec3(0.0f, 0.0f, 1.0f)));
	glm::mat3 FullMatrix = TransformMatrix * RotationMatrix;
	GLint FullMatrixUniformLocation = glGetUniformLocation(programID, "FullMatrix");
	glUniformMatrix3fv(FullMatrixUniformLocation,1,GL_FALSE,&FullMatrix[0][0]);


	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, (void*)(arraybufferoffset));
}

void MeGlWindow::keyPressEvent(QKeyEvent* e)
{
	switch (e->key())
	{
	case Qt::Key::Key_W:
		TransformY += TransformSpeed;
		break;
	case Qt::Key::Key_S:
		TransformY += -TransformSpeed;
		break;
	case Qt::Key::Key_A:
		TransformX += -TransformSpeed;
		break;
	case Qt::Key::Key_D:
		TransformX += TransformSpeed;
		break;
	case Qt::Key::Key_Q:
		RotationAngle += 5.0;
		break;
	case Qt::Key::Key_E:
		RotationAngle += -5.0;
		break;
	}
	repaint();
}