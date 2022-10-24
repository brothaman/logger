#include <iostream>
#include "../../src/Log.h"

class SerialPort
{
    // fake serial port that will write to standard output
    public:
        SerialPort() {};
        ~SerialPort() {};
        template <class T> void write(T data);
};

template <class T> void SerialPort::write(T data)
{
    std::cout << data;
}

using LogLevel = Log<SerialPort>::eLogLevel;

int main()
{
    SerialPort * serial_port = new SerialPort();
    Log<SerialPort> * serial_logger = new Log<SerialPort>(serial_port);
    serial_logger->setLogLevel(LogLevel::kTrace);
    serial_logger->log("Hello world ", LogLevel::kTrace);
    serial_logger->log("I am adding this on\n", LogLevel::kTrace);
    serial_logger->log("This should begin on a new line ", LogLevel::kTrace);
    serial_logger->logln("and im adding this one", LogLevel::kTrace);
    serial_logger->logln("This should be on a line of its own", LogLevel::kTrace);
    delete serial_port;
}
