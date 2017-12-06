#pragma once
#include <QtGui\qwidget.h>
#include <MeGlWindow.h>
#include "FunctionButton.h"

class Gui_Property_Manager : public QWidget{
	
	Q_OBJECT

protected:
	Object* CurrentObj;

	QVBoxLayout* MainLayout = new QVBoxLayout();
	QHBoxLayout* NameLayout = new QHBoxLayout();
	QLabel* NameLabel = new QLabel;
	QLabel* objName = new QLabel;
	QLabel* TransformLabel = new QLabel;
public:
	Gui_Property_Manager(Object* obj);

	void refresh(Object* obj);
};
