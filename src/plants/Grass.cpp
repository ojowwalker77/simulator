#include "plants/Grass.h"

Grass::Grass() : alive(true), growthLevel(0.0f) {}

void Grass::update(float temperature, float precipitation, const std::string& weatherEvent) {
    if (weatherEvent == "Snow") {
        die();
    } else if (alive && temperature > 1.0f && precipitation > 1.0f) {
        grow();
    }
}

bool Grass::isAlive() const {
    return alive;
}

float Grass::getGrowthLevel() const {
    return growthLevel;
}

void Grass::grow() {
    if (growthLevel < 1.0f) {
        growthLevel += 0.1f; // Increment growth level
    }
}

void Grass::die() {
    alive = false;
    growthLevel = 0.0f; // Reset growth
}
