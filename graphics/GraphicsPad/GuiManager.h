#pragma once
#include "Gui_Property_Manager.h"

class GuiManager : public QWidget{

	Q_OBJECT

protected:
	MeGlWindow* MyWindow = new MeGlWindow;
	Gui_Property_Manager* PropertyManager = new Gui_Property_Manager(MyWindow->renderer()->getCurrentObject());
	FunctionButton* CreateCube = new FunctionButton("CreateCubeInScene");
	FunctionButton* CreatePlane = new FunctionButton("CreatePlaneInScene");
	FunctionButton* CreatePointLight = new FunctionButton("CreatePointLightInScene");
	FunctionButton* FB_ImportTexture = new FunctionButton("ImportTexture");

private:
	void SetAllConnections();
	void RefreshPropertyManager();

private slots:
	void CreateCubeInScene();
	void CreatePlaneInScene();
	void CreatePointLightInScene();
	void ImportTexture();
	void setPositionForCurrentObject();
	void setRotationForCurrentObject();
	void setScaleForCurrentObject();
	void BindMaterialToCurrentObject();
	void BindPropertyToCurrentMaterial();

public:
	GuiManager();
	~GuiManager(void) {}

//	void keyPressEvent(QKeyEvent*);
};
