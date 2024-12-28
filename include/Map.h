#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <unordered_map>

// Estrutura para representar um hexágono
struct HexCell {
    std::string id; // ID único do hexágono
    std::string type; // Tipo de terreno (e.g., água, floresta)
    float temperature; // Temperatura atual
    float altitude; // Altitude do hexágono

    bool hasGrass; // Whether grass is present
    int grassGrowthStage; // Growth stage of the grass

    HexCell()
        : id(""), type("undefined"), temperature(0.0f), altitude(0.0f),
          hasGrass(false), grassGrowthStage(0) {}

    // Construtor com parâmetros
    HexCell(const std::string& id, const std::string& type, float temp, float alt)
        : id(id), type(type), temperature(temp), altitude(alt) {}
};

// Classe para representar o mapa hexagonal
class HexMap {
private:
    std::vector<std::vector<HexCell>> grid; // Matriz 2D de células hexagonais
    int width;
    int height;

    // Gera um ID único baseado nas coordenadas e propriedades
    std::string generateHexID(int x, int y, const std::string& type, float temp, float alt);

public:
    // Construtor
    HexMap(int width, int height);

    // Inicializa o mapa com valores padrão
    void initializeMap(const std::string& defaultType, float defaultTemp, float defaultAlt);
    void updateMap(float deltaTime);

    // Obtém a estação atual com base no mês
    std::string getSeason(int month);

    // Obtém o ajuste sazonal de temperatura com base na estação
    float getSeasonalTemperatureAdjustment(const std::string& season);

    // Mostra o mapa em formato simplificado (apenas IDs)
    void logMapState();

    void updatePlants(float deltaTime, const std::string& weatherEvent);
};

#endif // MAP_H
