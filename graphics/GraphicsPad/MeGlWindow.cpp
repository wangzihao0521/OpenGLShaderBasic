#include <gl\glew.h>
#include <MeGlWindow.h>

static GLuint	arraybufferoffset;
extern const char* vertexshader;
extern const char* fragmentshader;

void MeGlWindow::senddatatoOpenGL()
{
	glClearColor(0, 0, 0, 1);
	GLfloat vertexPos[] = {
		+0.0f,+0.0f,
		+1.0f,+0.0f,+0.0f,
		-1.0f,-1.0f,
		+0.0f,+1.0f,+0.0f,
		-1.0f,+1.0f,
		+0.0f,+0.0f,+1.0f,
		+1.0f,-1.0f,
		+0.0f,+0.0f,+1.0f,
		+1.0f,+1.0f,
		+0.0f,+1.0f,+0.0f,
	};

	GLuint BufferID;

	GLushort indices[] = {
		0,1,2,
		0,3,4
	};
	glGenBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPos) + sizeof(indices), 0, GL_STATIC_DRAW);

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexPos), vertexPos);
	arraybufferoffset = sizeof(vertexPos);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertexPos), sizeof(indices), indices);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
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

	GLuint programID = glCreateProgram();
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

	glViewport(0,0,width(),height());
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void*)(arraybufferoffset));
}