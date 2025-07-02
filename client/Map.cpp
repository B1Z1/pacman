#include "Map.hpp"
#include <fstream>

Map::Map() {
    // Większa mapa jako tablica 2D (0 - pusta przestrzeń, 1 - ściana, 2 - kulka)
    std::vector<std::vector<int> > defaultMap = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
        { 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1 },
        { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
        { 1, 2, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 2, 1 },
        { 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1 },
        { 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 2, 1, 2, 1, 1, 0, 1, 1, 2, 1, 2, 1, 1, 1, 1 },
        { 1, 2, 2, 2, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 2, 2, 2, 1 },
        { 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1 },
        { 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
        { 1, 2, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1 },
        { 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1 },
        { 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1 },
        { 1, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 1 },
        { 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1 },
        { 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    };
    grid = defaultMap;

    // Tworzenie ścian i kulek
    for (size_t y = 0; y < grid.size(); ++y) {
        for (size_t x = 0; x < grid[y].size(); ++x) {
            if (grid[y][x] == 1) {
                // Ściana
                sf::RectangleShape wall(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                wall.setPosition({
                    x * CELL_SIZE,
                    y * CELL_SIZE
                });
                wall.setFillColor(sf::Color::Blue);
                walls.push_back(wall);
            } else if (grid[y][x] == 2) {
                // Kulka (dot)
                sf::CircleShape dot(CELL_SIZE / 8);
                dot.setPosition({
                    x * CELL_SIZE + CELL_SIZE / 2 - CELL_SIZE / 8,
                    y * CELL_SIZE + CELL_SIZE / 2 - CELL_SIZE / 8
                });
                dot.setFillColor(sf::Color::White);
                dots.push_back(dot);
            }
        }
    }
}

void Map::render(sf::RenderWindow &window) {
    // Renderowanie ścian
    for (const auto &wall: walls) {
        window.draw(wall);
    }

    // Renderowanie kulek
    for (const auto &dot: dots) {
        window.draw(dot);
    }
}

bool Map::checkCollision(const sf::Vector2f &position) const {
    // Konwersja pozycji na indeksy siatki
    int gridX = static_cast<int>(position.x / CELL_SIZE);
    int gridY = static_cast<int>(position.y / CELL_SIZE);

    // Sprawdzenie czy pozycja jest w granicach mapy
    if (gridY >= 0 && gridY < grid.size() && gridX >= 0 && gridX < grid[0].size()) {
        return grid[gridY][gridX] == 1; // 1 oznacza ścianę
    }
    return true; // Kolizja poza mapą
}

bool Map::checkDotCollision(const sf::Vector2f &position) {
    int gridX = static_cast<int>(position.x / CELL_SIZE);
    int gridY = static_cast<int>(position.y / CELL_SIZE);

    if (gridY >= 0 && gridY < grid.size() && gridX >= 0 && gridX < grid[0].size()) {
        if (grid[gridY][gridX] == 2) {
            grid[gridY][gridX] = 0; // Usunięcie kulki z siatki
            // Znalezienie i usunięcie odpowiedniej kulki z wektora
            for (auto it = dots.begin(); it != dots.end(); ++it) {
                if (it->getPosition().x / CELL_SIZE == gridX &&
                    it->getPosition().y / CELL_SIZE == gridY) {
                    dots.erase(it);
                    return true;
                }
            }
        }
    }
    return false;
}
