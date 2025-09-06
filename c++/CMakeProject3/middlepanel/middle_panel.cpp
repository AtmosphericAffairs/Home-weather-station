#include "middle_panel.h"
//#include <QApplication>

MiddlePanel::MiddlePanel(QWidget* parent, QApplication* a) : QWidget(parent), app(a)
{
	layout = new QVBoxLayout(this);
	layout->setSpacing(0);          
	layout->setContentsMargins(0, 0, 0, 0);
	temperature_label = new QLabel(QStringLiteral("T: "), this);
	wind_label = new QLabel(QStringLiteral("W: "), this);
	pressure_label = new QLabel(QStringLiteral("P: "), this);

	QVariant classCssLabel("midl_label");
	QVariant classCssTemp("temperatureLabel");
	QVariant classCssWind("windLabel");
	QVariant classCssPress("pressureLabel");

	

	temperature_label->setProperty("class", classCssLabel);
	temperature_label->setProperty("class", classCssTemp);
	wind_label->setProperty("class", classCssLabel);
	wind_label->setProperty("class", classCssWind);
	pressure_label->setProperty("class", classCssLabel);
	pressure_label->setProperty("class", classCssPress);

	layout->addWidget(temperature_label);
	layout->addWidget(wind_label);
	layout->addWidget(pressure_label);

}

void MiddlePanel::update_values(double t, double w, double p) 
{
	

	if (!temperature_label || !wind_label || !pressure_label) {
		return;
	}

	temperature_label->setText(QStringLiteral("T: ") + QString::number(t, 'f', 1) + QStringLiteral(" �C"));
	wind_label->setText(QStringLiteral("W: ") + QString::number(w, 'f', 1) + QStringLiteral(" �/�"));
	pressure_label->setText(QStringLiteral("P: ") + QString::number(p, 'f', 1) + QStringLiteral(" ���"));
	
}