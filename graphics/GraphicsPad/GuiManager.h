#pragma once
#include <unordered_map>
#include "Gui_Property_Manager.h"

class GuiManager : public QWidget{

	Q_OBJECT

protected:
	MeGlWindow* MyWindow = new MeGlWindow;
	std::unordered_map<char*, M_PropertyType> m;
	Gui_Property_Manager* PropertyManager = new Gui_Property_Manager(MyWindow->renderer()->getCurrentObject());
	FunctionButton* CreateCube = new FunctionButton("CreateCubeInScene");
	FunctionButton* CreatePlane = new FunctionButton("CreatePlaneInScene");
	FunctionButton* CreatePointLight = new FunctionButton("CreatePointLightInScene");
	FunctionButton* FB_ImportTexture = new FunctionButton("ImportTexture");
	FunctionButton* CreateMaterial = new FunctionButton("CreateMaterial", "do it", 3);
	FunctionButton* AddProperty_Material = new FunctionButton("AddProperty2Mat", "do it", 4);

private:
	void SetAllConnections();
	void RefreshPropertyManager();
	void RegisterPropertyType();

private slots:
	void CreateCubeInScene();
	void CreatePlaneInScene();
	void CreatePointLightInScene();
	void ImportTexture();
	void CreateMat();
	void AddPro2Mat();
	void setPositionForCurrentObject(glm::vec3 newPos);
	void setRotationForCurrentObject(glm::vec3 newPos);
	void setScaleForCurrentObject(glm::vec3 newPos);
	void BindMaterialToCurrentObject(char* matName);
	void BindPropertyToCurrentMaterial(char* PropertyName,char* PropertyValue);
	void BindPropertyToCurrentMaterial(char*, glm::vec3);
	void BindPropertyToCurrentMaterial(char*, glm::vec2);
	void BindPropertyToCurrentMaterial(char*, float);
	void NextCurrentObject();
	void ToggleCastShadows();
	void ToggleReceiveShadows();
public:
	GuiManager();
	~GuiManager(void) {}

//	void keyPressEvent(QKeyEvent*);
};
