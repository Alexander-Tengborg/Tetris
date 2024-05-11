#include "Game.h"

Game::Game() {
    m_window.create(sf::VideoMode(m_game_size.x, m_game_size.y), "Tetris!");

    //UNUSED
    // if(!m_texture.loadFromFile("../resources/textures/red.png"))
    //     std::cout << "FAILED TO LOAD RED.PNG D:" << "\n";    

    m_switched_block = false;

    //FIXME fix this so it can return properly  
    if(!m_sounds.loadSounds())
        return;

    m_font.loadFromFile("../resources/fonts/Roboto-Regular.ttf");

    m_current_shape = TetrisShape::generateRandomShape(m_start_coordinates);
    for(int i = 0; i < 3; i++)
        m_next_shapes.push_back(TetrisShape::generateRandomShape(m_start_coordinates));

    m_placed_shapes.resize(m_grid_size.y, std::vector<sf::RectangleShape>(m_grid_size.x));
}

//FIXME Currently gets redefined every game loop, despite being mostly static (score etc will change)
void Game::drawLeftSideArea() {
    //FIXME Use variables/constants instead of 250, 800;
    sf::RectangleShape left_side_area(sf::Vector2f(250, 800));
    left_side_area.setFillColor(sf::Color::Black);
    left_side_area.setPosition(sf::Vector2f(0, 0));
    
    m_window.draw(left_side_area);

    // HOLD BIG BOX
    sf::RectangleShape hold(sf::Vector2f(200, 185));
    hold.setFillColor(sf::Color::Black);
    hold.setOutlineColor(sf::Color::Cyan);
    hold.setOutlineThickness(2);
    hold.setPosition(sf::Vector2f(25, 50));

    m_window.draw(hold);

    // HOLD TEXT
    sf::Text hold_text("Hold", m_font);
    hold_text.setPosition(sf::Vector2f(85, 50));

    m_window.draw(hold_text);

    // HOLD SMALL BOX
    sf::RectangleShape hold_small(sf::Vector2f(150, 120));
    hold_small.setPosition(sf::Vector2f(50, 90));
    hold_small.setFillColor(sf::Color::Black);
    hold_small.setOutlineColor(sf::Color::Cyan);
    hold_small.setOutlineThickness(2);

    m_window.draw(hold_small);

    //HELD SHAPE
    if(m_held_shape.has_value()) {
        for(int i = 0; i < m_held_shape.value().m_cubes.size(); i++) {
            m_held_shape.value().m_cubes[i].setPosition(sf::Vector2f(60 + (m_held_shape.value().m_offsets[i].x)*40, 120+(m_held_shape.value().m_offsets[i].y)*40));
        }
        m_held_shape.value().draw(m_window);
    }

    // STATS 
    sf::RectangleShape stats(sf::Vector2f(200, 350));
    stats.setFillColor(sf::Color::Black);
    stats.setOutlineColor(sf::Color::Cyan);
    stats.setOutlineThickness(2);
    stats.setPosition(sf::Vector2f(25, 400));

    m_window.draw(stats);


    // STATS - SCORE TEXT
    sf::Text score_text("Score", m_font);
    score_text.setPosition(sf::Vector2f(85, 400));

    m_window.draw(score_text);

    // STATS - SCORE BOX
    sf::RectangleShape score(sf::Vector2f(150, 50));
    score.setPosition(sf::Vector2f(50, 440));
    score.setFillColor(sf::Color::Black);
    score.setOutlineColor(sf::Color::Cyan);
    score.setOutlineThickness(2);

    m_window.draw(score);

    // STATS - SCORE VALUE
    sf::Text score_value(std::to_string(m_score), m_font);
    score_value.setPosition(sf::Vector2f(110, 445));

    m_window.draw(score_value);

    // STATS - LEVEL TEXT
    sf::Text level_text("Level", m_font);
    level_text.setPosition(sf::Vector2f(85, 500));

    m_window.draw(level_text);

    // STATS - LEVEL BOX
    sf::RectangleShape level(sf::Vector2f(150, 50));
    level.setPosition(sf::Vector2f(50, 540));
    level.setFillColor(sf::Color::Black);
    level.setOutlineColor(sf::Color::Cyan);
    level.setOutlineThickness(2);

    m_window.draw(level);

    // STATS - LEVEL VALUE
    sf::Text level_value(std::to_string(m_level), m_font);
    level_value.setPosition(sf::Vector2f(110, 545));

    m_window.draw(level_value);

    // STATS - LINES TEXT
    sf::Text lines_text("Lines", m_font);
    lines_text.setPosition(sf::Vector2f(85, 600));

    m_window.draw(lines_text);

    // STATS - LINES BOX
    sf::RectangleShape lines(sf::Vector2f(150, 50));
    lines.setPosition(sf::Vector2f(50, 640));
    lines.setFillColor(sf::Color::Black);
    lines.setOutlineColor(sf::Color::Cyan);
    lines.setOutlineThickness(2);

    m_window.draw(lines);

    // STATS - LINES VALUE
    sf::Text lines_value(std::to_string(m_lines), m_font);
    lines_value.setPosition(sf::Vector2f(110, 645));

    m_window.draw(lines_value);
}

//FIXME Currently gets redefined every game loop, despite being mostly static (next will change)
void Game::drawRightSideArea() {
    //FIXME Use variables/constants instead of 250, 800;
    sf::RectangleShape right_side_area(sf::Vector2f(250, 800));
    right_side_area.setFillColor(sf::Color::Black);
    right_side_area.setPosition(sf::Vector2f(650, 0));
    
    m_window.draw(right_side_area);

    // NEXT BIG BOX
    sf::RectangleShape next(sf::Vector2f(200, 350));
    next.setFillColor(sf::Color::Black);
    next.setOutlineColor(sf::Color::Cyan);
    next.setOutlineThickness(2);
    next.setPosition(sf::Vector2f(675, 50));

    m_window.draw(next);

    // NEXT TEXT
    sf::Text next_text("Next", m_font);
    next_text.setPosition(sf::Vector2f(735, 50));

    m_window.draw(next_text);

    int offset = 0;

    for(TetrisShape& shape: m_next_shapes) {
        for(int i = 0; i < shape.m_cubes.size(); i++) {
            shape.m_cubes[i].setPosition(sf::Vector2f(750 + (shape.m_offsets[i].x)*40, offset+120+(shape.m_offsets[i].y)*40));
        }
        shape.draw(m_window);
        offset += 100;
    }

    // NEXT SMALL BOX
    // sf::RectangleShape next_small(sf::Vector2f(150, 285));
    // next_small.setPosition(sf::Vector2f(700, 90));
    // next_small.setFillColor(sf::Color::Black);
    // next_small.setOutlineColor(sf::Color::Cyan);
    // next_small.setOutlineThickness(2);

    // window.draw(next_small);

}

//FIXME Currently gets redefined every game loop, despite being completely static
void Game::drawGrid() {
    for(int i = 1; i < m_grid_size.y; i++) {
        sf::RectangleShape line(sf::Vector2f(400, 0.5f));
        line.setPosition(sf::Vector2f(250, i*800/m_grid_size.y));
        line.setFillColor(sf::Color(42, 42, 42));

        m_window.draw(line);
    }

    for(int i = 1; i < m_grid_size.x; i++) {
        sf::RectangleShape line(sf::Vector2f(1, 800));
        line.setPosition(sf::Vector2f(250+i*400/m_grid_size.x, 0));
        line.setFillColor(sf::Color(42, 42, 42));

        m_window.draw(line);
    }
}

//FIXME Currently gets redefined every game loop, despite being completely static
void Game::drawGameArea() {
    sf::RectangleShape game_area(sf::Vector2f(400, 800));
    game_area.setFillColor(sf::Color::Black);
    game_area.setOutlineColor(sf::Color::White);
    game_area.setOutlineThickness(3);
    game_area.setPosition(sf::Vector2f(250, 0));

    m_window.draw(game_area);
}

void Game::moveRowsDown(std::vector<int> cleared_rows) {
    for(int i = 0; i < cleared_rows.size(); i++) {
        cleared_rows[i] += i;
        for(int row = cleared_rows[i]; row > 0; row--) {
            std::cout << "MOVING ROW " << row << "\n";
            m_placed_shapes[row] = m_placed_shapes[row-1];
            for(sf::RectangleShape& shape: m_placed_shapes[row]) {
                sf::Vector2f cur_pos = shape.getPosition();
                cur_pos.y += 40;

                shape.setPosition(cur_pos);
            }
        }
    }
}

int Game::clearRows(sf::Vector2i row_span) {
    int amount_cleared_rows = 0;
    
    std::vector<int> cleared_rows;

    for(int row = row_span.y; row >= row_span.x; row--) {
        bool skip_clear = false;
        for(const sf::RectangleShape& shape: m_placed_shapes[row]) {
            sf::Vector2f cur_size = shape.getSize();

            if(cur_size.x != 40 && cur_size.y != 40)
                skip_clear = true;
        }

        //If the row wasnt cleared, continue
        if(skip_clear)
            continue;

        //Row was cleared, so clear the current row
        for(int col = 0; col < m_placed_shapes[row].size(); col++) {
            m_placed_shapes[row][col] = sf::RectangleShape();
        }

        amount_cleared_rows++;
        cleared_rows.push_back(row);
    }

    if(amount_cleared_rows) {
        moveRowsDown(cleared_rows);
        int multiplier = 100;
        if(amount_cleared_rows == 2)
            multiplier = 300;
        if(amount_cleared_rows == 3)
            multiplier = 500;
        if(amount_cleared_rows == 4)
            multiplier = 800;

        m_score += multiplier * amount_cleared_rows;
    }

    m_lines += amount_cleared_rows;

    m_level = 1 + m_lines / 10;

    return amount_cleared_rows;
}

void Game::calculateFallSpeed() {

}


//SCORE:
// https://tetris.wiki/Scoring

//LEVEL:
//LEVEL UP ONCE EVERY 10 LINES

//SPEED:
//https://harddrop.com/wiki/Tetris_Worlds

void Game::runGame() {
    m_sounds.playTheme();

    while(m_window.isOpen())
    {
        sf::Event event;
        while(m_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && !m_switched_block) {
            m_switched_block = true;

            //TODO before storing the current shape in held shape we want to reset its position and rotation

            //If we are currently holding a shape;
            if(m_held_shape.has_value()) {
                TetrisShape temp_shape = m_current_shape;
                m_current_shape = m_held_shape.value();
                m_held_shape = temp_shape;
            } else {
                m_held_shape = m_current_shape;
                m_current_shape = m_next_shapes.front();
                m_next_shapes.erase(m_next_shapes.begin());
                m_next_shapes.push_back(TetrisShape::generateRandomShape(m_start_coordinates));
            }
        }

        //FIXME Compare isKeyPressed to the KeyPressed event type
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_clock_rotate.getElapsedTime().asMilliseconds() >= 200) {
            m_current_shape.rotate(m_placed_shapes);
            m_clock_rotate.restart();
            m_sounds.playMoveSound();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_clock_x.getElapsedTime().asMilliseconds() >= 75 && m_current_shape.canMoveLeft(m_placed_shapes)) {
            m_current_shape.moveLeft();
            m_clock_x.restart();
            m_sounds.playMoveSound();
        } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_clock_x.getElapsedTime().asMilliseconds() >= 75 && m_current_shape.canMoveRight(m_placed_shapes)) {
            m_current_shape.moveRight();
            m_clock_x.restart();
            m_sounds.playMoveSound();
        }


        //TODO Implement the calculateFallSpeed() function
        int speed_up = 1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            speed_up = 20;
        } else {
            speed_up = 1;
        }


        if(m_clock_y.getElapsedTime().asMilliseconds() >= 1000 * std::pow(0.8-((m_level-1)*0.007), m_level-1) / speed_up) {
            std::cout << 1000 * std::pow(0.8-((m_level-1)*0.007), m_level-1) / speed_up << "\n";
            if(m_current_shape.canMoveDown(m_placed_shapes)) {
                m_current_shape.moveDown();
                
                //FIXME 
                if(speed_up == 20)
                    m_score += 1;
            } else {
                sf::Vector2i row_span = m_current_shape.place(m_placed_shapes);
                m_current_shape = m_next_shapes.front();
                m_next_shapes.erase(m_next_shapes.begin());
                m_next_shapes.push_back(TetrisShape::generateRandomShape(m_start_coordinates));
        
                m_switched_block = false;

                //TODO Something gotta happen when its game over
                if(!m_current_shape.canMove(m_placed_shapes, 0, 0))
                    std::cout << "GAME OVER!!" << "\n";

                if(clearRows(row_span))
                    m_sounds.playLineClearSound();
            }

            m_clock_y.restart();
        }

        m_window.clear();

        drawLeftSideArea();
        drawRightSideArea();

        drawGameArea();

        m_current_shape.update();
        m_current_shape.draw(m_window);

        //TODO Make a function for this?
        for(const auto& v: m_placed_shapes) {
            for(const auto& r: v) {
                m_window.draw(r);
            }
        }

        // DRAW GRID
        drawGrid();

        // std::cout << std::pow(0.8-((m_level-1)*0.007), m_level-1) << "\n";

        m_window.display();
    }
}