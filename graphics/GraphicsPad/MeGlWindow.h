#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include <QtOpenGL\qglwidget>
#include <string>
#include <Qt\qtimer.h>

class MeGlWindow : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();
	void senddatatoOpenGL();
	void installshaders();
	void keyPressEvent(QKeyEvent*);
	void LoadCubeMap();
	bool checkShaderStatus(GLuint ShaderID);
	bool checkProgramStatus(GLuint ProgramID);
	std::string ReadShaderCode(const char* file);
	static const char* TexFile[];

	QTimer	*Mytimer;
public:
};

#endif
