#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include <QtOpenGL\qglwidget>
#include <string>

class MeGlWindow : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();
	void senddatatoOpenGL();
	void installshaders();
	void keyPressEvent(QKeyEvent*);
	bool checkShaderStatus(GLuint ShaderID);
	bool checkProgramStatus(GLuint ProgramID);
	std::string ReadShaderCode(const char* file);

public:
};

#endif
