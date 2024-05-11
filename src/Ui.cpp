#include "Ui.h"

Ui::Ui(std::shared_ptr<sf::RenderWindow> window, sf::Vector2i grid_size) {
    m_window = window;

    if(!m_font.loadFromFile("../resources/fonts/Roboto-Regular.ttf")) {
        std::cout << "Failed to load file Roboto-Regular.ttf" << "\n";
        m_window->close();
    }

    createStaticLeftSideArea();
    createStaticRightSideArea();
    createStaticGrid(grid_size);
    createGameArea();
}

void Ui::createStaticLeftSideArea() {
    sf::RectangleShape left_side_area(sf::Vector2f(250, 800));
    left_side_area.setFillColor(sf::Color::Black);
    left_side_area.setPosition(0, 0);
    
    m_ui_rects.push_back(left_side_area);

    // HOLD BIG BOX
    sf::RectangleShape hold(sf::Vector2f(200, 185));
    hold.setFillColor(sf::Color::Black);
    hold.setOutlineColor(sf::Color::Cyan);
    hold.setOutlineThickness(2);
    hold.setPosition(25, 50);

    m_ui_rects.push_back(hold);

    // HOLD TEXT
    sf::Text hold_text("Hold", m_font);

    int hold_text_x = 125 - hold_text.getLocalBounds().getSize().x / 2;
    hold_text.setPosition(hold_text_x, 50);

    m_ui_static_text.push_back(hold_text);

    // HOLD SMALL BOX
    // sf::RectangleShape hold_small(sf::Vector2f(150, 120));
    // hold_small.setPosition(50, 90);
    // hold_small.setFillColor(sf::Color::Black);
    // hold_small.setOutlineColor(sf::Color::Cyan);
    // hold_small.setOutlineThickness(2);

    // m_ui_rects.push_back(hold_small);

    // STATS 
    sf::RectangleShape stats(sf::Vector2f(200, 350));
    stats.setFillColor(sf::Color::Black);
    stats.setOutlineColor(sf::Color::Cyan);
    stats.setOutlineThickness(2);
    stats.setPosition(25, 400);

    m_ui_rects.push_back(stats);

    // STATS - SCORE TEXT, 125 is the center pos of the stats rect
    sf::Text score_text("Score", m_font);

    int score_text_x = 125 - score_text.getLocalBounds().getSize().x / 2;
    score_text.setPosition(score_text_x, 400);

    m_ui_static_text.push_back(score_text);

    // STATS - SCORE BOX
    sf::RectangleShape score(sf::Vector2f(150, 50));
    score.setPosition(50, 440);
    score.setFillColor(sf::Color::Black);
    score.setOutlineColor(sf::Color::Cyan);
    score.setOutlineThickness(2);

    m_ui_rects.push_back(score);

    // STATS - LEVEL TEXT
    sf::Text level_text("Level", m_font);

    int level_text_x = 125 - level_text.getLocalBounds().getSize().x / 2;
    level_text.setPosition(level_text_x, 500);

    m_ui_static_text.push_back(level_text);

    // STATS - LEVEL BOX
    sf::RectangleShape level(sf::Vector2f(150, 50));
    level.setPosition(50, 540);
    level.setFillColor(sf::Color::Black);
    level.setOutlineColor(sf::Color::Cyan);
    level.setOutlineThickness(2);

    m_ui_rects.push_back(level);

    // STATS - LINES TEXT
    sf::Text lines_text("Lines", m_font);

    int lines_text_x = 125 - lines_text.getLocalBounds().getSize().x / 2;
    lines_text.setPosition(lines_text_x, 600);

    m_ui_static_text.push_back(lines_text);

    // STATS - LINES BOX
    sf::RectangleShape lines(sf::Vector2f(150, 50));
    lines.setPosition(50, 640);
    lines.setFillColor(sf::Color::Black);
    lines.setOutlineColor(sf::Color::Cyan);
    lines.setOutlineThickness(2);

    m_ui_rects.push_back(lines);
}

void Ui::createStaticRightSideArea() {
    //FIXME Use variables/constants instead of 250, 800;
    sf::RectangleShape right_side_area(sf::Vector2f(250, 800));
    right_side_area.setFillColor(sf::Color::Black);
    right_side_area.setPosition(650, 0);
    
    m_ui_rects.push_back(right_side_area);

    // NEXT BIG BOX
    sf::RectangleShape next(sf::Vector2f(200, 360));
    next.setFillColor(sf::Color::Black);
    next.setOutlineColor(sf::Color::Cyan);
    next.setOutlineThickness(2);
    next.setPosition(675, 50);

    m_ui_rects.push_back(next);

    // NEXT TEXT
    sf::Text next_text("Next", m_font);

    int lines_text_x = 775 - next_text.getLocalBounds().getSize().x / 2;
    next_text.setPosition(lines_text_x, 50);

    m_ui_static_text.push_back(next_text);

    // NEXT SMALL BOX
    // sf::RectangleShape next_small(sf::Vector2f(150, 285));
    // next_small.setPosition(700, 90);
    // next_small.setFillColor(sf::Color::Black);
    // next_small.setOutlineColor(sf::Color::Cyan);
    // next_small.setOutlineThickness(2);

    // window.draw(next_small);
}

void Ui::createStaticGrid(sf::Vector2i grid_size) {
    sf::Color grid_color(42, 42, 42);

    for(int i = 1; i < grid_size.y; i++) {
        sf::RectangleShape line(sf::Vector2f(400, 1.0));
        line.setPosition(250, i * 800 / grid_size.y);
        line.setFillColor(grid_color);

        m_grid.push_back(line);
    }

    for(int i = 1; i < grid_size.x; i++) {
        sf::RectangleShape line(sf::Vector2f(1, 800));
        line.setPosition(250 + i * 400 / grid_size.x, 0);
        line.setFillColor(grid_color);

        m_grid.push_back(line);
    }
}

void Ui::createGameArea() {
    m_game_area = sf::RectangleShape(sf::Vector2f(400, 800));
    m_game_area.setFillColor(sf::Color::Black);
    m_game_area.setOutlineColor(sf::Color::White);
    m_game_area.setOutlineThickness(3);
    m_game_area.setPosition(250, 0);
}

void Ui::drawStaticSideAreas() {
    for(const sf::RectangleShape& rect: m_ui_rects) {
        m_window->draw(rect);
    }

    for(const sf::Text& text: m_ui_static_text) {
        m_window->draw(text);
    }
}

void Ui::drawGrid() {
    for(const sf::RectangleShape& grid_line: m_grid) {
        m_window->draw(grid_line);
    }
}

void Ui::drawGameArea() {
    m_window->draw(m_game_area);
}

void Ui::drawShape(std::unique_ptr<TetrisShape>& shape, int offset_x, int offset_y) {
    sf::Vector2i x_bounds = shape->calculateXBounds();

    if((x_bounds.y - x_bounds.x) % 2 == 0)
        offset_x += 20;
    else if((x_bounds.y - x_bounds.x) == 1)
        offset_x += 40;
    else if((x_bounds.y - x_bounds.x) == 3)
        offset_y -= 20;

    for(int i = 0; i < shape->m_cubes.size(); i++) {
        int x = offset_x + 85 - (x_bounds.x + x_bounds.y) * 40 + shape->m_offsets[i].x * 40;
        int y = offset_y + 185 / 2 + 60 + shape->m_offsets[i].y * 40;

        shape->m_cubes[i].setPosition(x, y);
    }
    shape->draw(m_window);
}

void Ui::drawNextShapes(std::vector<std::unique_ptr<TetrisShape>>& next_shapes) {
    int offset_y = 0;

    for(std::unique_ptr<TetrisShape>& shape: next_shapes) {
        drawShape(shape, 650, offset_y);

        offset_y += 100;
    }
}

void Ui::drawStats(int score, int level, int lines) {
    // STATS - SCORE VALUE
    sf::Text score_value(std::to_string(score), m_font);
    int score_text_x = 125 - score_value.getLocalBounds().getSize().x / 2;
    score_value.setPosition(score_text_x, 445);
    m_window->draw(score_value);

    // STATS - LEVEL VALUE
    sf::Text level_value(std::to_string(level), m_font);
    int level_text_x = 125 - level_value.getLocalBounds().getSize().x / 2;
    level_value.setPosition(level_text_x, 545);
    m_window->draw(level_value);

    // STATS - LINES VALUE
    sf::Text lines_value(std::to_string(lines), m_font);
    int lines_text_x = 125 - lines_value.getLocalBounds().getSize().x / 2;
    lines_value.setPosition(lines_text_x, 645);
    m_window->draw(lines_value);
}