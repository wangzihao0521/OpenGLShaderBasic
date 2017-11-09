#ifndef ME_GL_WINDOW
#define ME_GL_WINDOW
#include "Renderer.h"
#include <QtOpenGL\qglwidget>
#include <string>
#include <Qt\qtimer.h>
#include <Camera.h>


class MeGlWindow : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();
//	void senddatatoRenderer();
//	void installshaders();
	void UserInput();
	void keyPressEvent(QKeyEvent*);
	void LoadCubeMap();
	void DrawObjects(Camera & camera);
//	bool checkShaderStatus(GLuint ShaderID);
//	bool checkProgramStatus(GLuint ProgramID);
//	std::string ReadShaderCode(const char* file);
	static const char* TexFile[];

	QTimer	*Mytimer;
	Renderer* MyRenderer;
	Renderer* renderer() { return MyRenderer->getInstatnce(); }
public:
};

#endif
