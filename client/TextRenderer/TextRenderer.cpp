#include <cmath>
#include <SFML/Graphics.hpp>

#include "TextRenderer.hpp"
#include "../Global.hpp"

/**
 * Renderuje tekst na ekranie gry używając własnej tekstury czcionki
 *
 * @param i_center Czy tekst ma być wycentrowany (true) czy wyrównany do lewej (false)
 * @param i_x Pozycja X tekstu (w pikselach)
 * @param i_y Pozycja Y tekstu (w pikselach)
 * @param i_text Tekst do wyświetlenia (może zawierać znaki nowej linii)
 * @param i_window Referencja do okna SFML do renderowania
 */
void render_text(bool i_center, unsigned short i_x, unsigned short i_y, const std::string &i_text,
               sf::RenderWindow &i_window) {
    short character_x = i_x;
    short character_y = i_y;

    unsigned char character_width;

    sf::Sprite character_sprite;

    sf::Texture font_texture;
    font_texture.loadFromFile("Resources/Font.png");


    character_width = font_texture.getSize().x / 96;

    character_sprite.setTexture(font_texture);

    if (1 == i_center) {
        character_x = static_cast<short>(round(
            0.5f * (CELL_SIZE * MAP_WIDTH - character_width * i_text.substr(0, i_text.find_first_of('\n')).size())));
        character_y = static_cast<short>(round(
            0.5f * (CELL_SIZE * MAP_HEIGHT - FONT_HEIGHT * (1 + std::count(i_text.begin(), i_text.end(), '\n')))));
    }

    for (std::string::const_iterator a = i_text.begin(); a != i_text.end(); a++) {
        if ('\n' == *a) {
            if (1 == i_center) {
                character_x = static_cast<short>(
                    round(
                        0.5f * (
                            CELL_SIZE * MAP_WIDTH - character_width * i_text.substr(
                                1 + a - i_text.begin(),
                                i_text.find_first_of('\n', 1 + a - i_text.begin()) - (1 + a - i_text.begin())
                            ).
                            size()
                        )
                    )
                );
            } else {
                character_x = i_x;
            }

            character_y += FONT_HEIGHT;

            continue;
        }

        character_sprite.setPosition(character_x, character_y);
        character_sprite.setTextureRect(sf::IntRect(character_width * (*a - 32), 0, character_width, FONT_HEIGHT));

        character_x += character_width;

        i_window.draw(character_sprite);
    }
}
