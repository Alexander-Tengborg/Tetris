#include <SFML/Graphics.hpp>

#include <vector>
#include <cmath>
#include <algorithm>

#include "TetrisShape.h"

#include <iostream>

const int grid_rows = 20;
const int grid_cols = 10;

// https://i.imgur.com/kupYzAI.png

//Currently gets redefined every game loop, despite being mostly static (score etc will change)
void draw_left_side_area(sf::RenderWindow& window) {
    sf::RectangleShape left_side_area(sf::Vector2f(250, 800));
    left_side_area.setFillColor(sf::Color::Black);
    left_side_area.setPosition(sf::Vector2f(0, 0));
    
    window.draw(left_side_area);

    // FONT
    sf::Font font;
    font.loadFromFile("Roboto-Regular.ttf");

    // HOLD BIG BOX
    sf::RectangleShape hold(sf::Vector2f(200, 185));
    hold.setFillColor(sf::Color::Black);
    hold.setOutlineColor(sf::Color::Cyan);
    hold.setOutlineThickness(2);
    hold.setPosition(sf::Vector2f(25, 50));

    window.draw(hold);

    // HOLD TEXT
    sf::Text hold_text("Hold", font);
    hold_text.setPosition(sf::Vector2f(85, 50));

    window.draw(hold_text);

    // HOLD SMALL BOX
    sf::RectangleShape hold_small(sf::Vector2f(150, 120));
    hold_small.setPosition(sf::Vector2f(50, 90));
    hold_small.setFillColor(sf::Color::Black);
    hold_small.setOutlineColor(sf::Color::Cyan);
    hold_small.setOutlineThickness(2);

    window.draw(hold_small);

    // STATS 
    sf::RectangleShape stats(sf::Vector2f(200, 350));
    stats.setFillColor(sf::Color::Black);
    stats.setOutlineColor(sf::Color::Cyan);
    stats.setOutlineThickness(2);
    stats.setPosition(sf::Vector2f(25, 400));

    window.draw(stats);


    // STATS - SCORE TEXT
    sf::Text score_text("Score", font);
    score_text.setPosition(sf::Vector2f(85, 400));

    window.draw(score_text);

    // STATS - SCORE BOX
    sf::RectangleShape score(sf::Vector2f(150, 50));
    score.setPosition(sf::Vector2f(50, 440));
    score.setFillColor(sf::Color::Black);
    score.setOutlineColor(sf::Color::Cyan);
    score.setOutlineThickness(2);

    window.draw(score);

    // STATS - SCORE VALUE
    sf::Text score_value("23", font);
    score_value.setPosition(sf::Vector2f(110, 445));

    window.draw(score_value);

    // STATS - LEVEL TEXT
    sf::Text level_text("Level", font);
    level_text.setPosition(sf::Vector2f(85, 500));

    window.draw(level_text);

    // STATS - LEVEL BOX
    sf::RectangleShape level(sf::Vector2f(150, 50));
    level.setPosition(sf::Vector2f(50, 540));
    level.setFillColor(sf::Color::Black);
    level.setOutlineColor(sf::Color::Cyan);
    level.setOutlineThickness(2);

    window.draw(level);

    // STATS - LEVEL VALUE
    sf::Text level_value("24", font);
    level_value.setPosition(sf::Vector2f(110, 545));

    window.draw(level_value);

    // STATS - LINES TEXT
    sf::Text lines_text("Lines", font);
    lines_text.setPosition(sf::Vector2f(85, 600));

    window.draw(lines_text);

    // STATS - LINES BOX
    sf::RectangleShape lines(sf::Vector2f(150, 50));
    lines.setPosition(sf::Vector2f(50, 640));
    lines.setFillColor(sf::Color::Black);
    lines.setOutlineColor(sf::Color::Cyan);
    lines.setOutlineThickness(2);

    window.draw(lines);

    // STATS - LINES VALUE
    sf::Text lines_value("24", font);
    lines_value.setPosition(sf::Vector2f(110, 645));

    window.draw(lines_value);

}

//Currently gets redefined every game loop, despite being mostly static (next will change)
void draw_right_side_area(sf::RenderWindow& window) {
    sf::RectangleShape right_side_area(sf::Vector2f(250, 800));
    right_side_area.setFillColor(sf::Color::Black);
    right_side_area.setPosition(sf::Vector2f(650, 0));
    
    window.draw(right_side_area);

    // FONT
    sf::Font font;
    font.loadFromFile("Roboto-Regular.ttf");

    // NEXT BIG BOX
    sf::RectangleShape next(sf::Vector2f(200, 350));
    next.setFillColor(sf::Color::Black);
    next.setOutlineColor(sf::Color::Cyan);
    next.setOutlineThickness(2);
    next.setPosition(sf::Vector2f(675, 50));

    window.draw(next);

    // NEXT TEXT
    sf::Text next_text("Next", font);
    next_text.setPosition(sf::Vector2f(735, 50));

    window.draw(next_text);

    // NEXT SMALL BOX
    sf::RectangleShape next_small(sf::Vector2f(150, 285));
    next_small.setPosition(sf::Vector2f(700, 90));
    next_small.setFillColor(sf::Color::Black);
    next_small.setOutlineColor(sf::Color::Cyan);
    next_small.setOutlineThickness(2);

    window.draw(next_small);

}

//Currently gets redefined every game loop, despite being completely static
void drawGrid(sf::RenderWindow& window) {
    for(int i = 1; i < grid_rows; i++) {
        sf::RectangleShape line(sf::Vector2f(400, 0.5f));
        line.setPosition(sf::Vector2f(250, i*800/grid_rows));
        line.setFillColor(sf::Color(42, 42, 42));

        window.draw(line);
    }

    for(int i = 1; i < grid_cols; i++) {
        sf::RectangleShape line(sf::Vector2f(1, 800));
        line.setPosition(sf::Vector2f(250+i*400/grid_cols, 0));
        line.setFillColor(sf::Color(42, 42, 42));

        window.draw(line);
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(900, 800), "Tetris");

    sf::RectangleShape game_area(sf::Vector2f(400, 800));
    game_area.setFillColor(sf::Color::Black);
    game_area.setOutlineColor(sf::Color::White);
    game_area.setOutlineThickness(3);
    game_area.setPosition(sf::Vector2f(250, 0));


    // The starting coordinate for every new TetrisShape
    sf::Vector2f start_coordinate(4, 1);

    TetrisShape current_shape = TetrisShape::generateRandomShape(start_coordinate);

    std::vector<std::vector<sf::RectangleShape>> placed_shapes(grid_rows, std::vector<sf::RectangleShape>(grid_cols));

    sf::Clock clock_y;
    sf::Clock clock_x;

    sf::Clock clock_rotate;

    int speed_up = 1;

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && clock_rotate.getElapsedTime().asMilliseconds() >= 100) {
            current_shape.rotate();
            clock_rotate.restart();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && clock_x.getElapsedTime().asMilliseconds() >= 75) {
            current_shape.moveLeft();
            clock_x.restart();
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && clock_x.getElapsedTime().asMilliseconds() >= 75) {
            current_shape.moveRight();
            clock_x.restart();
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            speed_up = 20;
        } else {
            speed_up = 1;
        }

        if(clock_y.getElapsedTime().asMilliseconds() >= 1000 / speed_up) {
            if(current_shape.canMoveDown())
                current_shape.moveDown();
            else {
                current_shape.place(placed_shapes);
                current_shape = TetrisShape::generateRandomShape(start_coordinate);
            }

            clock_y.restart();
        }

        window.clear();

        draw_left_side_area(window);
        draw_right_side_area(window);

        window.draw(game_area);

        current_shape.update();
        current_shape.draw(window);

        for(const auto& v: placed_shapes) {
            for(const auto& r: v) {
                window.draw(r);
            }
        }

        // DRAW GRID
        drawGrid(window);

        window.display();
    }

    return 0;
}