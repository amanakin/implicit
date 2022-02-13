// logger.cc

#include <stdexcept>
#include <logger.h>
#include <utils.h>

Logger* Logger::logger = nullptr;

Logger::Logger(const std::string& name) 
    : logFile(name, std::fstream::out)
{
    if (!logFile.is_open()) {
        throw std::logic_error("can't open file");
    }
}

Logger::~Logger() {
    logFile.close();
}

void Logger::createLogger(const std::string& logFilename) {
    if (logger != nullptr) {
        delete logger;
    }

    logger = new Logger(logFilename);
}

void Logger::log(const std::string& data) {
    if (logger != nullptr) {
        logger->logFile << currentDateTime() << ": " << data << '\n';
    }
}

void Logger::deleteLogger() {
    if (logger != nullptr) {
        delete logger;
        logger = nullptr;
    }
}