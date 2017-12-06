#include "FunctionButton.h"

FunctionButton::FunctionButton(QString functionName, QString buttonText)
{
	QHBoxLayout* layout;
	setLayout(layout = new QHBoxLayout);
	layout->setAlignment(Qt::AlignAbsolute);
	setMaximumWidth(500);
	layout->addWidget(label = new QLabel);
	label->setMinimumWidth(35);
	label->setMinimumWidth(5);
	label->setAlignment(Qt::AlignCenter);
	label->setText(functionName);
	layout->addWidget(textBox = new QTextEdit);
	textBox->setMaximumWidth(350);
	textBox->setMaximumHeight(25);
	textBox->setAlignment(Qt::AlignLeft);
	layout->addWidget(button = new QPushButton);
	button->setText(buttonText);
	connect(button, SIGNAL(clicked()), this, SLOT(ButtonIsClicked()));

}

void FunctionButton::ButtonIsClicked() {
	
	emit clicked();
}