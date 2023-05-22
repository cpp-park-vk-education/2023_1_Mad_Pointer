#pragma once

#include "file_sink.h"

#include <filesystem>
#include <iostream>

namespace Logs {
    class Logger {
    public:
        enum Level { INFO_LEVEL, WARN_LEVEL, ERROR_LEVEL };

        static inline std::array<std::string, Level::ERROR_LEVEL + 1u> LevelStr = {"INFO", "WARN", "ERROR"};

    public:
        Logger(const std::string& filename) : m_sink(filename) {}

        void log(Level level, const char* source, const std::string& message) {
            const std::string formattedMessage = "[" + LevelStr[level] + "] - " + source + " - " + message + "\n";
            m_sink.write(formattedMessage);
        }

    private:
        FileSink m_sink;
    };
}  // namespace Logs

inline Logs::Logger& getGlobalLogger() {
    static Logs::Logger logger(std::filesystem::current_path().generic_string() + "data.log");
    return logger;
}

#define STR_(x) #x
#define STR(x) STR_(x)

#define LOG_INFO(message) getGlobalLogger().log(Logs::Logger::Level::INFO_LEVEL, __FILE__ ":" STR(__LINE__), (message))
#define LOG_WARN(message) getGlobalLogger().log(Logs::Logger::Level::WARN_LEVEL, __FILE__ ":" STR(__LINE__), (message))
#define LOG_ERROR(message) getGlobalLogger().log(Logs::Logger::Level::ERROR_LEVEL, __FILE__ ":" STR(__LINE__), (message))
