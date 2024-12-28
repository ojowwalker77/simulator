#include "LogManager.h"
#include <fstream>
#include <filesystem>
#include <stdexcept>

void LogManager::logEvent(const std::string& category, const nlohmann::json& event) {
    std::string logDirectory = "logs";
    std::string logFile = logDirectory + "/" + category + ".json";

    // Ensure the "logs" directory exists
    if (!std::filesystem::exists(logDirectory)) {
        std::filesystem::create_directory(logDirectory);
    }

    // Append event to log file
    std::ofstream file(logFile, std::ios::app);
    if (file.is_open()) {
        file << event.dump() << std::endl;
        file.close();
    } else {
        throw std::runtime_error("Failed to open log file: " + logFile);
    }
}
