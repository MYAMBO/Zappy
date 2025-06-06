/*
** EPITECH PROJECT, 2025
** Logger
** File description:
** Logger
**
** Created by Martin BONTE
** This file is part of a custom independent logging library written entirely by me.
** All logic, design, and implementation choices are my own work.
*/

#include "Logger.hpp"


/************************************************************
**         >>>>   CONSTRUCTORS DESTRUCTORS    <<<<         **
************************************************************/


debug::Logger::Logger()
    : _logFilePath("debug.log")
{
    createLogFile();
    _output = Output::File;
}

debug::Logger::~Logger()
{
}

debug::Logger& debug::Logger::getInstance()
{
    static Logger instance;
    return instance;
}

/************************************************************
**               >>>>   MEMBER FUNCTIONS   <<<<            **
************************************************************/

void debug::Logger::logCurrentTime() const
{
    std::ofstream os(_logFilePath, std::ios::app);

    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    os << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
}

std::string debug::Logger::logCurrentHour() const
{
    std::ofstream os(_logFilePath, std::ios::app);

    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(localTime, "[%H:%M:%S]");
    return oss.str();
}

bool debug::Logger::logFileExists() const
{
    return std::filesystem::exists(_logFilePath);
}

bool debug::Logger::logFileIsWritable() const
{
    std::error_code ec;
    auto perms = std::filesystem::status(_logFilePath, ec).permissions();

    if (ec) {
        std::cerr << "Erreur : Impossible de vérifier les permissions du fichier : " << ec.message() << std::endl;
        return false;
    }
    return (perms & std::filesystem::perms::owner_write) != std::filesystem::perms::none
        || (perms & std::filesystem::perms::group_write) != std::filesystem::perms::none
        || (perms & std::filesystem::perms::others_write) != std::filesystem::perms::none;
}

bool debug::Logger::createLogFile()
{
    if (logFileExists())
        return true;

    std::ofstream logFile(_logFilePath);

    if (!logFile.is_open()) {
        std::cerr << "Erreur : Impossible de créer le fichier log : " << _logFilePath << std::endl;
        return false;
    }
    logFile.close();
    return true;
}

bool debug::Logger::log(const std::string& message)
{
    if (message.empty()) {
        std::cerr << "Erreur : Message vide fourni au logger" << std::endl;
        return false;
    }
    
    bool fileExists = logFileExists();
    if (!fileExists && !createLogFile()) {
        std::cerr << "Erreur : Impossible de créer le fichier log : " << _logFilePath << std::endl;
        return false;
    }
    if (!logFileIsWritable()) {
        std::cerr << "Erreur : Le fichier " << _logFilePath << " n'est pas accessible en écriture" << std::endl;
        return false;
    }
    
    std::ofstream logFile(_logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier log : " << _logFilePath << std::endl;
        return false;
    }
    
    logFile << message;
    
    logFile.flush();
    logFile.close();
    
    if (logFile.fail())
    std::cerr << "Error : Problème lors de la fermeture du fichier log" << std::endl;
    return true;
}


/************************************************************
**           >>>> STATIC  MEMBER FUNCTIONS   <<<<          **
************************************************************/


bool debug::Logger::infoLog(const std::string& message, debug::Logger::Output output, bool date)
{
    std::string dateStr;
    if (date) {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(localTime, "[%Y-%m-%d %H:%M:%S] ");
        dateStr = oss.str();
    }
    if (output == Console || output == Both) {
        std::cout << dateStr << "[INFO]   " << message << std::endl;
    }
    if (output == File || output == Both) {
        return getInstance().log(dateStr + "[INFO]   " + message + "\n");
    }
    return false;
}

bool debug::Logger::debugLog(const std::string& message, debug::Logger::Output output, bool date)
{
    std::string dateStr;
    if (date) {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(localTime, "[%Y-%m-%d %H:%M:%S] ");
        dateStr = oss.str();
    }
    if (output == Console || output == Both) {
        std::cout << dateStr << "[DEBUG]   " << message << std::endl;
    }
    if (output == File || output == Both) {
        return getInstance().log(dateStr + "[DEBUG]   " + message + "\n");
    }
    return false;
}

bool debug::Logger::warningLog(const std::string& message, debug::Logger::Output output, bool date)
{
    std::string dateStr;
    if (date) {
        std::time_t now = std::time(nullptr);
        std::tm* localTime = std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(localTime, "[%Y-%m-%d %H:%M:%S] ");
        dateStr = oss.str();
    }
    if (output == Console || output == Both) {
        std::cout << dateStr << "[WARNING] " << message << std::endl;
    }
    if (output == File || output == Both) {
        return getInstance().log(dateStr + "[WARNING] " + message + "\n");
    }
    return false;
}

void debug::Logger::clearLogFile()
{
    std::ofstream logFile(getInstance().getLogFile(), std::ios::trunc);

    if (!logFile.is_open()) {
        std::cerr << "Erreur : Impossible de vider le fichier log : " << getInstance().getLogFile() << std::endl;
        return;
    }
    logFile.close();
}

void debug::Logger::setDefaultOutput(Output output)
{
    getInstance()._output = output;
}

debug::Logger::Output debug::Logger::getDefaultOutput()
{
    return getInstance()._output;
}


/************************************************************
**                  >>>>    SETTERS   <<<<                 **
************************************************************/


void debug::Logger::setLogFile(const std::string& filePath)
{
    _logFilePath = filePath;
}


/************************************************************
**               >>>>   GETTERS   <<<<                     **
************************************************************/


std::string debug::Logger::getLogFile() const
{
    return _logFilePath;
}
