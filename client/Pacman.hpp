#ifndef PACMAN_PACMAN_HPP
#define PACMAN_PACMAN_HPP

#include "Entity.hpp"
#include "Map.hpp"

class Pacman : public Entity {
private:
    static constexpr float SPEED = 200.0f;

public:
    Pacman(float x, float y);
    void update(float deltaTime, const Map& map);
    void handleInput();
};

#endif //PACMAN_PACMAN_HPP
