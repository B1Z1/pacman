#include "Pacman.hpp"

Pacman::Pacman(float x, float y) : Entity(x, y) {
    shape.setSize(sf::Vector2f(30.0f, 30.0f));
    shape.setFillColor(sf::Color::Yellow);
    shape.setOrigin({ 15.0f, 15.0f });
    speed = SPEED;
}

void Pacman::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        direction = sf::Vector2f(-1.0f, 0.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        direction = sf::Vector2f(1.0f, 0.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        direction = sf::Vector2f(0.0f, -1.0f);
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        direction = sf::Vector2f(0.0f, 1.0f);
    }
}

void Pacman::update(float deltaTime, const Map &map) {
    handleInput();

    // Oblicz nową potencjalną pozycję
    sf::Vector2f newPosition = position + direction * speed * deltaTime;

    // Sprawdź kolizję z mapą
    if (!map.checkCollision(newPosition)) {
        position = newPosition;
        shape.setPosition(position);
    }
}
