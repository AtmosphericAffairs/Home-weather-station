#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QAction>
#include <QLabel>
#include <QApplication>

class QApplication;

class MiddlePanel : public QWidget {
	Q_OBJECT
public:
	explicit MiddlePanel(QWidget* parent = nullptr, QApplication* app = nullptr);
	void update_values(double t, double w, double p);

private:

	QApplication* app;
	QVBoxLayout* layout;
	QLabel* temperature_label;
	QLabel* wind_label;
	QLabel* pressure_label;
};