#include <gl\glew.h>
#include <MeGlWindow.h>
#include <Vertex.h>
#include <ShapeFactory.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\glm.hpp>


static GLuint	arraybufferoffset;
static GLuint	numIndices;
extern const char* vertexshader;
extern const char* fragmentshader;

GLuint programID;



void MeGlWindow::senddatatoOpenGL()
{
	glClearColor(0, 0, 0, 1);

	Shapedata renderShape = ShapeFactory::MakeCube();

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

	renderShape.cleanup();
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

	glm::mat4 TransformMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -5.0f));
	glm::mat4 RotationMatrix = glm::rotate(glm::mat4(), 45.0f, glm::vec3(1.0f, 1.0f, 0.0f));
	glm::mat4 projectionMatrix = glm::perspective(60.0f, ((float)width() / height()), 0.1f, 10.0f);

	glm::mat4 FullTransformMatrix = projectionMatrix*  TransformMatrix * RotationMatrix;

	GLuint FullTransformMatrixUniformLocaiton = glGetUniformLocation(programID, "FullTransformMatrix");
	glUniformMatrix4fv(FullTransformMatrixUniformLocaiton, 1, GL_FALSE, &FullTransformMatrix[0][0]);

	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, (void*)(arraybufferoffset));
}