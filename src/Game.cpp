#include "Game.h"

Game::Game() {
    m_window = std::make_shared<sf::RenderWindow>(sf::VideoMode(m_window_size.x, m_window_size.y), "Tetris!");

    //UNUSED
    // if(!m_texture.loadFromFile("../resources/textures/red.png"))
    //     std::cout << "FAILED TO LOAD RED.PNG D:" << "\n";    

    m_switched_block = false;

    std::cout << "Ui Loading" << "\n";
    m_ui = std::make_unique<Ui>(m_window, m_grid_size);
    std::cout << "Ui Loaded" << "\n";

    //FIXME fix this so it can return properly  
    if(!m_sounds.loadSounds())
        return;

    m_current_shape = TetrisShape::generateRandomShape(m_start_coordinates);
    for(int i = 0; i < 3; i++)
        m_next_shapes.push_back(TetrisShape::generateRandomShape(m_start_coordinates));

    m_placed_shapes.resize(m_grid_size.y, std::vector<sf::RectangleShape>(m_grid_size.x));
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

    while(m_window->isOpen())
    {
        sf::Event event;
        while(m_window->pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                m_window->close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C) && !m_switched_block) {
            m_switched_block = true;

            //TODO before storing the current shape in held shape we want to reset its position and rotation
            m_current_shape.reset(m_start_coordinates);

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

        m_window->clear();

    // std::cout << "Running 1" << "\n";

    // std::cout << &m_window << "\n";

        m_ui->drawStaticSideAreas();

    // std::cout << "Running 2" << "\n";
        m_ui->drawNextShapes(m_next_shapes);
        
        if(m_held_shape.has_value())
            m_ui->drawHeldShape(m_held_shape.value());
        
        m_ui->drawStats(m_score, m_level, m_lines);

        m_ui->drawGameArea();

        m_current_shape.update();
        m_current_shape.draw(m_window);

        //TODO Make a function for this?
        for(const auto& v: m_placed_shapes) {
            for(const auto& r: v) {
                m_window->draw(r);
            }
        }

        // DRAW GRID
        m_ui->drawGrid();


        // std::cout << std::pow(0.8-((m_level-1)*0.007), m_level-1) << "\n";

        m_window->display();
    }
}