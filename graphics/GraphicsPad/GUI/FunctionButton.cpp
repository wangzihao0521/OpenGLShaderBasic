#include "FunctionButton.h"

FunctionButton::FunctionButton(QString functionName, QString buttonText, int ArguementAmount)
{
	QHBoxLayout* layout;
	setLayout(layout = new QHBoxLayout);
	layout->setAlignment(Qt::AlignLeft);
	setMaximumWidth(550);
	layout->addWidget(label = new QLabel);
	label->setMinimumWidth(100);
	label->setAlignment(Qt::AlignCenter);
	label->setText(functionName);
	for (int i = 0; i < ArguementAmount; ++i)
	{
		QTextEdit* textObj = new QTextEdit;
		textBox.push_back(textObj);
		layout->addWidget(textObj);
		textObj->setMaximumWidth(350);
		textObj->setMaximumHeight(25);
		textObj->setAlignment(Qt::AlignLeft);
	}	
	layout->addWidget(button = new QPushButton);
	button->setText(buttonText);
	connect(button, SIGNAL(clicked()), this, SLOT(ButtonIsClicked()));

}

void FunctionButton::ButtonIsClicked() {
	
	emit clicked();
}

std::vector<QString> FunctionButton::getArguements() {
	std::vector<QString> Arguements;
	for (auto iter = textBox.begin(); iter != textBox.end(); ++iter)
	{
		Arguements.push_back((*iter)->toPlainText());
	}
	return Arguements;
}

void FunctionButton::setText(std::string text1, std::string text2, std::string text3)
{
	QString string0 = QString::fromStdString(text1);
	QString string1 = QString::fromStdString(text2);
	QString string2 = QString::fromStdString(text3);
	textBox[0]->setText(string0);
	textBox[1]->setText(string1);
	textBox[2]->setText(string2);
}
