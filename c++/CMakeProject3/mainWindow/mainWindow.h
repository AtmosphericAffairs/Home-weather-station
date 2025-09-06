#pragma once
#include <QSystemTrayIcon>
#include <QMenu>
#include <iostream>
#include <QApplication>
#include <QWidget>
#include <QFile>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QDebug> //на удаление
#include <QDir> //на удаление
#include <QMainWindow>
#include <QCloseEvent>
#include <QIcon>
#include <QPropertyAnimation> 
#include <string>
#include "../middlepanel/middle_panel.h"
#include "../toppanel/topPanel.h"


class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	void update_values(double t, double w, double p);
public slots:
	void closePr();
signals:
	void closeProgram();
protected:
	void closeEvent(QCloseEvent* event) override;
private:
	QSystemTrayIcon* m_trayIcon;
	QPropertyAnimation* m_fadeAnimation;
	TopPanel* topPanel;
	MiddlePanel* middlePanel;
	void createTryIcon();
	void removeTrayIcon();
	void startFadeOut();
};
