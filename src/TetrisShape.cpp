#include "TetrisShape.h"

//In the Game class TetrisShape is used as a member variable, and this constructor is called as the variable is defined.
//In the Game class constructor it initializes TetrisShape with the other instructor, so this constructor is basically a placeholder
//Need to fix this somehow, possibly by having the member variable in TetrisShape be a pointer or std::optional instead.
TetrisShape::TetrisShape() {

}

//TODO Tetromino is the real name for a TetrisShape consisting of 4 blocks
//TODO blocks instead of cubes/rects
TetrisShape::TetrisShape(sf::Vector2f start, std::vector<sf::Vector2f> offsets, sf::Color color, bool can_rotate)
    : m_grid_coord(start), m_offsets(offsets), m_original_offsets(offsets), m_can_rotate(can_rotate) {

    m_cubes = std::vector<sf::RectangleShape>();

    for(const sf::Vector2f& offset: offsets) {
        sf::RectangleShape rect(sf::Vector2f(40, 40));
        rect.setPosition(sf::Vector2f(250 + (m_grid_coord.x+offset.x)*40, (m_grid_coord.y+offset.y)*40));
        rect.setFillColor(color);
        m_cubes.push_back(rect);
    }

}

sf::Vector2i TetrisShape::calculateXBounds() {
    sf::Vector2i x_bounds(INT_MAX, INT_MIN);

    for(const sf::Vector2f& offset: m_offsets) {
        x_bounds.x = std::min(x_bounds.x, (int) offset.x);
        x_bounds.y = std::max(x_bounds.y, (int) offset.x);
    }

    return x_bounds;
}

void TetrisShape::reset(sf::Vector2f start) {
    m_grid_coord = start;
    m_offsets = m_original_offsets;
}

void TetrisShape::draw(std::shared_ptr<sf::RenderWindow> window) {
    for(const sf::RectangleShape& rect: m_cubes) {
        window->draw(rect);
    }
}

void TetrisShape::update() {
    for(int i = 0; i < m_cubes.size(); i++) {
        sf::Vector2f offset = m_offsets[i];

        m_cubes[i].setPosition(sf::Vector2f(250 + (m_grid_coord.x+offset.x)*40, (m_grid_coord.y+offset.y)*40));
    }
}

bool TetrisShape::canMoveLeft(std::vector<std::vector<sf::RectangleShape>>& placed_shapes) {
    return canMove(placed_shapes, -1, 0);
}

void TetrisShape::moveLeft() {
    m_grid_coord.x -= 1;
}

bool TetrisShape::canMoveRight(std::vector<std::vector<sf::RectangleShape>>& placed_shapes) {
    return canMove(placed_shapes, 1, 0);
}

void TetrisShape::moveRight() {
    m_grid_coord.x += 1;
}

bool TetrisShape::canMoveDown(std::vector<std::vector<sf::RectangleShape>>& placed_shapes) {
    return canMove(placed_shapes, 0, 1);
}

void TetrisShape::moveDown() {
    m_grid_coord.y += 1;
}

bool TetrisShape::canMove(std::vector<std::vector<sf::RectangleShape>>& placed_shapes, int x_dir, int y_dir, std::vector<sf::Vector2f> offsets) {
    if(offsets.size() == 0)
        offsets = m_offsets;
    
    for(const auto& offset: offsets) {
        int row = m_grid_coord.y + offset.y + y_dir;
        int col = m_grid_coord.x + offset.x + x_dir;

        // Out of bounds
        if(row < 0 || col < 0 || row >= placed_shapes.size() || col >= placed_shapes[0].size())
            return false;

        //FIXME Find a better way to check if a placed_shape exists for the given row and col
        //Since all of our placed shapes are 40x40...
        sf::Vector2f cur_size = placed_shapes[row][col].getSize();
        if(cur_size.x == 40 && cur_size.y == 40)
            return false;
    }

    return true;
}

//Use rotation matrix to turn the shapes
//Since our y-axis is flipped when compared to normal graphs (-y goes up and y goes down)
//If we want to rotate clockwise we what normally would be a counter clockwise rotation
//So if we want to rotate 90 deg clockwise, we have to calculate it like we want to rotate 90 deg counter clockwise
std::vector<sf::Vector2f> TetrisShape::calculateRotatedCubeOffsets() {
    std::vector<sf::Vector2f> offsets;

    for(sf::Vector2f& offset: m_offsets) {
        double x = offset.x * std::cos(M_PI / 2) - offset.y * std::sin(M_PI / 2);
        double y = offset.x * std::sin(M_PI / 2) + offset.y * std::cos(M_PI / 2);
        offsets.push_back(sf::Vector2f(x, y));
    }

    return offsets;
}

void TetrisShape::rotate(std::vector<std::vector<sf::RectangleShape>>& placed_shapes) {
    if(!m_can_rotate)
        return;

    std::vector<sf::Vector2f> offsets = calculateRotatedCubeOffsets();

    std::vector<std::pair<int, int>> move_directions({{0, 0}, {1, 0}, {-1, 0}, {2, 0}, {-2, 0}, {0, 1}});

    //If the shape cannot be rotated without going out of bounds or colliding with another shape,
    //It tries to move once to the right, once to the left, twice to the right and twice to the left (AND ONCE DOWN).
    //If any of these moves are possible without going out of bounds or colloding, the shape will be rotated.
    //Otherwise, the shape wont be rotated
    for(const std::pair<int, int>& dirs: move_directions) {
        if(canMove(placed_shapes, dirs.first, dirs.second, offsets)) {
            m_offsets = offsets;
            m_grid_coord.x += dirs.first;
            m_grid_coord.y += dirs.second;
            return;
        }
    }

    std::cout << "Could not rotate :(((" << "\n";

    // calculateBounds();
}

//Returns the highest and lowest rows of the placed shaped so we then have to check as few rows as possible
sf::Vector2i TetrisShape::place(std::vector<std::vector<sf::RectangleShape>>& placed_shapes) {
    sf::Vector2i row_span(INT_MAX, INT_MIN);

    for(int i = 0; i < m_cubes.size(); i++) {
        int row = m_grid_coord.y + m_offsets[i].y;
        int col = m_grid_coord.x + m_offsets[i].x;

        std::cout << "row: " << row_span.x << " " << row << "\n";

        //FIXME row_span.x/y are floats, row is int. Convert them to the same type in a better way
        row_span.x = std::min(row_span.x, row);
        row_span.y = std::max(row_span.y, row);

        placed_shapes[row][col] = m_cubes[i];
    }

    return row_span;
}

//Unused for now
void TetrisShape::setTexture(sf::Texture& texture) {
    for(auto& r: m_cubes) {
        r.setTexture(&texture);
    }
}

TetrisShape TetrisShape::generateRandomShape(sf::Vector2f grid_coord) {

    int i = rand() % TetrisShape::shapes.size();

    bool can_rotate = true;

    //TODO dont want the square/O to be able to rotate. Is there a cleaner way to do this?
    if(i == 3)
        can_rotate = false;

    return TetrisShape(grid_coord, TetrisShape::shapes[i].first, TetrisShape::shapes[i].second, can_rotate);
}

//Add enum for all types? 
//TODO this feels dirty
const std::array<std::pair<std::vector<sf::Vector2f>, sf::Color>, 7> TetrisShape::shapes = {
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-2, 0), sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0)}), sf::Color::Cyan), // I
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(-1, -1)}), sf::Color::Blue), // L
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(1, -1)}), sf::Color(255, 165, 0)), // J
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(1, -1), sf::Vector2f(0, -1)}), sf::Color::Yellow), // O
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(0, -1), sf::Vector2f(1, -1)}), sf::Color::Green), // S
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, 0), sf::Vector2f(0, 0), sf::Vector2f(1, 0), sf::Vector2f(0, -1)}), sf::Color::Magenta), // T
    std::make_pair(std::vector<sf::Vector2f>({sf::Vector2f(-1, -1), sf::Vector2f(0, 0), sf::Vector2f(0, -1), sf::Vector2f(1, 0)}), sf::Color::Red), // Z
};