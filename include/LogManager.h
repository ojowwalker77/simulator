#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <string>
#include <nlohmann/json.hpp>

class LogManager {
public:
    static void logEvent(const std::string& category, const nlohmann::json& event);
};

#endif // LOGMANAGER_H
