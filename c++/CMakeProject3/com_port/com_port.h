#pragma once
#include <QObject>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>

class ComPort : public QObject {
    Q_OBJECT
public:
    explicit ComPort(QObject* parent = nullptr);
    ~ComPort();

    void startReading();
    void stop();
    std::vector<std::string> get_available_ports();
    std::string readLineFromSerial(std::vector<std::string>& ports_name);

signals:
    void dataReceived(const QString& data); 
    void errorOccurred(const QString& error);

private:
    char buffer[256];
    boost::asio::io_context io;
    boost::asio::serial_port port;
    void handleRead(const boost::system::error_code& ec, size_t bytes_read);
};