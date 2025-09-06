#include "mainWindow/mainWindow.h"
#include "com_port/com_port.h"
#include <QApplication>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    ComPort comPort;

    MainWindow window;

    // Создаем объект порта в основном потоке

    QObject::connect(&comPort, &ComPort::dataReceived, &window, [&window](const QString& data) {
        qDebug() << "data:" << data;

        std::string strData = data.toStdString();


        try {
            // Парсим строку в JSON-объект
            json jsdata = json::parse(strData);

            // Извлекаем значения
            double celsius = jsdata["temperature"];
            double val = jsdata["val"];
            double pressure = jsdata["pressure"];
            val *= 0.0546875;

            // Выводим результат
            std::cout << "T: " << celsius << " °C\n"
                << "W: " << val << "mps\n"
                << "P: " << pressure << " Hpa\n";
            window.update_values(celsius, val, pressure);
        }
        catch (const json::parse_error& e) {
            std::cerr << "Ошибка парсинга JSON: " << e.what() << std::endl;
        }
        });

    QObject::connect(&window, &MainWindow::closeProgram, &comPort, [&comPort]() 
        {
            comPort.stop();
        });

    comPort.startReading();  // Запускаем чтение
    window.show();
    return a.exec();
}