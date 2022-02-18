// logger.cc

#include <stdexcept>
#include <logger.h>
#include <utils.h>

Logger* Logger::Logger_ = nullptr;

Logger::Logger(const std::string& name) 
    : logFile_(name, std::fstream::out),
    isTime_(true)
{
    if (!logFile_.is_open()) {
        throw std::logic_error("can't open file");
    }

    logFile_ << "<pre>\n";
}

Logger::~Logger() {
    logFile_ << "</pre>\n";
    logFile_.close();
}

void Logger::createLogger(const std::string& logFilename) {
    if (Logger_ != nullptr) {
        delete Logger_;
    }

    Logger_ = new Logger(logFilename);
}

void Logger::log(const std::string& data) {
    if (Logger_ != nullptr) {
        if (Logger_->isTime_) {
            Logger_->logFile_ << CurrentDateTime() << ": "; 
        }
        Logger_->logFile_ << data << '\n';
    }
}

void Logger::deleteLogger() {
    if (Logger_ != nullptr) {
        delete Logger_;
        Logger_ = nullptr;
    }
}

void Logger::setTimeCtrl(bool isTime) {
    Logger_->isTime_ = isTime;
}