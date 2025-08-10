#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "GameConfig.h"

sf::FloatRect calculateView(const sf::Vector2f &windowSize, float pacRatio) {
    sf::Vector2f viewSize = windowSize;
    sf::FloatRect viewport({ 0.f, 0.f }, { 1.f, 1.f });
    float ratio = viewSize.x / viewSize.y;

    // too high
    if (ratio < pacRatio) {
        viewSize.y = viewSize.x / pacRatio;
        float vp_h = viewSize.y / windowSize.y;
        viewport.size.y = vp_h;
        viewport.position.y = (1.f - vp_h) / 2.f;
    }
    // too wide
    else if (ratio > pacRatio) {
        viewSize.x = viewSize.y * pacRatio;
        float vp_w = viewSize.x / windowSize.x;

        viewport.position.x = vp_w;
        viewport.size.x = (1.f - vp_w) / 2.f;
    }
    return viewport;
}

void resizeWindow(sf::RenderWindow &window, const sf::Event::Resized &resized) {
    float width = resized.size.x;
    float height = resized.size.y;

    sf::View view = window.getView();

    view.setViewport(calculateView({ width, height }, WIN_RATIO));
    window.setView(view);
}

int main() {
    Game game;

    srand(time(NULL));

    auto viewWidth = 28 * TILE_SIZE;
    auto viewHeight = 36 * TILE_SIZE;
    auto windowWidth = viewWidth * 2;
    auto windowHeight = viewHeight * 2;

    sf::RenderWindow window(
        sf::VideoMode({ windowWidth, windowHeight }),
        "Pacman"
    );

    window.setFramerateLimit(60);
    window.setView(sf::View({ 0, 0 }, { static_cast<float>(viewWidth), static_cast<float>(viewHeight) }));

    sf::Clock clock;
    sf::Time elapsed;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto *resized = event->getIf<sf::Event::Resized>()) {
                resizeWindow(window, *resized);
            }

            if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                    window.close();
                }
            }
        }

        elapsed = clock.restart();
    }

    return 0;
}
