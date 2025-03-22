#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Pacman");

    sf::CircleShape pacman(25);

    pacman.setFillColor(sf::Color::Yellow);
    pacman.setPosition({ 100, 100 });

    float speed = 0.1;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (isKeyPressed(sf::Keyboard::Key::W)) {
            pacman.move({ 0, -speed });
        }

        if (isKeyPressed(sf::Keyboard::Key::S)) {
            pacman.move({ 0, speed });
        }

        if (isKeyPressed(sf::Keyboard::Key::D)) {
            pacman.move({ speed, 0 });
        }

        if (isKeyPressed(sf::Keyboard::Key::A)) {
            pacman.move({ -speed, 0 });
        }


        window.clear();
        window.draw(pacman);
        window.display();
    }
}
