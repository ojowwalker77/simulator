#ifndef SOLARCYCLE_H
#define SOLARCYCLE_H

#include <cmath> // Para funções matemáticas como sin e fmod
#include <iostream>

class SolarCycle {
private:
    float timeOfYear;              // Tempo acumulado no ano (em horas)
    float timeOfDay;               // Hora atual do dia (0 a dayLength)
    float dayLength;               // Duração de um dia (em horas)
    float maxTemperatureImpact;    // Impacto máximo da temperatura diária
    float minTemperatureImpact;    // Impacto mínimo da temperatura diária

public:
    // Construtor com valores padrão
    SolarCycle(float dayLength = 24.0f, float maxImpact = 10.0f, float minImpact = -10.0f)
        : timeOfYear(0.0f), timeOfDay(0.0f), dayLength(dayLength),
          maxTemperatureImpact(maxImpact), minTemperatureImpact(minImpact) {}

    // Avança o tempo no ciclo solar
    void advanceTime(float deltaTime);

    // Obtém o fator de temperatura com base no ciclo solar
    float getTemperatureFactor() const;

    // Obtém o tempo atual do ano em horas
    float getTimeOfYear() const { return timeOfYear; }

    // Mostra o estado atual do ciclo solar (para debug)
    void logCycleState() const;
};

#endif // SOLARCYCLE_H
