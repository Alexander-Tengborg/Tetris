#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

#include "TetrisShape.h"

class Ui {

    sf::Font m_font;
    std::shared_ptr<sf::RenderWindow> m_window;

    std::vector<sf::RectangleShape> m_ui_rects;
    std::vector<sf::Text> m_ui_static_text;
    std::vector<sf::RectangleShape> m_grid;

    sf::RectangleShape m_game_area;

    sf::Text m_score_text;
    sf::Text m_level_text;
    sf::Text m_line_text;

public:
    Ui(std::shared_ptr<sf::RenderWindow> window, sf::Vector2f grid_size);

    void createStaticLeftSideArea();
    void createStaticRightSideArea();
    void createStaticGrid(sf::Vector2f grid_size);
    void createGameArea();

    void drawStaticSideAreas();
    void drawGrid();
    void drawGameArea();

    void drawNextShapes(std::vector<TetrisShape>& next_shapes);
    void drawHeldShape(TetrisShape& held_shape);
    void drawStats(int score, int level, int lines);
};