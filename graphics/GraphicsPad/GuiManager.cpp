#include "GuiManager.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>


void GuiManager::SetAllConnections()
{
	connect(CreateCube, SIGNAL(clicked()), this, SLOT(CreateCubeInScene()));
	connect(CreatePlane, SIGNAL(clicked()), this, SLOT(CreatePlaneInScene()));
	connect(CreatePointLight, SIGNAL(clicked()), this, SLOT(CreatePointLightInScene()));
	connect(FB_ImportTexture, SIGNAL(clicked()), this, SLOT(ImportTexture()));
	connect(PropertyManager->Position, SIGNAL(clicked()), this, SLOT(setPositionForCurrentObject()));
	connect(PropertyManager->Rotation, SIGNAL(clicked()), this, SLOT(setRotationForCurrentObject()));
	connect(PropertyManager->Scale, SIGNAL(clicked()), this, SLOT(setScaleForCurrentObject()));
	connect(PropertyManager->BindMaterial, SIGNAL(clicked()), this, SLOT(BindMaterialToCurrentObject()));
	connect(PropertyManager->BindProperty, SIGNAL(clicked()), this, SLOT(BindPropertyToCurrentMaterial()));
}

void GuiManager::RefreshPropertyManager()
{
	Object* obj = MyWindow->renderer()->getCurrentObject();
	PropertyManager->refresh(obj);
}

GuiManager::GuiManager()
{
	QVBoxLayout* MainLayout;
	setLayout(MainLayout = new QVBoxLayout);
	QVBoxLayout* SceneControlLayout;
	MainLayout->addLayout(SceneControlLayout = new QVBoxLayout);
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
	SetAllConnections();
}

void GuiManager::CreateCubeInScene()
{
	QString Arguement = CreateCube->getArguement();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->CreateCubeInScene(ba->data());
		MyWindow->setFocus();
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

void GuiManager::setPositionForCurrentObject()
{
	std::vector<QString> Arguements = PropertyManager->Position->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	glm::vec3 newPos = glm::vec3();
	newPos.x = Arguements[0].toFloat();
	newPos.y = Arguements[1].toFloat();
	newPos.z = Arguements[2].toFloat();

	MyWindow->renderer()->setPositionforCurrentObject(newPos);
}

void GuiManager::setRotationForCurrentObject()
{
	std::vector<QString> Arguements = PropertyManager->Rotation->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	glm::vec3 newRot = glm::vec3();
	newRot.x = Arguements[0].toFloat();
	newRot.y = Arguements[1].toFloat();
	newRot.z = Arguements[2].toFloat();

	MyWindow->renderer()->setRotationforCurrentObject(newRot);
}

void GuiManager::setScaleForCurrentObject()
{
	std::vector<QString> Arguements = PropertyManager->Scale->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	glm::vec3 newScale = glm::vec3();
	newScale.x = Arguements[0].toFloat();
	newScale.y = Arguements[1].toFloat();
	newScale.z = Arguements[2].toFloat();

	MyWindow->renderer()->setScaleforCurrentObject(newScale);
}

void GuiManager::BindMaterialToCurrentObject()
{
	QString Arguement = FB_ImportTexture->getArguement();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->BindMaterial2CurrentObject(ba->data());
	}
}

void GuiManager::BindPropertyToCurrentMaterial()
{
	std::vector<QString> Arguements = PropertyManager->Scale->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	QByteArray* ba0 = new QByteArray(Arguements[0].toLatin1());
	QByteArray* ba1 = new QByteArray(Arguements[1].toLatin1());
	MyWindow->renderer()->Bind_Property_CurrentMaterial(ba0->data(), ba1->data());
}