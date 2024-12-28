#include "Climate.h"
#include "Constants.h"
#include <stdexcept>

// Helper function to map season names to indices
int seasonIndex(const std::string& season) {
    for (int i = 0; i < 4; ++i) {
        if (Constants::SEASONS[i] == season) {
            return i;
        }
    }
    throw std::invalid_argument("Invalid season name: " + season);
}

// Get the climate zone based on latitude
std::string Climate::getClimateZone(float latitude) {
    if (latitude >= 66.5f || latitude <= -66.5f) {
        return "Polar";
    } else if (latitude >= -23.5f && latitude <= 23.5f) {
        return "Tropical";
    } else {
        return "Temperate";
    }
}

// Generate daily temperature
float Climate::generateDailyTemperature(const std::string& season, const std::string& climateZone) {
    using namespace Constants;
    static std::random_device rd;               // Random device for seeding
    static std::mt19937 gen(rd());              // Mersenne Twister random generator
    std::uniform_real_distribution<> dist(-5.0, 5.0); // Daily variation range

    int index = seasonIndex(season);

    float baseTemp;
    if (climateZone == "Polar") {
        baseTemp = POLAR_TEMPERATURE[index];
    } else if (climateZone == "Tropical") {
        baseTemp = TROPICAL_TEMPERATURE[index];
    } else {
        baseTemp = TEMPERATURE_RANGES[index];
    }

    return baseTemp + dist(gen); // Base temperature with random daily variation
}

float Climate::generateDailyPrecipitation(const std::string& season, const std::string& climateZone) {
    using namespace Constants;
    static std::random_device rd;        // Random device para seed
    static std::mt19937 gen(rd());       // Mersenne Twister random generator

    // Ajuste o "range" de variação de acordo com cada clima.
    // Estes valores servem de exemplo; ajuste como preferir.
    float basePrecipitation;
    float maxVariation;

    if (climateZone == "Polar") {
        basePrecipitation = 0.5f;   // Anteriormente era 0.5
        maxVariation     = 1.0f;   // Antes você somava até +5.0, agora menos
    }
    else if (climateZone == "Tropical") {
        basePrecipitation = 2.0f;   // Anteriormente era 5.0
        maxVariation     = 3.0f;   // Em vez de somar até +5.0
    }
    else { // Temperate
        basePrecipitation = 1.0f;   // Antes era 3.0
        maxVariation     = 2.0f;   // Em vez de +5.0
    }

    // Se desejar, você pode adicionar um fator sazonal
    // Ex: no Inverno, menos precipitação, na Primavera, mais etc.
    float seasonFactor = 1.0f;
    if (season == "Winter") {
        seasonFactor = 0.7f;
    } else if (season == "Spring") {
        seasonFactor = 1.2f;
    } else if (season == "Autumn") {
        seasonFactor = 0.9f;
    }
    // (No Summer, deixamos 1.0f ou ajustamos como quiser.)

    // Cria a distribuição com base no 'maxVariation'
    std::uniform_real_distribution<float> dist(0.0f, maxVariation);

    // Calcula e aplica o fator sazonal
    float precipitation = (basePrecipitation + dist(gen)) * seasonFactor;
    return precipitation;
}
