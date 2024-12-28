#include <cstdlib> // For rand()
#include <ctime>   // For srand()
#include <cmath>   // For uniform distribution
#include <random>



#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    // Universal Constants
    constexpr float GRAVITY = 9.81f; // m/s^2
    constexpr float AIR_DENSITY = 1.225f; // kg/m^3
    constexpr float WATER_HEAT_CAPACITY = 4184.0f; // J/(kg·K)

    // Biological Constants
    constexpr float PHOTOSYNTHESIS_RATE = 0.08f;
    constexpr float RESPIRATION_RATE = 0.02f;

    // Simulation Parameters
    constexpr float HUMIDITY_DIFFUSION_RATE = 0.01f;
    constexpr float TEMPERATURE_DIFFUSION_RATE = 0.005f;

    constexpr float HOURS_IN_A_DAY = 24.0f;
    constexpr int DAYS_IN_A_MONTH = 30;
    constexpr int MONTHS_IN_A_YEAR = 12;
    constexpr float HOURS_IN_A_MONTH = DAYS_IN_A_MONTH * HOURS_IN_A_DAY;
    constexpr float HOURS_IN_A_YEAR = MONTHS_IN_A_YEAR * HOURS_IN_A_MONTH;

    const std::string SEASONS[] = {"Winter", "Spring", "Summer", "Autumn"};
    const int SEASON_STARTS[] = {1, 4, 7, 10}; // Starting months: Jan, Apr, Jul, Oct
    constexpr float TEMPERATURE_RANGES[] = { -10.0f, 0.0f, 10.0f, 10.0f }; // Winter to Autumn

    // Climate Zones
    const std::string CLIMATE_ZONES[] = { "Polar", "Temperate", "Tropical" };
    constexpr float POLAR_TEMPERATURE[] = { -30.0f, -20.0f, -15.0f, -20.0f };
    constexpr float TROPICAL_TEMPERATURE[] = { 20.0f, 25.0f, 30.0f, 25.0f };
    constexpr float POLAR_PRECIPITATION = 0.5f;
    constexpr float TROPICAL_PRECIPITATION = 5.0f;
}

namespace Formulas {


inline float generateRandomFloat(float min, float max) {
    static std::random_device rd;  // Random device for seeding
    static std::mt19937 gen(rd()); // Mersenne Twister generator
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}

    inline float calculateSeasonalTemperature(float baseTemp, float timeOfYear, float seasonalVariation) {
        float transitionFactor = sin((timeOfYear / Constants::MONTHS_IN_A_YEAR) * M_PI * 2.0f);
        return baseTemp + (transitionFactor * seasonalVariation);
    }

    inline float adjustPrecipitationForSeason(float basePrecipitation, const std::string& season) {
        if (season == "Spring" || season == "Autumn") {
            return basePrecipitation * 2.2f + Formulas::generateRandomFloat(-0.5f, 0.5f);
        } else if (season == "Winter") {
            return basePrecipitation * 1.7f + Formulas::generateRandomFloat(-0.5f, 0.5f);
        } else {
            return basePrecipitation + Formulas::generateRandomFloat(-0.3f, 0.3f);
        }
    }

    inline std::string determineWeatherEvent(float temperature, float precipitation, const std::string& season, const std::string& climateZone) {
        // Rare weather events
        float randomChance = Formulas::generateRandomFloat(0.0f, 1.0f);
        if (climateZone == "Polar" && season == "Winter" && randomChance < 0.1f) {
            return "Snowstorm";
        } else if (climateZone == "Tropical" && season == "Summer" && randomChance < 0.5f) {
            return "Hurricane";
        } else if (season == "Summer" && randomChance < 0.02f && climateZone == "Temperate") {
            return "Drought";
        }

        // Common weather events
        if (precipitation > 2.0f) {
            if (temperature <= 0.0f) {
                return "Snow";
            } else if (temperature > 0.0f && temperature < 25.0f) {
                return "Rain";
            }
        } else if (precipitation > 1.0f && randomChance < 0.2f) {
            return "Cloudy";
        }

        // Default to clear skies
        return "Clear Skies";
    }

    inline float applyClimateAnomaly(float baseTemp, int year) {
        // Reduce anomaly impact to ±1.0°C
        if (year % 5 == 0) {
            return baseTemp - 1.0f;
        } else if (year % 7 == 0) {
            return baseTemp + 1.0f;
        }
        return baseTemp;
    }

}
#endif // CONSTANTS_H
