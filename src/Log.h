#ifndef _LOG_HH_
#define _LOG_HH_

#include <cstddef>
#include <cstdint>

template <class T>
class Log
{
    public:
        /* CONSTRUCTOR */
        Log(T *_output_port);

        /**
         * log
         *
         * @brief conditionally log data to output based on log level
         *
         * @param data information to log to the output.
         */
        template <class Tdata> void log(Tdata data, uint8_t level);

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
        void setLogLevel(uint8_t);

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
        uint8_t getLogLevel();

        // enum to set log level
        enum eLogLevel
        {
            kNone,
            kFatal,
            kError,
            kWarn,
            kInfo,
            kTrace,
            kAll,

            kLogLevels
        };

        // enum for communication type
        enum eCommType
        {
            kSerial,
            kSPI,
            kI2C,
        };
    private:
        // log error level
        uint8_t ui_config_log_level;

        // config ansi support
        uint8_t ui_config_ansi;

        // length of the log level string
        static const uint8_t ui_log_level_string_length = 6;
        
        // string to go with 
        static const char as_log_level[kLogLevels][ui_log_level_string_length];

        /**
         * as_log_level_color
         *
         * @brief a 3 digit corresponding to the ANSI code to format text
         */
        static const char as_log_level_color[kLogLevels][4];

//        /**
//         *
//         *
//         * @brief function to write ANSI format
//         *
//         * @param code ANSI code to write to output
//         * 
//         * @return a c-string containing ANSI format
//         */
//        char * generateANSIFormat(char * buf, )
        // pointer output object
        // this output object should
        // have a function write that
        // writes a single byte of 
        // information. This should
        // default to the first serial port
        // available
         T *t_output_port;
};

template <class T> const uint8_t Log<T>::ui_log_level_string_length;
template <class T> const char Log<T>::as_log_level[kLogLevels][ui_log_level_string_length] = 
{
    "\0",
    "FATAL",
    "ERROR",
    "WARN",
    "INFO",
    "TRACE",
    "ALL"
};
// TODO: add support for configuring these values
template <class T> const char Log<T>::as_log_level_color[kLogLevels][4] = 
{
    "\0",
    "041",
    "031",
    "093",
    "090",
    "096",
    "001"
};
template <class T> void Log<T>::setLogLevel(uint8_t ui_level)
{
    if (ui_level < kNone && ui_level > kLogLevels)
    {
        // throw an exception
        this->ui_config_log_level = kNone;
    }
    else
    {
        this->ui_config_log_level = ui_level;
    }
}

template <class T> uint8_t Log<T>::getLogLevel(void)
{
    return this->ui_log_level;
}

template <class T> template <class Tdata> void Log<T>::log(Tdata data, uint8_t level)
{
    // if requested log level is greater than the configured level dont log
    if (level > ui_config_log_level)
        return;

    // add formatted prefix to output
    if (level != kNone && ui_config_ansi)
    {
        // begin the ANSI escape sequence
        this->t_output_port->write('\033');
        this->t_output_port->write('[');

        // add format prefixes
        this->t_output_port->write(';');
        for (int i=0; as_log_level_color[level][i] != 0x00 && i<3; i++)
            this->t_output_port->write(as_log_level_color[level][i]);

        // if the log level is anything but all add color
        this->t_output_port->write(';');
        for (int i=0; level!=kAll && as_log_level_color[level][i]!=0x00 && i<3; i++)
            this->t_output_port->write(as_log_level_color[level][i]);

        // end the ANSI escape sequence
        this->t_output_port->write('m');

        // write the log level to the output port
        for (int i=0; level!=kNone && as_log_level[level][i]!=0x0 && i<ui_log_level_string_length; i++)
            this->t_output_port->write(as_log_level[level][i] );
        this->t_output_port->write(':');

        // reset output to standard ANSI escape sequence
        this->t_output_port->write('\033');
        this->t_output_port->write('[');
        this->t_output_port->write('m');

        // add a space between debug level
        this->t_output_port->write('\t');
    }
    // TODO: add support for actually writing and interpreting data based on type
    this->t_output_port->write(data);

    // add a new line at the end
    this->t_output_port->write('\r');
    this->t_output_port->write('\n');
}

/* CONSTRUCTOR */
template <class T> Log<T>::Log(T *_output_port)
{
    this->t_output_port = _output_port;
    // TODO: configure a serial port for use
    // if arduino use hardware serial
    // if _avr_ configure serial port for output at 9600 baud
}
#endif
