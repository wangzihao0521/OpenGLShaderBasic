#ifndef FUNCTION_BUTTON_H
#define FUNCTION_BUTTON_H

#include <QtGui\qwidget.h>
#include <QtGui\qpushbutton.h>
#include <QtGui\qtextedit.h>
#include <QtGui\qlabel.h>
#include <QtGui\qhboxlayout>
#include <vector>
#include <string>

class FunctionButton : public QWidget 
{
	Q_OBJECT

	QPushButton* button;
	QLabel* label;
	std::vector<QTextEdit*> textBox;

private slots:
	void ButtonIsClicked();

signals:
	void clicked();

public:
	FunctionButton(QString functionName, QString buttonText = "Do it", int ArguementAmount = 1);
	QString getArguement() { return textBox[0]->toPlainText(); }
	std::vector<QString> getArguements();
	void setText(std::string text1, std::string text2, std::string text3);
};


#endif // !FUNCTION_BUTTON_H

