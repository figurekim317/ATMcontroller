#include "Utility.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

// Logs a message with an optional log level, optionally writes to a log file.
void logMessage(const std::string& message, const std::string& level, const std::string& logFile) {
    // Get the current time
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm = *std::localtime(&time_t_now);

    // Format the time as [YYYY-MM-DD HH:MM:SS]
    std::ostringstream timeStream;
    timeStream << "[" << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S") << "]";

    // Construct the log message
    std::ostringstream logStream;
    logStream << timeStream.str() << " [" << level << "]: " << message;

    // Print to console
    std::cout << logStream.str() << std::endl;

    // Optionally write to a log file
    if (!logFile.empty()) {
        std::ofstream file(logFile, std::ios::app); // Append mode
        if (file.is_open()) {
            file << logStream.str() << std::endl;
            file.close();
        } else {
            std::cerr << "[ERROR]: Unable to open log file: " << logFile << std::endl;
        }
    }
}
