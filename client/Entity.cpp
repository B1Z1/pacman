#include "Entity.hpp"

Entity::Entity(float x, float y) : position(x, y), direction(0.0f, 0.0f), speed(0.0f) {
    shape.setPosition(position);
}

void Entity::update() {
    position += direction * speed;
    shape.setPosition(position);
}

void Entity::render(sf::RenderWindow& window) {
    window.draw(shape);
}
