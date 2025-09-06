#include "topPanel.h"
//#include <QApplication>




TopPanel::TopPanel(QWidget* parent, QApplication* a) : QWidget(parent), app(a)
{	
	layout = new QHBoxLayout(this);
	layout->setContentsMargins(5, 0, 0, 0);
	layout->setSpacing(5);

	fileButton = new QPushButton(QStringLiteral("����"), this);
	settingButton = new QPushButton(QStringLiteral("���������"), this);

	fileMenu = new QMenu(QStringLiteral("����"), this);
	exitAction = fileMenu->addAction(QStringLiteral("�����"));

	QVariant classCss("topButton");

	fileButton->setProperty("class", classCss);
	settingButton->setProperty("class", classCss);

	connect(exitAction, &QAction::triggered, this, [this]()
	{
		if (app)
		{
			emit closeProgram();
			app->quit();
		}
	});

	fileButton->setMenu(fileMenu);



	layout->addWidget(fileButton);
	layout->addWidget(settingButton);

	layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

	this->setFixedHeight(20);

}
