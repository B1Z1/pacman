#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include <SFML/Graphics.hpp>
#include "Pacman.hpp"
#include "Map.hpp"
#include <memory>

class Game {
private:
    sf::RenderWindow window;
    bool isRunning;
    sf::Clock clock;
    float deltaTime;

    std::unique_ptr<Pacman> pacman;
    std::unique_ptr<Map> map;

    void processEvents();
    void update();
    void render();

public:
    Game();
    void run();
};

#endif //PACMAN_GAME_HPP
