#include "Gui_Property_Manager.h"

void Gui_Property_Manager::deleteAllWidget()
{
	delete NameLabel;
	delete objName;
	delete SwitchNext;
	delete Position;
	delete Rotation;
	delete Scale;
	delete MaterialLabel;
	delete matName;
	delete BindMaterial;
	delete BindProperty;
	delete CastShadowLabel;
	delete ReceiveShadowLabel;
	delete IsCastShadow;
	delete IsReceiveShadow;
	QLayoutItem* child;
	for (auto iter = SinglePropertyLayout.begin(); iter != SinglePropertyLayout.end(); iter++)
	{
		while ((child = (*iter)->takeAt(0)) != 0)
		{
			delete child->widget();
			delete child;
		}
	}
}

void Gui_Property_Manager::setValueForAllWidget(Object* obj)
{
	NameLabel = new QLabel("name");
	objName = new QLabel(obj->getName());
	SwitchNext = new QPushButton;
	SwitchNext->setText("NextObject");
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
	CastShadowLabel = new QLabel("Cast Shadow");
	ReceiveShadowLabel = new QLabel("Receive Shadow");
	IsCastShadow = new QCheckBox();
	IsReceiveShadow = new QCheckBox();
}

Gui_Property_Manager::Gui_Property_Manager(Object* obj)
{
	CurrentObj = obj;
	refresh(obj);
	setLayout(MainLayout);
//	MainLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
//	MainLayout->setAlignment(Qt::AlignTop);

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

	MainLayout->addLayout(CastShadowLayout);
	CastShadowLayout->setAlignment(Qt::AlignLeft);

	MainLayout->addLayout(ReceiveShadowLayout);
	ReceiveShadowLayout->setAlignment(Qt::AlignLeft);
	
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
	NameLayout->addWidget(SwitchNext);

	connect(SwitchNext, SIGNAL(clicked()), this, SLOT(NextObj()));
	
	TransformLayout->addWidget(Position);

	connect(Position, SIGNAL(clicked()), this, SLOT(PositionButtonClicked()));

	CastShadowLayout->addWidget(CastShadowLabel);
	CastShadowLayout->addWidget(IsCastShadow);
	IsCastShadow->setChecked(obj->Is_CastShadow());

	connect(IsCastShadow, SIGNAL(stateChanged(int)), this, SLOT(CastShadowChanged()));

	if (obj->getType() == Non_Light)
	{
		TransformLayout->addWidget(Rotation);
		TransformLayout->addWidget(Scale);

		connect(Rotation, SIGNAL(clicked()), this, SLOT(RotationButtonClicked()));
		connect(Scale, SIGNAL(clicked()), this, SLOT(ScaleButtonClicked()));

		MaterialLayout->addWidget(MaterialLabel);
		MaterialLayout->addWidget(matName);

		std::vector<M_Property*> AllMaterialProperty = obj->getMaterial().PropertyArray;

		for (auto iter = AllMaterialProperty.begin(); iter != AllMaterialProperty.end(); iter++)
		{
			QHBoxLayout* onePropertyLayout = new QHBoxLayout;
			MaterialPropertyLayout->addLayout(onePropertyLayout);
			onePropertyLayout->setAlignment(Qt::AlignLeft);
			QLabel* PropertyNameLabel = new QLabel((*iter)->getName());
			QLabel* PropertyValueLabel = new QLabel;
			switch ((*iter)->getType())
			{
			case M_Texture2D:
			{
				PropertyValueLabel->setText((*iter)->getTexture()->getName());
				break;
			}
			case M_vec3:
			{
				glm::vec3 Vec3 = (*iter)->getVec3();
				std::ostringstream oss,oss1,oss2;
				oss << Vec3.x;
				std::string x = oss.str();
				oss1 << Vec3.y;
				std::string y = oss1.str();
				oss2 << Vec3.z;
				std::string z = oss2.str();
				PropertyValueLabel->setText((x +"," + y + "," + z).c_str());
				break;
			}
			case M_vec2:
			{
				glm::vec2 Vec2 = (*iter)->getVec2();
				std::ostringstream oss,oss1;
				oss << Vec2.x;
				std::string x = oss.str();
				oss1 << Vec2.y;
				std::string y = oss1.str();
				PropertyValueLabel->setText((x + "," + y ).c_str());
				break;
			}
			case M_float:
			{
				float f = (*iter)->getFloat();
				std::ostringstream oss;
				oss << f;
				PropertyValueLabel->setText((oss.str()).c_str());
				break;
			}
			default:
				break;
			}
			
			onePropertyLayout->addWidget(PropertyNameLabel);
			onePropertyLayout->addWidget(PropertyValueLabel);
			SinglePropertyLayout.push_back(onePropertyLayout);
		}

		BindFunctionLayout->addWidget(BindMaterial);
		BindFunctionLayout->addWidget(BindProperty);

		connect(BindMaterial, SIGNAL(clicked()), this, SLOT(BindMatButtonClicked()));
		connect(BindProperty, SIGNAL(clicked()), this, SLOT(BindPptButtonClicked()));

		ReceiveShadowLayout->addWidget(ReceiveShadowLabel);
		ReceiveShadowLayout->addWidget(IsReceiveShadow);
		IsReceiveShadow->setChecked(obj->Is_ReceiveShadow());

		connect(IsReceiveShadow, SIGNAL(stateChanged(int)), this, SLOT(ReceiveShadowChanged()));
	}
	else 
	{

	}
}

void Gui_Property_Manager::PositionButtonClicked()
{
	std::vector<QString> Arguements = Position->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	glm::vec3 newPos = glm::vec3();
	newPos.x = Arguements[0].toFloat();
	newPos.y = Arguements[1].toFloat();
	newPos.z = Arguements[2].toFloat();

	emit ChangePos(newPos);
}

void Gui_Property_Manager::RotationButtonClicked()
{
	std::vector<QString> Arguements = Rotation->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	glm::vec3 newRot = glm::vec3();
	newRot.x = Arguements[0].toFloat();
	newRot.y = Arguements[1].toFloat();
	newRot.z = Arguements[2].toFloat();

	emit ChangeRot(newRot);
}

void Gui_Property_Manager::ScaleButtonClicked()
{
	std::vector<QString> Arguements = Scale->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}
	glm::vec3 newScale = glm::vec3();
	newScale.x = Arguements[0].toFloat();
	newScale.y = Arguements[1].toFloat();
	newScale.z = Arguements[2].toFloat();

	emit ChangeScale(newScale);
}

void Gui_Property_Manager::BindMatButtonClicked()
{
	QString Arguement = BindMaterial->getArguement();
	QByteArray* ba = new QByteArray(Arguement.toLatin1());
	if (Arguement != "")
	{
		emit ChangeMaterial(ba->data());
	}
}

void Gui_Property_Manager::BindPptButtonClicked()
{
	std::vector<QString> Arguements = BindProperty->getArguements();
	for (auto iter = Arguements.begin(); iter != Arguements.end(); iter++)
	{
		if (*iter == "")
			return;
	}

	QByteArray* ba0 = new QByteArray(Arguements[0].toLatin1());

	M_Property* p = CurrentObj->getMaterial().FindPropertyByName(ba0->data());
	if (p == nullptr)
		return;
	switch (p->getType())
	{
	case M_Texture2D:
	{
		QByteArray* ba1 = new QByteArray(Arguements[1].toLatin1());
		emit ChangeProperty(ba0->data(), ba1->data());
		break;
	}
	case M_vec3:
	{
		QStringList sl = Arguements[1].split(',');
		glm::vec3 newVec3 = glm::vec3();
		newVec3.x = sl[0].toFloat();
		newVec3.y = sl[1].toFloat();
		newVec3.z = sl[2].toFloat();
		emit ChangeVec3(ba0->data(), newVec3);
		break;
	}
	case M_vec2:
	{
		QStringList sl = Arguements[1].split(',');
		glm::vec2 newVec2 = glm::vec2();
		newVec2.x = sl[0].toFloat();
		newVec2.y = sl[1].toFloat();
		emit ChangeVec2(ba0->data(), newVec2);
		break;
	}
	case M_float:
	{
		emit ChangeFloat(ba0->data(), Arguements[1].toFloat());
		break;
	}
	default:
		break;
	}
	
	
}

void Gui_Property_Manager::NextObj()
{
	emit SwitchToNextObject();
}

void Gui_Property_Manager::CastShadowChanged()
{
	emit ToggleCastShadow();
}

void Gui_Property_Manager::ReceiveShadowChanged()
{
	emit ToggleReceiveShadow();
}
