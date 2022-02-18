#pragma once

#include <iostream>
#include <fstream>

struct Logger {
    static void createLogger(const std::string& logFilename);
    static void log(const std::string& data);
    static void deleteLogger();
    static void setTimeCtrl(bool isTime);

private:
    Logger(const Logger& other);
    Logger& operator=(const Logger& other);

    explicit Logger(const std::string& logFilename);
    ~Logger();

    std::fstream logFile_;
    bool isTime_;
    static Logger* Logger_;
};