#pragma once

#include <QtGui\qwidget.h>
#include <QtGui\qcheckbox.h>

#include "MeGlWindow.h"
#include "FunctionButton.h"

#include <sstream>


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
	QHBoxLayout* CastShadowLayout = new QHBoxLayout;
	QHBoxLayout* ReceiveShadowLayout = new QHBoxLayout;
	QLabel* NameLabel = new QLabel;
	QLabel* objName = new QLabel;
	QLabel* TransformLabel = new QLabel;	
	QLabel* MaterialLabel = new QLabel;
	QLabel* matName = new QLabel;
	QLabel* CastShadowLabel = new QLabel;
	QLabel* ReceiveShadowLabel = new QLabel;
	std::vector<QHBoxLayout*> SinglePropertyLayout;
	FunctionButton* Position = new FunctionButton("position", "change", 3);
	FunctionButton* Rotation = new FunctionButton("rotation", "change", 3);
	FunctionButton* Scale = new FunctionButton("scale", "change", 3);
	FunctionButton* BindMaterial = new FunctionButton("BindMaterial");
	FunctionButton* BindProperty = new FunctionButton("BindProperty", "Do it", 2);
	QPushButton* SwitchNext = new QPushButton;
	QCheckBox* IsCastShadow = new QCheckBox;
	QCheckBox* IsReceiveShadow = new QCheckBox;

private:
	void deleteAllWidget();
	void setValueForAllWidget(Object* obj);
signals:
	void ChangePos(glm::vec3 newPos);
	void ChangeRot(glm::vec3 newRot);
	void ChangeScale(glm::vec3 newScale);
	void ChangeMaterial(char * MaterialName);
	void ChangeProperty(char * PropertyName, char * PropertyValue);
	void ChangeVec3(char * PropertyName, glm::vec3 newVec3);
	void ChangeVec2(char * PropertyName, glm::vec2 newVec2);
	void ChangeFloat(char * PropertyName, float newFloat);
	void SwitchToNextObject();
	void ToggleCastShadow();
	void ToggleReceiveShadow();
private slots:
	void PositionButtonClicked();
	void RotationButtonClicked();
	void ScaleButtonClicked();
	void BindMatButtonClicked();
	void BindPptButtonClicked();
	void NextObj();
	void CastShadowChanged();
	void ReceiveShadowChanged();
public:
	Gui_Property_Manager(Object* obj);

	void refresh(Object* obj);
};
