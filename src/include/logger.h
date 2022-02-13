#pragma once

#include <iostream>
#include <fstream>

struct Logger {
    static void createLogger(const std::string& logFilename);
    static void log(const std::string& data);
    static void deleteLogger();

private:
    Logger(const Logger& other);
    Logger& operator=(const Logger& other);

    explicit Logger(const std::string& logFilename);
    ~Logger();

    std::fstream logFile;
    static Logger* logger;
};