#ifndef _LOG_HH_
#define _LOG_HH_

template <typename T>
class Log
{
    public:
        // function to log data
        template <typename T>
        size_t log(T data, uint8_t level);

        // set error level
        void setLogLevel(uint8_t);

        // get error level
        uint8_t getLogLevel();

        // enum to set log level
        enum LogLevel
        {
            eNone=1,
            eFatal,
            eError,
            eWarn,
            eInfo,
            eTrace,
            eAll
        };

        // string to go with 
        static const char asLogLevel[eAll][] = {
            "\0",
            "FATAL",
            "ERROR",
            "WARN",
            "INFO",
            "TRACE",
            "ALL"
        };

        // enum for communication type
        enum CommType
        {
            kSerial,
            kSPI,
            kI2C,
        };
    private:
        // log error level
        uint8_t ui_log_level;
        
        // pointer output object
        // this output object should
        // have a function write that
        // writes a single byte of 
        // information. This should
        // default to the first serial port
        // available
        T *tOutputPort;
};
#endif
