#include "Gui_Property_Manager.h"

Gui_Property_Manager::Gui_Property_Manager(Object* obj)
{
	CurrentObj = obj;
	refresh(obj);
	setLayout(MainLayout);

	MainLayout->addLayout(NameLayout);
	NameLayout->setAlignment(Qt::AlignLeft);
	NameLayout->addWidget(NameLabel);
	NameLayout->addWidget(objName);

	MainLayout->addWidget(TransformLabel);


}

void Gui_Property_Manager::refresh(Object * obj)
{
	CurrentObj = obj;
	if (CurrentObj == nullptr)
	{
		return;
	}	
	
	
	
}
