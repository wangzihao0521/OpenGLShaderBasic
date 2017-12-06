#include "GuiManager.h"
#include <QtGui\qvboxlayout>
#include <QtGui\qhboxlayout>


void GuiManager::SetAllConnections()
{
	connect(CreateCube, SIGNAL(clicked()), this, SLOT(CreateCubeInScene()));
	connect(CreatePlane, SIGNAL(clicked()), this, SLOT(CreatePlaneInScene()));
	connect(CreatePointLight, SIGNAL(clicked()), this, SLOT(CreatePointLightInScene()));
	connect(FB_ImportTexture, SIGNAL(clicked()), this, SLOT(ImportTexture()));
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
	QString Arguement = CreateCube->getArguements();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->CreateCubeInScene(ba->data());
		MyWindow->setFocus();
	}
}

void GuiManager::CreatePlaneInScene()
{
	QString Arguement = CreatePlane->getArguements();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->CreatePlaneInScene(ba->data());
		MyWindow->setFocus();
	}
}

void GuiManager::CreatePointLightInScene()
{
	QString Arguement = CreatePointLight->getArguements();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->CreatePointLight(ba->data());
		MyWindow->setFocus();
	}
}

void GuiManager::ImportTexture()
{
	QString Arguement = FB_ImportTexture->getArguements();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		MyWindow->renderer()->ImportTexture(ba->data());
	}
}