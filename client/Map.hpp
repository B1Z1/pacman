#ifndef PACMAN_MAP_HPP
#define PACMAN_MAP_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Map {
private:
    std::vector<std::vector<int>> grid;
    std::vector<sf::RectangleShape> walls;
    std::vector<sf::CircleShape> dots;
    const float CELL_SIZE = 32.0f;

public:
    Map();
    void loadMap(const std::string& filename);
    void render(sf::RenderWindow& window);
    bool checkCollision(const sf::Vector2f& position) const;
    bool checkDotCollision(const sf::Vector2f& position);

    float getCellSize() const { return CELL_SIZE; }
};

#endif //PACMAN_MAP_HPP
