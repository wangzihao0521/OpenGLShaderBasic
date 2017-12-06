#include <Qt\qapplication.h>
#include "GuiManager.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	GuiManager MeGuiManager;
	MeGuiManager.show();
//	MeGlWindow meWindow;
//	meWindow.show();
	return app.exec();
}