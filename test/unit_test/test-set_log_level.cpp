#include <iostream>
#include "../../include/Log.h"

class SerialPort
{
    // fake serial port that will write to standard out
    public:
        SerialPort() {};
        ~SerialPort() {};
        template <class T>
        void write(T data);
};

template <class T> void SerialPort::write(T data)
{
    std::cout << data;
}

int main()
{
    SerialPort *serial_port = new SerialPort();
    Log<SerialPort> serial_logger = Log<SerialPort>(serial_port);
    serial_logger.setLogLevel(Log<SerialPort>::eLogLevel::kAll);
    serial_logger.log("Hello world", Log<SerialPort>::eLogLevel::kFatal);
    delete serial_port;
    return 0;
}
