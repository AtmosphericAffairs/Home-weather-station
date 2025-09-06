#pragma once
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVariant>
#include <QMenu>
#include <QAction>
#include <QApplication>

class QApplication;

class TopPanel : public QWidget {
	Q_OBJECT
public: 
	explicit TopPanel(QWidget* parent = nullptr, QApplication* app = nullptr);

signals:
	void closeProgram();

private:
	QApplication* app;
	QAction* exitAction;
	QMenu* fileMenu;
	QHBoxLayout* layout;
	QPushButton* fileButton;
	QPushButton* settingButton;
};