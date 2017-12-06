#ifndef FUNCTION_BUTTON_H
#define FUNCTION_BUTTON_H

#include <QtGui\qwidget.h>
#include <QtGui\qpushbutton.h>
#include <QtGui\qtextedit.h>
#include <QtGui\qlabel.h>
#include <QtGui\qhboxlayout>

class FunctionButton : public QWidget 
{
	Q_OBJECT

	QPushButton* button;
	QLabel* label;
	QTextEdit* textBox;

private slots:
	void ButtonIsClicked();

signals:
	void clicked();

public:
	FunctionButton(QString functionName, QString buttonText = "Do it");
	QString getArguements() { return textBox->toPlainText(); }
};


#endif // !FUNCTION_BUTTON_H

