#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Pacman.hpp"
#include "Map.hpp"

Game::Game() : window(sf::VideoMode({800, 600}), "Pacman"), isRunning(true), deltaTime(0.0f) {
    window.setFramerateLimit(60);

    // Inicjalizacja mapy i Pacmana
    map = std::make_unique<Map>();
    pacman = std::make_unique<Pacman>(400.0f, 300.0f); // Startowa pozycja Pacmana
}

void Game::processEvents() {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Game::update() {
    deltaTime = clock.restart().asSeconds();
    pacman->update(deltaTime, *map);
}

void Game::render() {
    window.clear(sf::Color::Black);

    map->render(window);
    pacman->render(window);

    window.display();
}

void Game::run() {
    while (isRunning && window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

int main() {
    Game game;
    game.run();
    return 0;
}
