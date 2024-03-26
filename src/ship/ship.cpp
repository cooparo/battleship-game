// PAOLO CONTI, mat. 2032506

#include <vector>
#include "ship/ship.h"

bool Ship::is_vertical(Position a, Position b) {
    // Compares two positions, es. (A2, A6) o (D5, F5); there are no "diagonal" ships.
    if (a.x() == b.x()) return true;
    else return false;
};

std::vector<Position> Ship::get_ship_positions() const {
    std::vector<Position> pos;

    // Checks if the ship hasn't been placed yet and has a default position.
    if (position_.is_default_position()) return pos;

    // Gets x and y of the current position, and then gets the distance of the external points from the middle of the ship.
    int x = position_.x();
    char y = position_.y();
    int half_size = size_ / 2;

    // Checks if the ship is vertical or horizontal and then adds all the position to the vector.
    if (is_vertical_) {
        for (int z = y - half_size;  z <= y + half_size;  z++) {
            pos.push_back(Position(x, z));
        }
    } else {
        for (int z = x - half_size;  z <= x + half_size;  z++) {
            pos.push_back(Position(z, y));
        }
    }

    // Returns the list of the ship's positions.
    return pos;
}