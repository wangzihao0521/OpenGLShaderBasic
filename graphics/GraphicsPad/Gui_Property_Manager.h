#pragma once
#include <QtGui\qwidget.h>
#include <MeGlWindow.h>
#include "FunctionButton.h"


class Gui_Property_Manager : public QWidget{
	
	Q_OBJECT

protected:
	Object* CurrentObj;

	QVBoxLayout* MainLayout = new QVBoxLayout;
	QHBoxLayout* NameLayout = new QHBoxLayout;
	QVBoxLayout* TransformLayout = new QVBoxLayout;
	QHBoxLayout* MaterialLayout = new QHBoxLayout;
	QVBoxLayout* MaterialPropertyLayout = new QVBoxLayout;
	QVBoxLayout* BindFunctionLayout = new QVBoxLayout;
	QLabel* NameLabel = new QLabel;
	QLabel* objName = new QLabel;
	QLabel* TransformLabel = new QLabel;	
	QLabel* MaterialLabel = new QLabel;
	QLabel* matName = new QLabel;
	
public:
	FunctionButton* Position = new FunctionButton("position", "change", 3);
	FunctionButton* Rotation = new FunctionButton("rotation", "change", 3);
	FunctionButton* Scale = new FunctionButton("scale", "change", 3);
	FunctionButton* BindMaterial = new FunctionButton("BindMaterial");
	FunctionButton* BindProperty = new FunctionButton("BindProperty", "do it", 2);
private:
	void deleteAllWidget();
	void setValueForAllWidget(Object* obj);

public:
	Gui_Property_Manager(Object* obj);

	void refresh(Object* obj);
};
