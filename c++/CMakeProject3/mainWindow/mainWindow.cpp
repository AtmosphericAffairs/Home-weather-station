#include "mainwindow.h"




MainWindow::MainWindow( QWidget* parent) : QMainWindow(parent), m_trayIcon(nullptr), m_fadeAnimation(new QPropertyAnimation(this, "windowOpacity", this))
{

    this->resize(800, 600);
    this->setWindowTitle("meteo_client");
    QFile styleFile(":qss/style.qss");
    if (styleFile.open(QIODevice::ReadOnly | QIODevice::Text)) 
    {
        QString styleSheet = QString::fromUtf8(styleFile.readAll());
        setStyleSheet(styleSheet);
        styleFile.close();
    }

    m_fadeAnimation->setDuration(300);  
    m_fadeAnimation->setStartValue(1.0);  
    m_fadeAnimation->setEndValue(0.0);    
    m_fadeAnimation->setEasingCurve(QEasingCurve::OutCubic);  

    connect
    (
        m_fadeAnimation, &QPropertyAnimation::finished, this, [this]()
        {
            hide();  
            createTryIcon(); 
        }
    );


    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QGridLayout* mainLayot = new QGridLayout(centralWidget);
    mainLayot->setContentsMargins(0, 0, 0, 0);
    mainLayot->setSpacing(0);


    topPanel = new TopPanel(centralWidget, qApp);
    middlePanel = new MiddlePanel(centralWidget, qApp);
    QFrame* bot = new QFrame(centralWidget);

    mainLayot->addWidget(topPanel, 0, 0, 1, 1);
    mainLayot->addWidget(middlePanel, 2, 0, 20, 1);
    mainLayot->addWidget(bot, 22, 0, 20, 1);

    QDir resDir(":/");
    connect(topPanel, &TopPanel::closeProgram, this, &MainWindow::closePr);
}


void MainWindow::startFadeOut() 
{
    if (m_fadeAnimation->state() != QPropertyAnimation::Running) 
    {
        m_fadeAnimation->start();
    }
}

void MainWindow::closeEvent(QCloseEvent* event) {
    if (m_trayIcon && m_trayIcon->isVisible()) {
        event->ignore();
        hide();
    } else {
        event->ignore();
        createTryIcon();
        hide();
    }
}

void MainWindow::createTryIcon() 
{
    if (!m_trayIcon) 
    {
        m_trayIcon = new QSystemTrayIcon(this);
        m_trayIcon->setIcon(QIcon(":/img/nimbus.png"));

        QMenu* trayMenu = new QMenu(this);
        trayMenu->addAction(QStringLiteral("Развернуть"), this, [this]() {
            showNormal();
            setWindowOpacity(0.0);  // Начало анимации (полностью прозрачное)
            QPropertyAnimation* fadeIn = new QPropertyAnimation(this, "windowOpacity");
            fadeIn->setDuration(300);
            fadeIn->setStartValue(0.0);
            fadeIn->setEndValue(1.0);
            fadeIn->setEasingCurve(QEasingCurve::OutCubic);
            fadeIn->start(QPropertyAnimation::DeleteWhenStopped);  // Автоудаление
            removeTrayIcon();
            });

        trayMenu->addAction(QStringLiteral("Закрыть"), qApp, &QApplication::quit);
        m_trayIcon->setContextMenu(trayMenu);
        m_trayIcon->show();

        connect(m_trayIcon, &QSystemTrayIcon::activated, this, [this](QSystemTrayIcon::ActivationReason reason) 
            {
            if (reason == QSystemTrayIcon::DoubleClick) 
            {
                showNormal();
                // Анимация появления при двойном клике
                setWindowOpacity(0.0);
                QPropertyAnimation* fadeIn = new QPropertyAnimation(this, "windowOpacity");
                fadeIn->setDuration(300);
                fadeIn->setStartValue(0.0);
                fadeIn->setEndValue(1.0);
                fadeIn->start(QPropertyAnimation::DeleteWhenStopped);
                removeTrayIcon();
            }
        });
    }
}

void MainWindow::removeTrayIcon() 
{
    if (m_trayIcon) 
    {
        m_trayIcon->hide();
        m_trayIcon->deleteLater();
        m_trayIcon = nullptr;
    }
}


void MainWindow::update_values(double t, double w, double p) 
{
    this->middlePanel->update_values(t, w, p);
}

void MainWindow::closePr(){
    emit closeProgram();
}
