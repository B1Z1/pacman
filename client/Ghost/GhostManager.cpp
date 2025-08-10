#include "GhostManager.hpp"

#include <array>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "Ghost.hpp"
#include "../Global.hpp"
#include "../Pacman/Pacman.hpp"

/**
 * Konstruktor klasy GhostManager
 * Inicjalizuje menedżera duchów z domyślnymi wartościami:
 * - ustawia falę na 0
 * - ustawia timer fali na LONG_SCATTER_DURATION
 * - tworzy tablicę 4 duchów z odpowiednimi ID (0-3)
 */
GhostManager::GhostManager() : current_wave(0),
                               wave_timer(LONG_SCATTER_DURATION),
                               ghosts({ Ghost(0), Ghost(1), Ghost(2), Ghost(3) }) {
}

/**
 * Rysuje wszystkie duchy na ekranie
 * @param i_flash Parametr określający czy duchy mają migać
 * @param i_window Okno renderowania SFML
 */
void GhostManager::draw(bool i_flash, sf::RenderWindow &i_window) {
    for (Ghost &ghost: ghosts) {
        ghost.draw(i_flash, i_window);
    }
}

/**
 * Resetuje stan wszystkich duchów do wartości początkowych
 * @param i_level Aktualny poziom gry (wpływa na czas rozproszenia)
 * @param i_ghost_positions Tablica pozycji startowych dla duchów
 */
void GhostManager::reset(unsigned char i_level, const std::array<Position, 4> &i_ghost_positions) {
    current_wave = 0;


    wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));

    for (unsigned char a = 0; a < 4; a++) {
        ghosts[a].set_position(i_ghost_positions[a].x, i_ghost_positions[a].y);
    }

    for (Ghost &ghost: ghosts) {
        ghost.reset(ghosts[2].get_position(), ghosts[0].get_position());
    }
}

/**
 * Aktualizuje stan wszystkich duchów
 * Zarządza falami (chase/scatter), timerami i ruchem duchów
 * @param i_level Aktualny poziom gry
 * @param i_map Mapa gry
 * @param i_pacman Referencja do obiektu Pacmana
 */
void GhostManager::update(unsigned char i_level, std::array<std::array<Cell, MAP_HEIGHT>, MAP_WIDTH> &i_map,
                          Pacman &i_pacman) {
    if (0 == i_pacman.get_energizer_timer()) {
        if (0 == wave_timer) {
            if (7 > current_wave) {
                current_wave++;

                for (Ghost &ghost: ghosts) {
                    ghost.switch_mode();
                }
            }


            if (1 == current_wave % 2) {
                wave_timer = CHASE_DURATION;
            } else if (2 == current_wave) {
                wave_timer = static_cast<unsigned short>(LONG_SCATTER_DURATION / pow(2, i_level));
            } else {
                wave_timer = static_cast<unsigned short>(SHORT_SCATTER_DURATION / pow(2, i_level));
            }
        } else {
            wave_timer--;
        }
    }

    for (Ghost &ghost: ghosts) {
        ghost.update(i_level, i_map, ghosts[0], i_pacman);
    }
}
