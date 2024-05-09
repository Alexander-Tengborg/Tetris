#include "TetrisShape.h"

//TODO Tetromino is the real name for a TetrisShape consisting of 4 blocks
//TODO blocks instead of cubes/rects
TetrisShape::TetrisShape(sf::Vector2f start, std::vector<sf::Vector2f> offsets, sf::Color color, bool can_rotate) {
    m_grid_coord = start;

    m_offsets = offsets;
    m_cubes = std::vector<sf::RectangleShape>();

    m_can_rotate = can_rotate;

    for(const sf::Vector2f& offset: offsets) {
        sf::RectangleShape rect(sf::Vector2f(40, 40));
        rect.setPosition(sf::Vector2f(250 + (m_grid_coord.x+offset.x)*40, (m_grid_coord.y+offset.y)*40));
        rect.setFillColor(color);

        m_cubes.push_back(rect);
    }

    calculateBounds();
}

void TetrisShape::draw(sf::RenderWindow& window) {
    for(const sf::RectangleShape& rect: m_cubes) {
        window.draw(rect);
    }
}

void TetrisShape::update() {
    for(int i = 0; i < m_cubes.size(); i++) {
        sf::Vector2f offset = m_offsets[i];

        m_cubes[i].setPosition(sf::Vector2f(250 + (m_grid_coord.x+offset.x)*40, (m_grid_coord.y+offset.y)*40));
    }
}

void TetrisShape::calculateBounds() {
    sf::Vector2f min_bounds(INT_MAX, INT_MAX);
    sf::Vector2f max_bounds(INT_MIN, INT_MIN);

    for(const sf::Vector2f& offset: m_offsets) {
        min_bounds.x = std::min(min_bounds.x, offset.x);
        min_bounds.y = std::min(min_bounds.y, offset.y);

        max_bounds.x = std::max(max_bounds.x, offset.x);
        max_bounds.y = std::max(max_bounds.y, offset.y);
    }

    m_min_bounds = min_bounds;
    m_max_bounds = max_bounds;
}

bool TetrisShape::canMoveLeft() {
    return m_grid_coord.x + m_min_bounds.x > 0;
}

void TetrisShape::moveLeft() {
    if(!canMoveLeft())
        return;

    m_grid_coord.x -= 1;
}

bool TetrisShape::canMoveRight() {
    return m_grid_coord.x + m_max_bounds.x < 10 - 1; //TODO 10=grid_cols, change this
}

void TetrisShape::moveRight() {
    if(!canMoveRight())
        return;

    m_grid_coord.x += 1;
}

bool TetrisShape::canMoveDown(std::vector<std::vector<sf::RectangleShape>>& placed_shapes) {
    if(m_grid_coord.y + m_max_bounds.y >= 20 - 1) //FIXME 20=grid_rows, change this
        return false;
    
    for(const auto& offset: m_offsets) {
        int row = m_grid_coord.y + offset.y + 1;
        int col = m_grid_coord.x + offset.x;

        //FIXME Find a better way to check if a placed_shape exists for the given row and col
        //Since all of our placed shapes are 40x40...
        sf::Vector2f cur_size = placed_shapes[row][col].getSize();
        if(cur_size.x != 0 && cur_size.y != 0)
            return false;
    }

    return true;
}

void TetrisShape::moveDown() {
    // if(!canMoveDown(std::vector<std::vector<sf::RectangleShape>>& placed_shapes))
        // return;

    m_grid_coord.y += 1;
}

void TetrisShape::rotateCube(sf::Vector2f& offset) {
    double x = offset.x * std::cos(M_PI / 2) - offset.y * std::sin(M_PI / 2);
    double y = offset.x * std::sin(M_PI / 2) + offset.y * std::cos(M_PI / 2);

    std::cout << "Before: " << offset.x << ", after: " << x << "\n";
    offset.x = x;
    offset.y = y;
}

//Use rotation matrix to turn the shapes
//Since our y-axis is flipped when compared to normal graphs (-y goes up and y goes down)
//If we want to rotate clockwise we what normally would be a counter clockwise rotation
//So if we want to rotate 90 deg clockwise, we have to calculate it like we want to rotate 90 deg counter clockwise
void TetrisShape::rotate() {
    if(!m_can_rotate)
        return;

    for(sf::Vector2f& offset: m_offsets) {
        rotateCube(offset);
    }

    calculateBounds();
}

void TetrisShape::place(std::vector<std::vector<sf::RectangleShape>>& placed_shapes) {
    for(int i = 0; i < m_cubes.size(); i++) {
        int row = m_grid_coord.y + m_offsets[i].y;
        int col = m_grid_coord.x + m_offsets[i].x;

        placed_shapes[row][col] = m_cubes[i];
    }
}

TetrisShape TetrisShape::generateRandomShape(sf::Vector2f grid_coord) {
    srand(time(NULL));
    int i = rand() % TetrisShape::shapes.size();

    bool can_rotate = true;

    if(i == 3)
        can_rotate = false;

    return TetrisShape(grid_coord, TetrisShape::shapes[i].first, TetrisShape::shapes[i].second, can_rotate);
    // return TetrisShape(grid_coord, {sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(0, -1)});
    // return TetrisShape(grid_coord, {sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(2, 0), sf::Vector2f(3, 0)});
}

const std::array<std::pair<std::vector<sf::Vector2f>, sf::Color>, 7> TetrisShape::shapes = {
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-2, 0), sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0)}), sf::Color::Cyan), // I
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(-1, -1)}), sf::Color::Blue), // L
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(1, -1)}), sf::Color(255, 165, 0)), // J
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(1, -1), sf::Vector2f(0, -1)}), sf::Color::Yellow), // O
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(0, -1), sf::Vector2f(1, -1)}), sf::Color::Green), // S
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(0, -1)}), sf::Color::Magenta), // T
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, -1), sf::Vector2f(0, 0), sf::Vector2f(0, -1), sf::Vector2f(1, 0)}), sf::Color::Red), // Z
};