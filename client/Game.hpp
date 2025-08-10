#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include <SFML/Graphics.hpp>

class Game {
private:
    sf::RenderWindow window;

public:
    Game();
    void run();
};

#endif //PACMAN_GAME_HPP
