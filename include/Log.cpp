#include "Log.h"

template class Log<int>;

template <class T> const char Log<T>::asLogLevel[eAll][6] = {
            "\0",
            "FATAL",
            "ERROR",
            "WARN",
            "INFO",
            "TRACE",
            "ALL"
        };

/**
 * setLogLevel
 *
 * @brief Set the log level (1-7) of the logger
 *
 * @param ui_level unsigned 8-bit integer that has log level
 *                 possible values are:
 *                 1 - None: log nothing
 *                 2 - Fatal: Log grave errors to output
 *                 3 - Error: Log errors to output
 *                 4 - Warn: Log warnings to output
 *                 5 - Info: Log miscellaneous information to output
 *                 6 - Trace: Log traceback information to the output
 *                 7 - All: Log everything else to the output
 */
template <class T> void Log<T>::setLogLevel(uint8_t ui_level)
{
    if (ui_level < eNone && ui_level > eAll)
    {
        // throw an exception
        this->ui_log_level = eNone;
    }
    else
    {
        this->ui_log_level = ui_level;
    }
}

/**
 * getLogLevel
 *
 * @brief get the currently configured log level (1-7) of the logger
 *
 * @return the currently configured log level. Possible values are:
 *                 1 - None: log nothing
 *                 2 - Fatal: Log grave errors to output
 *                 3 - Error: Log errors to output
 *                 4 - Warn: Log warnings to output
 *                 5 - Info: Log miscellaneous information to output
 *                 6 - Trace: Log traceback information to the output
 *                 7 - All: Log everything else to the output
 */
template <class T> uint8_t Log<T>::getLogLevel(void)
{
    return this->ui_log_level;
}

/**
 * log
 *
 * @brief conditionally log data to output based on log level
 *
 * @param data information to log to the output.
 */
template <class T> template <class Tdata> void Log<T>::log(typename Tdata data, uint8_t level)
{
    this->t_output_port->write(data);
}

/* CONSTRUCTOR */
template <class T> Log<T>::Log(void *_output_port)
{
    this->t_output_port = _output_port;
    // TODO: configure a serial port for use
    // if arduino use hardware serial
    // if _avr_ configure serial port for output at 9600 baud
}
