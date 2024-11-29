#ifndef UTILITY_H
#define UTILITY_H

#include <string>

// Logs a message with an optional log level, optionally writes to a log file.
void logMessage(const std::string& message, const std::string& level = "INFO", const std::string& logFile = "");

#endif // UTILITY_H
