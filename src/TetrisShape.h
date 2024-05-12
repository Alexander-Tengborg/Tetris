#pragma once
#define _USE_MATH_DEFINES

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>
#include <cmath>
#include <array>
#include <time.h>
#include <memory>
#include <optional>

//TODO
//typedef this std::vector<std::vector<std::optional<sf::RectangleShape>>>
//OR make it a shared pointer instead and store it is a member variable

class TetrisShape {
public:
    std::vector<sf::RectangleShape> m_cubes;
    std::vector<sf::Vector2f> m_offsets;

    //should be const
    std::vector<sf::Vector2f> m_original_offsets;

    sf::Vector2i m_grid_coord;

    bool m_can_rotate;

    static const std::array<std::vector<sf::Vector2f>, 7> shapes;

public:
    TetrisShape();

    TetrisShape(sf::Vector2i start, std::vector<sf::Vector2f> offsets, sf::Texture& texture, sf::Rect<int> texture_rect, bool can_rotate=true);

    sf::Vector2i calculateXBounds();

    void reset(sf::Vector2i start);

    void draw(std::shared_ptr<sf::RenderWindow> window);
    void draw(std::shared_ptr<sf::RenderWindow> window, sf::Shader& shader);

    void update();

    bool canMoveLeft(std::vector<std::vector<std::optional<sf::RectangleShape>>>& placed_shapes);

    void moveLeft();

    bool canMoveRight(std::vector<std::vector<std::optional<sf::RectangleShape>>>& placed_shapes);

    void moveRight();

    bool canMoveDown(std::vector<std::vector<std::optional<sf::RectangleShape>>>& placed_shapes);

    void moveDown();

    bool canMove(std::vector<std::vector<std::optional<sf::RectangleShape>>>& placed_shapes, int x_dir, int y_dir, std::vector<sf::Vector2f> offsets={});

    std::vector<sf::Vector2f> calculateRotatedCubeOffsets();

    void rotate(std::vector<std::vector<std::optional<sf::RectangleShape>>>& placed_shapes);

    sf::Vector2i place(std::vector<std::vector<std::optional<sf::RectangleShape>>>& placed_shapes);

    void setTexture(sf::Texture& texture);

    static TetrisShape generateRandomShape(sf::Vector2i grid_coord, sf::Texture& texture);
};