#ifndef GRASS_H
#define GRASS_H

#include <string>

class Grass {
public:
    Grass(); // Constructor
    void update(float temperature, float precipitation, const std::string& weatherEvent); // Update state
    bool isAlive() const; // Check if grass is alive
    float getGrowthLevel() const; // Get current growth level

private:
    bool alive;        // Is grass alive?
    float growthLevel; // Current growth level (e.g., 0.0 to 1.0)

    void grow();  // Grass grows
    void die();   // Grass dies
};

#endif // GRASS_H
