/*
** EPITECH PROJECT, 2025
** LoggerLib
** File description:
** Logger
**
** Created by Martin BONTE
** This File is part of a custom independent logging library written entirely by me.
** All logic, design, and implementation choices are my own work.
*/


#ifndef LOGGER_HPP
    #define LOGGER_HPP

    #include <fstream>
    #include <iostream>
    #include <filesystem>

namespace debug {
    class Logger {
        public:
            enum class Output {
                Console,
                File,
                Both
            };
            
            static Logger& getInstance();

            static void clearLogFile();
            static bool infoLog(const std::string& message, Output output = Output::File, bool date = false);
            static bool debugLog(const std::string& message, Output output = Output::File, bool date = false);
            static bool warningLog(const std::string& message, Output output = Output::File, bool date = false);
            
            static Output getDefaultOutput();

            static void setDefaultOutput(Output output);
        private:
            Logger();
            ~Logger();
            Logger(const Logger&) = delete;
            Logger& operator=(const Logger&) = delete;

            void logCurrentTime() const;
            std::string logCurrentHour() const;

            void setLogFile(const std::string& filePath);

            std::string getLogFile() const;

            bool createLogFile();
            bool logFileExists() const;
            bool logFileIsWritable() const;
            bool log(const std::string& message);

            Output _output;
            std::string _logFilePath;
    };
}

/************************************************************
**           >>>> STATIC  MEMBER FUNCTIONS   <<<<          **
************************************************************/


inline constexpr debug::Logger::Output File = debug::Logger::Output::File;
inline constexpr debug::Logger::Output Both = debug::Logger::Output::Both;
inline constexpr debug::Logger::Output Console = debug::Logger::Output::Console;

/**
 * @brief Log an info message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (Console, File, or Both).
 * @param date (optional) Whether to include the current date in the log message.
 * @return true if the log was successful, false otherwise.
 */
inline void InfoLog(const std::string& msg, debug::Logger::Output output = debug::Logger::Output::File, bool date = false)
{
    debug::Logger::getInstance().infoLog(msg, output, date);
}

/**
 * @brief Log a message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (Console, File, or Both).
 * @param date (optional) Whether to include the current date in the log message.
 * @return true if the log was successful, false otherwise.
 */
inline void DebugLog(const std::string& msg, debug::Logger::Output output = debug::Logger::Output::File, bool date = false)
{
    debug::Logger::getInstance().debugLog(msg, output, date);
}

/**
 * @brief Log a warning message with the current time.
 *
 * This function logs the message with the current time.
 * @param message The message to log.
 * @param output (optional) The output destination for the log (Console, File, or Both).
 * @param date (optional) Whether to include the current date in the log message.
 * @return true if the log was successful, false otherwise.
 */
inline void WarningLog(const std::string& msg, debug::Logger::Output output = debug::Logger::Output::File, bool date = false)
{
    debug::Logger::getInstance().warningLog(msg, output, date);
}

/**
 * @brief Clear the log File.
 *
 * This function clears the log File by truncating it.
 */
inline static void clearLogFile()
{
    debug::Logger::clearLogFile();
}

/**
 * @brief Set the default output for the logger.
 *
 * This function sets the default output for the logger.
 * @param output The output destination for the log (Console, File, or Both).
 */
inline static void setDefaultOutput(debug::Logger::Output output)
{
    debug::Logger::setDefaultOutput(output);
}

/**
 * @brief Get the default output for the logger.
 *
 * This function returns the default output for the logger.
 * @return The default output destination for the log (Console, File, or Both).
 */
inline static debug::Logger::Output getDefaultOutput()
{
    return debug::Logger::getDefaultOutput();
}

namespace Debug
{
    /**
     * @brief Log an info message with the current time.
     *
     * This function logs the message with the current time.
     * @param message The message to log.
     * @param output (optional) The output destination for the log (Console, File, or Both).
     * @param date (optional) Whether to include the current date in the log message.
     * @return true if the log was successful, false otherwise.
     */
    inline void InfoLog(const std::string& msg, debug::Logger::Output output = File, bool date = false)
    {
        debug::Logger::getInstance().infoLog(msg, output, date);
    }

    /**
     * @brief Log a debug message with the current time.
     *
     * This function logs the message with the current time.
     * @param message The message to log.
     * @param output (optional) The output destination for the log (Console, File, or Both).
     * @param date (optional) Whether to include the current date in the log message.
     * @return true if the log was successful, false otherwise.
     */
    inline void DebugLog(const std::string& msg, debug::Logger::Output output = File, bool date = false)
    {
        debug::Logger::getInstance().debugLog(msg, output, date);
    }

    /**
     * @brief Log a warning message with the current time.
     *
     * This function logs the message with the current time.
     * @param message The message to log.
     * @param output (optional) The output destination for the log (Console, File, or Both).
     * @param date (optional) Whether to include the current date in the log message.
     * @return true if the log was successful, false otherwise.
     */
    inline void WarningLog(const std::string& msg, debug::Logger::Output output = File, bool date = false)
    {
        debug::Logger::getInstance().warningLog(msg, output, date);
    }

    /**
     * @brief Clear the log File.
     *
     * This function clears the log File by truncating it.
     */
    inline void ClearLogFile()
    {
        debug::Logger::clearLogFile();
    }

    /**
     * @brief Set the default output for the logger.
     *
     * This function sets the default output for the logger.
     * @param output The output destination for the log (Console, File, or Both).
     */
    inline void SetOutput(debug::Logger::Output output)
    {
        debug::Logger::setDefaultOutput(output);
    }

    /**
     * @brief Get the default output for the logger.
     *
     * This function returns the default output for the logger.
     * @return The default output destination for the log (Console, File, or Both).
     */
    inline debug::Logger::Output GetOutput()
    {
        return debug::Logger::getDefaultOutput();
    }
}

#endif