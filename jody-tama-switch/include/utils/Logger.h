#pragma once

#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    DEBUG,
    INFO,
    WARNING,
    ERROR,
    CRITICAL
};

class Logger {
public:
    static void initialize(const std::string& filename = "jody-tama.log");
    static void shutdown();
    
    // Logging methods
    static void debug(const std::string& message);
    static void info(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);
    static void critical(const std::string& message);
    
    // Log with level
    static void log(LogLevel level, const std::string& message);
    
    // Configuration
    static void setLogLevel(LogLevel level);
    static void setLogToFile(bool enabled);
    static void setLogToConsole(bool enabled);
    
private:
    static Logger* instance;
    
    std::ofstream logFile;
    std::mutex logMutex;
    LogLevel currentLevel;
    bool logToFile;
    bool logToConsole;
    
    Logger();
    ~Logger();
    
    void writeLog(LogLevel level, const std::string& message);
    std::string getTimestamp();
    std::string getLevelString(LogLevel level);
    std::string formatMessage(LogLevel level, const std::string& message);
};