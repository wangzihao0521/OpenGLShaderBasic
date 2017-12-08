#include "GuiManager.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>


void GuiManager::SetAllConnections()
{
	connect(CreateCube, SIGNAL(clicked()), this, SLOT(CreateCubeInScene()));
	connect(CreatePlane, SIGNAL(clicked()), this, SLOT(CreatePlaneInScene()));
	connect(CreatePointLight, SIGNAL(clicked()), this, SLOT(CreatePointLightInScene()));
	connect(FB_ImportTexture, SIGNAL(clicked()), this, SLOT(ImportTexture()));
	connect(CreateMaterial, SIGNAL(clicked()), this, SLOT(CreateMat()));
	connect(AddProperty_Material, SIGNAL(clicked()), this, SLOT(AddPro2Mat()));
	connect(PropertyManager, SIGNAL(ChangePos(glm::vec3)), this, SLOT(setPositionForCurrentObject(glm::vec3)));
	connect(PropertyManager, SIGNAL(ChangeRot(glm::vec3)), this, SLOT(setRotationForCurrentObject(glm::vec3)));
	connect(PropertyManager, SIGNAL(ChangeScale(glm::vec3)), this, SLOT(setScaleForCurrentObject(glm::vec3)));
	connect(PropertyManager, SIGNAL(ChangeMaterial(char*)), this, SLOT(BindMaterialToCurrentObject(char*)));
	connect(PropertyManager, SIGNAL(ChangeProperty(char*,char*)), this, SLOT(BindPropertyToCurrentMaterial(char*,char*)));
	connect(PropertyManager, SIGNAL(ChangeVec3(char*, glm::vec3)), this, SLOT(BindPropertyToCurrentMaterial(char*, glm::vec3)));
	connect(PropertyManager, SIGNAL(ChangeVec2(char*, glm::vec2)), this, SLOT(BindPropertyToCurrentMaterial(char*, glm::vec2)));
	connect(PropertyManager, SIGNAL(ChangeFloat(char*, float)), this, SLOT(BindPropertyToCurrentMaterial(char*, float)));
	connect(PropertyManager, SIGNAL(SwitchToNextObject()), this, SLOT(NextCurrentObject()));
	connect(PropertyManager, SIGNAL(ToggleCastShadow()), this, SLOT(ToggleCastShadows()));
	connect(PropertyManager, SIGNAL(ToggleReceiveShadow()), this, SLOT(ToggleReceiveShadows()));
}

void GuiManager::RefreshPropertyManager()
{
	Object* obj = MyWindow->renderer()->getCurrentObject();
	PropertyManager->refresh(obj);
}

void GuiManager::RegisterPropertyType()
{
	m["Tex2D"] = M_PropertyType::M_Texture2D;
	m["Tex3D"] = M_PropertyType::M_Texture3D;
	m["vec2"] = M_PropertyType::M_vec2;
	m["vec3"] = M_PropertyType::M_vec3;
	m["float"] = M_PropertyType::M_float;
}

GuiManager::GuiManager()
{
	QVBoxLayout* MainLayout;
	setLayout(MainLayout = new QVBoxLayout);
	QVBoxLayout* SceneControlLayout;
	MainLayout->addLayout(SceneControlLayout = new QVBoxLayout);
	SceneControlLayout->setAlignment(Qt::AlignLeft);
	QHBoxLayout* SceneLayout;
	MainLayout->addLayout(SceneLayout = new QHBoxLayout);
	SceneLayout->addWidget(MyWindow);
	MyWindow->setFocusPolicy(Qt::ClickFocus);
//	QVBoxLayout* PropertyControlLayout;
//	SceneLayout->addLayout(PropertyControlLayout = new QVBoxLayout);
	SceneLayout->addWidget(PropertyManager);
	QHBoxLayout* CreateThingsLayout = new QHBoxLayout();
	SceneControlLayout->addLayout(CreateThingsLayout);
	CreateThingsLayout->setAlignment(Qt::AlignLeft);
	CreateThingsLayout->addWidget(CreateCube);
	CreateThingsLayout->addWidget(CreatePlane);
	CreateThingsLayout->addWidget(CreatePointLight);
	SceneControlLayout->addWidget(FB_ImportTexture);
	SceneControlLayout->addWidget(CreateMaterial);
	SceneControlLayout->addWidget(AddProperty_Material);
	SetAllConnections();

	RegisterPropertyType();
}

void GuiManager::CreateCubeInScene()
{
	QString Arguement = CreateCube->getArguement();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->CreateCubeInScene(ba->data());
		MyWindow->setFocus();
		RefreshPropertyManager();
	}
}

void GuiManager::CreatePlaneInScene()
{
	QString Arguement = CreatePlane->getArguement();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->CreatePlaneInScene(ba->data());
		MyWindow->setFocus();
		RefreshPropertyManager();
	}
}

void GuiManager::CreatePointLightInScene()
{
	QString Arguement = CreatePointLight->getArguement();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->CreatePointLight(ba->data());
		MyWindow->setFocus();
		RefreshPropertyManager();
	}
}

void GuiManager::ImportTexture()
{
	QString Arguement = FB_ImportTexture->getArguement();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->ImportTexture(ba->data());
	}
}

void GuiManager::CreateMat()
{
	std::vector<QString> Arguements = CreateMaterial->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	QByteArray* ba0 = new QByteArray(Arguements[0].toLatin1());
	QByteArray* ba1 = new QByteArray(Arguements[1].toLatin1());
	QByteArray* ba2 = new QByteArray(Arguements[2].toLatin1());

	MyWindow->renderer()->CreateMaterial(ba0->data(), ba1->data(), ba2->data());
}

void GuiManager::AddPro2Mat()
{
	std::vector<QString> Arguements = AddProperty_Material->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	QByteArray* ba0 = new QByteArray(Arguements[0].toLatin1());
	QByteArray* ba1 = new QByteArray(Arguements[1].toLatin1());
	QByteArray* ba2 = new QByteArray(Arguements[2].toLatin1());
	
	M_PropertyType type;
	if (strcmp(ba2->data(), "vec3") == 0)
		type = M_vec3;
	else if (strcmp(ba2->data(), "vec2") == 0)
		type = M_vec2;
	else if (strcmp(ba2->data(), "float") == 0)
		type = M_float;
	else if (strcmp(ba2->data(), "Tex2D") == 0)
		type = M_Texture2D;
	switch (type) 
	{
	case M_Texture2D:
	{
		QByteArray* ba3 = new QByteArray(Arguements[3].toLatin1());
		MyWindow->renderer()->Add_Property_Material(ba0->data(), ba1->data(), type, ba3->data());
		break;
	}
	case M_vec3:
	{
		QStringList sl = Arguements[3].split(',');
		glm::vec3 newVec3 = glm::vec3();
		newVec3.x = sl[0].toFloat();
		newVec3.y = sl[1].toFloat();
		newVec3.z = sl[2].toFloat();
		MyWindow->renderer()->Add_Property_Material(ba0->data(), ba1->data(), type, newVec3);
		break;
	}
	case M_vec2:
	{
		QStringList sl = Arguements[3].split(',');
		glm::vec2 newVec2 = glm::vec2();
		newVec2.x = sl[0].toFloat();
		newVec2.y = sl[1].toFloat();
		MyWindow->renderer()->Add_Property_Material(ba0->data(), ba1->data(), type, newVec2);
		break;
	}
	case M_float:
	{
		MyWindow->renderer()->Add_Property_Material(ba0->data(), ba1->data(), type, Arguements[3].toFloat());
		break;
	}
	}
	
}

void GuiManager::setPositionForCurrentObject(glm::vec3 newPos)
{
	MyWindow->renderer()->setPositionforCurrentObject(newPos);
	MyWindow->setFocus();
}

void GuiManager::setRotationForCurrentObject(glm::vec3 newRot)
{
	MyWindow->renderer()->setRotationforCurrentObject(newRot);
	MyWindow->setFocus();
}

void GuiManager::setScaleForCurrentObject(glm::vec3 newScale)
{
	MyWindow->renderer()->setScaleforCurrentObject(newScale);
	MyWindow->setFocus();
}

void GuiManager::BindMaterialToCurrentObject(char* matName)
{
	MyWindow->renderer()->BindMaterial2CurrentObject(matName);
	MyWindow->setFocus();
	RefreshPropertyManager();
}

void GuiManager::BindPropertyToCurrentMaterial(char* PropertyName,char* PropertyValues)
{
	MyWindow->renderer()->Bind_Property_CurrentMaterial(PropertyName, PropertyValues);
	MyWindow->setFocus();
	RefreshPropertyManager();
}

void GuiManager::BindPropertyToCurrentMaterial(char* PropertyName, glm::vec3 PropertyValues)
{
	MyWindow->renderer()->Bind_Property_CurrentMaterial(PropertyName, PropertyValues);
	MyWindow->setFocus();
	RefreshPropertyManager();
}

void GuiManager::BindPropertyToCurrentMaterial(char* PropertyName, glm::vec2 PropertyValues)
{
	MyWindow->renderer()->Bind_Property_CurrentMaterial(PropertyName, PropertyValues);
	MyWindow->setFocus();
	RefreshPropertyManager();
}

void GuiManager::BindPropertyToCurrentMaterial(char* PropertyName, float PropertyValues)
{
	MyWindow->renderer()->Bind_Property_CurrentMaterial(PropertyName, PropertyValues);
	MyWindow->setFocus();
	RefreshPropertyManager();
}

void GuiManager::NextCurrentObject()
{
	MyWindow->renderer()->switchtoNextObject();
	RefreshPropertyManager();
}

void GuiManager::ToggleCastShadows()
{
	MyWindow->renderer()->getCurrentObject()->toggleCastShadow();
	MyWindow->setFocus();
}

void GuiManager::ToggleReceiveShadows()
{
	MyWindow->renderer()->getCurrentObject()->toggleReceiveShadow();
	MyWindow->setFocus();
}
