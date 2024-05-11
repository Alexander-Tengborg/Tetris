#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <memory>

#include "GameSounds.h"
#include "TetrisShape.h"
#include "Ui.h"

#include <iostream>
#include <time.h>
#include <optional>
#include <memory>

class Game {
    const sf::Vector2f m_grid_size = {10, 20};

    const sf::Vector2f m_window_size = {900, 800};
    // const sf::Vector2f m_game_size = {400, m_window_size.y};
    // const sf::Vector2f m_side_area_size = {(m_window_size.x-m_game_size.x)/2, m_window_size.y};

    // The starting coordinate for every new TetrisShape
    sf::Vector2f m_start_coordinates = {4, 1};

    std::shared_ptr<sf::RenderWindow> m_window;
    GameSounds m_sounds;

    TetrisShape m_current_shape;
    std::optional<TetrisShape> m_held_shape;

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

    std::unique_ptr<Ui> m_ui;

public:
    Game();

    void moveRowsDown(std::vector<int> cleared_rows);

    int clearRows(sf::Vector2i row_span);

    void calculateFallSpeed();

    void runGame();
};