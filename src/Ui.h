#pragma once

#include "TetrisShape.h"

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>


class Ui {
    std::shared_ptr<sf::RenderWindow> m_window;

    sf::Font m_font;

    std::vector<sf::RectangleShape> m_ui_rects;
    std::vector<sf::Text> m_ui_static_text;
    std::vector<sf::RectangleShape> m_grid;

    sf::RectangleShape m_game_area;

    sf::Text m_score_text;
    sf::Text m_level_text;
    sf::Text m_line_text;

public:
    Ui(std::shared_ptr<sf::RenderWindow> window, sf::Vector2i grid_size);

    void createStaticLeftSideArea();
    void createStaticRightSideArea();
    void createStaticGrid(sf::Vector2i grid_size);
    void createGameArea();

    void drawStaticSideAreas();
    void drawGrid();
    void drawGameArea(sf::Texture& t, sf::Shader& s);

    void drawShape(std::unique_ptr<TetrisShape>& shape, int offset_x = 0, int offset_y = 0);
    void drawNextShapes(std::vector<std::unique_ptr<TetrisShape>>& next_shapes);
    void drawStats(int score, int level, int lines);
};