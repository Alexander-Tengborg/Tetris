#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

#include "GameSounds.h"
#include "TetrisShape.h"

#include <iostream>
#include <time.h>
#include <optional>

class Game {
    const sf::Vector2f m_grid_size = {10, 20};

    const sf::Vector2f m_game_size = {900, 800};

    // The starting coordinate for every new TetrisShape
    sf::Vector2f m_start_coordinates = {4, 1};

    sf::RenderWindow m_window;
    GameSounds m_sounds;

    TetrisShape m_current_shape;
    std::optional<TetrisShape> m_held_shape;

    sf::Font m_font;

    std::vector<std::vector<sf::RectangleShape>> m_placed_shapes;

    //Dont need 3 clocks, can just use 1 with modulo instead
    sf::Clock m_clock_y;
    sf::Clock m_clock_x;
    sf::Clock m_clock_rotate;

    int m_score = 0;
    int m_level = 0;
    int m_lines = 0;

    sf::Texture m_texture;

    std::vector<TetrisShape> m_next_shapes;

    bool m_switched_block;

public:
    Game();

    void drawLeftSideArea();
    void drawRightSideArea();
    void drawGrid();
    void drawGameArea();

    void moveRowsDown(std::vector<int> cleared_rows);

    int clearRows(sf::Vector2i row_span);

    void calculateFallSpeed();

    void runGame();
};