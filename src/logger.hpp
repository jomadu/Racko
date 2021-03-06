#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>

class Logger
{
public:
    enum LogLevel
    {
        ERROR,
        WARN,
        INFO,
        DEBUG,
        DEBUG1,
        DEBUG2
    };
    static Logger &instance();
    static void deleteInstance();
    static void logLevel(const LogLevel &log_level);
    static Logger::LogLevel logLevel();
    static void log(const LogLevel &log_level, const std::string &msg);

protected:
    LogLevel log_level_;
    Logger() : log_level_(LogLevel::INFO) {};
    ~Logger(){};

private:
    static Logger *inst_;
};


#define LOG_ERROR(msg) {\
    auto &logger = Logger::instance();\
    logger.log(Logger::LogLevel::ERROR, msg);\
}
#define LOG_WARN(msg) {\
    auto &logger = Logger::instance();\
    logger.log(Logger::LogLevel::WARN, msg);\
}
#define LOG_INFO(msg) {\
    auto &logger = Logger::instance();\
    logger.log(Logger::LogLevel::INFO, msg);\
}

#endif // LOGGER_HPP
