#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <random>
#include <nlohmann/json.hpp>
#include "Constants.h"
#include "LogManager.h"
#include "Climate.h"

// Struct to simulate plant states in hexagons
struct PlantState {
    bool hasGrass;
    int grassGrowthStage;

    PlantState() : hasGrass(false), grassGrowthStage(0) {}
};

// Simulate the growth and lifecycle of plants
void simulatePlants(std::vector<PlantState>& plantStates, const std::string& weatherEvent) {
    for (auto& plant : plantStates) {
        if (weatherEvent == "Snow") {
            // Grass dies under snow
            plant.hasGrass = false;
            plant.grassGrowthStage = 0;
        } else if (plant.hasGrass && plant.grassGrowthStage < 5) {
            // Grass grows up to stage 5
            plant.grassGrowthStage++;
        } else if (!plant.hasGrass && weatherEvent != "Snow") {
            // Grass starts growing in non-snowy conditions
            plant.hasGrass = true;
            plant.grassGrowthStage = 1;
        }
    }
}

int main() {
    using namespace Constants;

    const int YEARS_TO_SIMULATE = 50;
    const float timeStep = 1.0f;
    const float latitude = 45.0f;

    std::srand(std::time(nullptr)); // Seed random number generator

    // Initialize plant states for each hexagon (assuming 100 hexagons for simplicity)
    const int numHexagons = 100;
    std::vector<PlantState> plantStates(numHexagons);

    for (int year = 1; year <= YEARS_TO_SIMULATE; ++year) {
        for (float timeOfYear = 0.0f; timeOfYear < MONTHS_IN_A_YEAR; timeOfYear += timeStep) {
            int month = static_cast<int>(timeOfYear) % MONTHS_IN_A_YEAR + 1;

            std::string season = SEASONS[(month - 1) / 3];
            std::string climateZone = Climate::getClimateZone(latitude);

            std::vector<float> dailyTemperatures(DAYS_IN_A_MONTH);
            std::vector<float> dailyPrecipitation(DAYS_IN_A_MONTH);

            for (int day = 0; day < DAYS_IN_A_MONTH; ++day) {
                dailyTemperatures[day] = Climate::generateDailyTemperature(season, climateZone);
                dailyPrecipitation[day] = Climate::generateDailyPrecipitation(season, climateZone);
            }

            float avgTemperature = std::accumulate(dailyTemperatures.begin(), dailyTemperatures.end(), 0.0f) / DAYS_IN_A_MONTH;
            float avgPrecipitation = std::accumulate(dailyPrecipitation.begin(), dailyPrecipitation.end(), 0.0f) / DAYS_IN_A_MONTH;
            std::string weatherEvent = Formulas::determineWeatherEvent(avgTemperature, avgPrecipitation, season, climateZone);

            // Simulate plant states based on weather event
            simulatePlants(plantStates, weatherEvent);

            // Calculate aggregated plant data
            int totalGrass = 0;
            int totalGrowthStages = 0;
            for (const auto& plant : plantStates) {
                if (plant.hasGrass) {
                    totalGrass++;
                    totalGrowthStages += plant.grassGrowthStage;
                }
            }

            float avgGrowthStage = totalGrass > 0 ? static_cast<float>(totalGrowthStages) / totalGrass : 0.0f;

            // Create a JSON log entry with plant information
            nlohmann::json logEntry = {
                {"year", year},
                {"month", month},
                {"season", season},
                {"climate_zone", climateZone},
                {"avg_temperature", avgTemperature},
                {"avg_precipitation", avgPrecipitation},
                {"weather_event", weatherEvent},
                {"total_grass_coverage", totalGrass},
                {"avg_grass_growth_stage", avgGrowthStage}
            };
            LogManager::logEvent("environment", logEntry);
        }
    }

    return 0;
}
