#include "Gui_Property_Manager.h"

void Gui_Property_Manager::deleteAllWidget()
{
	delete NameLabel;
	delete objName;
	delete Position;
	delete Rotation;
	delete Scale;
	delete MaterialLabel;
	delete matName;
	delete BindMaterial;
	delete BindProperty;
	QLayoutItem* child;
	while ((child = MaterialPropertyLayout->takeAt(0)) != 0)
	{
		delete child;
	}
	
}

void Gui_Property_Manager::setValueForAllWidget(Object* obj)
{
	NameLabel = new QLabel("name");
	objName = new QLabel(obj->getName());
	Position = new FunctionButton("position", "change", 3);
	Rotation = new FunctionButton("rotation", "change", 3);
	Scale = new FunctionButton("scale", "change", 3);
	Position->setText(std::to_string(obj->getTransform().getPosition().x), std::to_string(obj->getTransform().getPosition().y), std::to_string(obj->getTransform().getPosition().z));
	Rotation->setText(std::to_string(obj->getTransform().getRotation().x), std::to_string(obj->getTransform().getRotation().y), std::to_string(obj->getTransform().getRotation().z));
	Scale->setText(std::to_string(obj->getTransform().getScale().x), std::to_string(obj->getTransform().getScale().y), std::to_string(obj->getTransform().getScale().z));
	MaterialLabel = new QLabel("material");
	matName = new QLabel(obj->getMaterial().getName());
	BindMaterial = new FunctionButton("BindMaterial");
	BindProperty = new FunctionButton("BindProperty", "do it", 2);
}

Gui_Property_Manager::Gui_Property_Manager(Object* obj)
{
	CurrentObj = obj;
	refresh(obj);
	setLayout(MainLayout);

	MainLayout->addLayout(NameLayout);
	NameLayout->setAlignment(Qt::AlignLeft);
	
	MainLayout->addLayout(TransformLayout);
	TransformLayout->setAlignment(Qt::AlignLeft);

	MainLayout->addLayout(MaterialLayout);
	MaterialLayout->setAlignment(Qt::AlignLeft);

	MainLayout->addLayout(MaterialPropertyLayout);
	MaterialPropertyLayout->setAlignment(Qt::AlignLeft);

	MainLayout->addLayout(BindFunctionLayout);
	BindFunctionLayout->setAlignment(Qt::AlignLeft);
	
}

void Gui_Property_Manager::refresh(Object * obj)
{
	CurrentObj = obj;
	if (CurrentObj == nullptr)
	{
		return;
	}

	deleteAllWidget();
	setValueForAllWidget(obj);

	NameLayout->addWidget(NameLabel);
	NameLayout->addWidget(objName);
	
	TransformLayout->addWidget(Position);
	TransformLayout->addWidget(Rotation);
	TransformLayout->addWidget(Scale);

	MaterialLayout->addWidget(MaterialLabel);
	MaterialLayout->addWidget(matName);

	for (auto iter = obj->getMaterial().PropertyArray.begin(); iter != obj->getMaterial().PropertyArray.end(); iter++)
	{
		QHBoxLayout* onePropertyLayout = new QHBoxLayout;
		MaterialPropertyLayout->addLayout(onePropertyLayout);
		onePropertyLayout->setAlignment(Qt::AlignLeft);
		QLabel* PropertyNameLabel = new QLabel((*iter)->getName());
		QLabel* PropertyValueLabel = new QLabel((*iter)->getTexture()->getName());
		onePropertyLayout->addWidget(PropertyNameLabel);
		onePropertyLayout->addWidget(PropertyValueLabel);
	}

	BindFunctionLayout->addWidget(BindMaterial);
	BindFunctionLayout->addWidget(BindProperty);
}
