#pragma once
#define _USE_MATH_DEFINES

#include <vector>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <cmath>

class TetrisShape {
public:
    std::vector<sf::RectangleShape> m_cubes;
    std::vector<sf::Vector2f> m_offsets;

    sf::Vector2f m_grid_coord;

    sf::Vector2f m_min_bounds;
    sf::Vector2f m_max_bounds;

public:
    TetrisShape(sf::Vector2f start, std::vector<sf::Vector2f> offsets);

    void draw(sf::RenderWindow& window);

    //USE OFFSETS VECTOR HERE?
    void update();

    void calculateBounds();

    bool canMoveLeft();

    void moveLeft();

    bool canMoveRight();

    void moveRight();

    bool canMoveDown();

    void moveDown();

    void rotateCube(sf::Vector2f& offset);

    void rotate();

    void place(std::vector<std::vector<sf::RectangleShape>>& placed_shapes);

    static TetrisShape generateRandomShape(sf::Vector2f grid_coord = {0, 1});
};