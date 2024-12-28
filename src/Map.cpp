#include "Map.h"
#include "SolarCycle.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

SolarCycle solarCycle;

HexMap::HexMap(int width, int height) : width(width), height(height) {
    grid.resize(height, std::vector<HexCell>(width));
}

void HexMap::initializeMap(const std::string& defaultType, float defaultTemp, float defaultAlt) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::string id = generateHexID(x, y, defaultType, defaultTemp, defaultAlt);
            grid[y][x] = HexCell(id, defaultType, defaultTemp, defaultAlt);
        }
    }
}

std::string HexMap::generateHexID(int x, int y, const std::string& type, float temp, float alt) {
    return "X" + std::to_string(x) + "Y" + std::to_string(y) + "_" + type +
           "_T" + std::to_string(temp) + "_A" + std::to_string(alt);
}

std::string HexMap::getSeason(int month) {
    for (size_t i = 0; i < std::size(Constants::SEASONS); ++i) {
        if (month >= Constants::SEASON_STARTS[i] &&
            (i == std::size(Constants::SEASONS) - 1 || month < Constants::SEASON_STARTS[i + 1])) {
            return Constants::SEASONS[i];
        }
    }
    return "Unknown"; // Fallback for invalid months
}

float HexMap::getSeasonalTemperatureAdjustment(const std::string& season) {
    for (size_t i = 0; i < std::size(Constants::SEASONS); ++i) {
        if (season == Constants::SEASONS[i]) {
            return Constants::TEMPERATURE_RANGES[i];
        }
    }
    return 0.0f; // Fallback for unknown seasons
}

void HexMap::updateMap(float deltaTime) {
    solarCycle.advanceTime(deltaTime);

    int month = static_cast<int>(solarCycle.getTimeOfYear() / Constants::HOURS_IN_A_MONTH) % Constants::MONTHS_IN_A_YEAR + 1;
    std::string season = getSeason(month);
    float temperatureFactor = solarCycle.getTemperatureFactor() + getSeasonalTemperatureAdjustment(season);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            grid[y][x].temperature += temperatureFactor;

            if (grid[y][x].temperature > 50.0f) grid[y][x].temperature = 50.0f; // Cap at 50°C
            if (grid[y][x].temperature < -30.0f) grid[y][x].temperature = -30.0f; // Cap at -30°C
        }
    }
}

void HexMap::logMapState() {
    int month = static_cast<int>(solarCycle.getTimeOfYear() / Constants::HOURS_IN_A_MONTH) % Constants::MONTHS_IN_A_YEAR + 1;
    std::string season = getSeason(month);

    std::cout << "Time of Year: " << solarCycle.getTimeOfYear()
              << " | Month: " << month
              << " | Season: " << season
              << " | Seasonal Adjustment: " << getSeasonalTemperatureAdjustment(season) << "\n";

    std::cout << "Temperature Map (°C):\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            std::cout << std::fixed << std::setprecision(1) << grid[y][x].temperature << "\t";
        }
        std::cout << "\n";
    }
    std::cout << "--------------------------------------------\n";
}

void HexMap::updatePlants(float deltaTime, const std::string& weatherEvent) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto& cell = grid[y][x];

            // Grass logic: Dies under snow
            if (weatherEvent == "Snow") {
                cell.hasGrass = false;
                cell.grassGrowthStage = 0;
            } else if (cell.hasGrass && cell.grassGrowthStage < 5) {
                // Grass grows up to stage 5
                cell.grassGrowthStage++;
            } else if (!cell.hasGrass && weatherEvent != "Snow") {
                // Grass starts growing in non-snowy conditions
                cell.hasGrass = true;
                cell.grassGrowthStage = 1;
            }
        }
    }
}
