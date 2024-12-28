#ifndef CLIMATE_H
#define CLIMATE_H

#include <string>
#include <vector>
#include <map>
#include "Constants.h"

class Climate {
public:
    // Generate daily temperature for a given climate zone and season
    static float generateDailyTemperature(const std::string& zone, const std::string& season);

    // Get the climate zone based on latitude
    static std::string getClimateZone(float latitude);

    // Generate precipitation data for the day
    static float generateDailyPrecipitation(const std::string& zone, const std::string& season);

    // Simulate weather events (e.g., storms, heatwaves)
    static std::string simulateWeatherEvent(const std::string& season, const std::string& zone);

private:
    // Define temperature and precipitation ranges for each climate zone
    static const std::map<std::string, std::pair<float, float>> TEMPERATURE_ZONES;
    static const std::map<std::string, float> PRECIPITATION_ZONES;
};

#endif // CLIMATE_H
