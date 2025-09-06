#include "com_port.h"
#include <QDebug>

ComPort::ComPort(QObject* parent)
    : QObject(parent),
        // Инициализируем член класса
      port(io)
{
    
    char buffer[256];
}

ComPort::~ComPort() {
    if(port.is_open()) {
        port.close();
    }
    io.stop();  // Останавливаем io_context
}

void ComPort::startReading() {
    bool flag_working_searg = true;
    while (flag_working_searg)
    {
        std::vector<std::string> ports = this->get_available_ports();
        std::string port_name = readLineFromSerial(ports);
        if (port_name != "") {
            port.open(port_name);
            port.set_option(boost::asio::serial_port_base::baud_rate(9600));
            port.set_option(boost::asio::serial_port_base::character_size(8));
            port.set_option(boost::asio::serial_port_base::stop_bits(
                boost::asio::serial_port_base::stop_bits::one));
            port.set_option(boost::asio::serial_port_base::parity(
                boost::asio::serial_port_base::parity::none));

            // Запускаем асинхронное чтение
            port.async_read_some(
                boost::asio::buffer(buffer),
                [this](auto... args) { this->handleRead(args...); }
            );

            // Запускаем io_context в отдельном потоке
            std::thread([this]() { io.run(); }).detach();
        }
    }

    }
    
void ComPort::handleRead(const boost::system::error_code& ec, size_t bytes_read) {
    if (!ec) {
        QString data = QString::fromStdString(std::string(buffer, bytes_read));
        emit dataReceived(data);  // Отправляем данные в основной поток

        //Читаем следующие данные
        port.async_read_some(
            boost::asio::buffer(buffer),
            [this](auto... args) { this->handleRead(args...); }
        );
    }
    else {
        emit errorOccurred(QString::fromStdString(ec.message()));
    }
}




std::vector<std::string> ComPort::get_available_ports() {
    std::vector<std::string> ports;

    // Проверяем стандартные COM-порты (COM1-COM256)
    for (int i = 1; i <= 256; ++i) {
        std::string port_name = "COM" + std::to_string(i);

        // Пытаемся открыть порт
        HANDLE hPort = CreateFileA(
            port_name.c_str(),
            GENERIC_READ | GENERIC_WRITE,
            0,
            NULL,
            OPEN_EXISTING,
            0,
            NULL);

        if (hPort != INVALID_HANDLE_VALUE) {
            std::cout << port_name << std::endl;
            ports.push_back(port_name);
            CloseHandle(hPort);
        }
    }

    return ports;
}

std::string ComPort:: readLineFromSerial(std::vector<std::string>& ports_name)
{

    for (auto& port_name : ports_name) {
        unsigned int timeout_ms = 2000;
        std::cout << "chec port " << port_name << std::endl;

        try {
            boost::asio::io_context io;
            boost::asio::serial_port port(io);
            boost::asio::deadline_timer timer(io);
            bool timeout_expired = false;
            boost::system::error_code ec;
            bool operation_completed = false;
            boost::asio::streambuf buffer;

            // 1. Открываем порт (с проверкой доступности)
            port.open(port_name, ec);
            if (ec) {
                std::cout << "port " << port_name << " not" << std::endl;
                continue;
            }

            // 2. Настраиваем параметры порта
            port.set_option(boost::asio::serial_port_base::baud_rate(9600));
            // ... остальные настройки порта

            // 3. Очищаем буфер
            boost::asio::read(port, buffer, boost::asio::transfer_at_least(0), ec);
            buffer.consume(buffer.size());

            // 4. Отправляем запрос с таймаутом
            timer.expires_from_now(boost::posix_time::milliseconds(timeout_ms));
            timer.async_wait([&](const boost::system::error_code& timer_ec) {
                if (!timer_ec && !operation_completed) {
                    timeout_expired = true;
                    port.cancel();
                }
                });

            // 5. Асинхронная запись и чтение
            boost::asio::async_write(port, boost::asio::buffer("WHO_ARE_YOU\n"),
                [&](const boost::system::error_code& write_ec, size_t) {
                    if (timeout_expired) return;

                    if (write_ec) {
                        ec = write_ec;
                        operation_completed = true;
                        timer.cancel();
                        return;
                    }

                    boost::asio::async_read_until(port, buffer, '\n',
                        [&](const boost::system::error_code& read_ec, size_t) {
                            if (!timeout_expired) {
                                ec = read_ec;
                                operation_completed = true;
                                timer.cancel();
                            }
                        });
                });

            // 6. Ожидаем завершения операций
            while (!operation_completed && !timeout_expired) {
                io.run_one();
            }

            // 7. Обрабатываем результат
            if (timeout_expired) {
                std::cout << "time_out " << port_name << ", next" << std::endl;
                port.close();
                continue;
            }

            if (ec) {
                std::cout << "crash " << port_name << ": " << ec.message() << std::endl;
                port.close();
                continue;
            }

            // 8. Проверяем ответ
            std::istream is(&buffer);
            std::string line;
            std::getline(is, line);

            port.close();
            std::cout << line << std::endl;
            if (line.find("i im meteo") != std::string::npos) {
                std::cout << "good port: " << port_name << std::endl;
                return port_name;
            }
            else {
                std::cout << "otvet ne good " << port_name << ", next" << std::endl;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "suka " << port_name << ": " << e.what() << std::endl;
            continue;
        }
    }

    std::cout << "((" << std::endl;
    return "";
}

void ComPort::stop() {
    io.stop();

    // 2. Закрываем порт (если открыт)
    if (port.is_open()) {
        boost::system::error_code ec;
        port.close();  // Игнорируем ошибки при закрытии
    }
}

