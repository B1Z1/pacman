#ifndef PACMAN_ENTITY_HPP
#define PACMAN_ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
protected:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;
    sf::RectangleShape shape;

public:
    Entity(float x, float y);
    virtual void update();
    virtual void render(sf::RenderWindow& window);

    sf::Vector2f getPosition() const { return position; }
    void setPosition(sf::Vector2f pos) { position = pos; shape.setPosition(pos); }
    void setDirection(sf::Vector2f dir) { direction = dir; }
};

#endif //PACMAN_ENTITY_HPP
