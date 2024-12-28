#include "SolarCycle.h"

void SolarCycle::advanceTime(float deltaTime) {
    timeOfYear += deltaTime;
    timeOfDay += deltaTime;

    if (timeOfDay >= dayLength) {
        timeOfDay -= dayLength; // Reinicia o ciclo diário
    }
}

float SolarCycle::getTemperatureFactor() const {
    float normalizedTime = timeOfDay / dayLength; // Tempo normalizado (0.0 a 1.0)
    if (normalizedTime <= 0.5f) {
        // Impacto máximo durante o dia (meio-dia)
        return maxTemperatureImpact * std::sin(normalizedTime * M_PI);
    } else {
        // Impacto mínimo durante a noite
        return minTemperatureImpact * std::cos((normalizedTime - 0.5f) * M_PI);
    }
}

void SolarCycle::logCycleState() const {
    std::cout << "Solar Cycle State:\n";
    std::cout << " - Time of Year (hours): " << timeOfYear << "\n";
    std::cout << " - Time of Day (hours): " << timeOfDay << "\n";
    std::cout << " - Day Length (hours): " << dayLength << "\n";
    std::cout << " - Temperature Factor: " << getTemperatureFactor() << "\n";
}
