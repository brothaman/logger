#include "Log.h"

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
template <typename T> void Log<T>::setLogLevel(uint8_t ui_level)
{
    this->ui_log_level = ui_level;
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
template <typename T> void Log<T>::getLogLevel(void)
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
template <typename T> template <typename Tdata> void Log<T>::log(Tdata data, uint8_t level)
{
    
    tOutputPort->write(data);
}
