// LUCA PAROLINI, mat. 2041811

#include "grid/defense_grid.h"
#include "ship/battleship.h"
#include "ship/support_ship.h"
#include "ship/submarine.h"
#include "command.h"
#include "constant.h"

DefenseGrid::DefenseGrid() : ships_{
    std::make_unique<Battleship>(),
    std::make_unique<Battleship>(),
    std::make_unique<Battleship>(),
    std::make_unique<SupportShip>(),
    std::make_unique<SupportShip>(),
    std::make_unique<SupportShip>(),
    std::make_unique<Submarine>(),
    std::make_unique<Submarine>()
} {}

void DefenseGrid::move(Ship* ship_ptr, Position pos) {
    for (int i = 0; i < kDefaultShipNumber; i++) {
        if (ships_[i].get() == ship_ptr) return move(i, pos);
    }
}

void DefenseGrid::move(int index, Position pos, bool is_vertical) {
    Ship &ship = *ships_.at(index);
    ship.set_vertical(is_vertical);
    move(index, pos); // e poi chiami l'altro move qui
}

void DefenseGrid::move(int index, Position pos) { 
    Ship &ship = *(ships_[index]); 
    int ship_size = ship.size();
    bool is_vertical = ship.is_vertical();

    std::vector<Position> positions = ship.get_ship_positions();
    Position ex_pos = ship.position();

    // Erase old grid positions
    for(int i = 0; i < positions.size(); i++) {
        Position p = positions[i];
        this->at(p) = ' ';
    }
    ship.set_position(Position()); // Set temp position

    // Checks if the cells are empty
    if(this->check_free_position(pos, index)) { 
        
        // Update ship pos
        ship.set_position(pos);
        positions = ship.get_ship_positions();

        // Update grid positions
        for(int i = 0; i < positions.size(); i++) {
            Position p = positions[i];
            this->at(p) = index + '0';
        }
    } else {
        // Restore old grid positions
        for(int i = 0; i < positions.size(); i++) {
            Position p = positions[i];
            this->at(p) = index + '0';
        }
        ship.set_position(ex_pos); // Restore temp position
        throw Command::InvalidCommandException("Posizione occupata.");
    }
}

bool DefenseGrid::check_free_position(Position pos, int index) {
    bool res = true;
    Ship& ship = *(ships_[index]); 
    int ship_size = ship.size();
    bool is_vertical = ship.is_vertical();

    int x = pos.x();
    char y = pos.y();

    if(is_vertical) {   // Vertical case
        // Offset
        y -= (ship_size - 1) / 2;

        for(int i = y; i < y + ship_size; i++) {
            if (i < 'A' || i > 'L') { res = false; break; }
            if(this->ships_in(Position(pos.x(), i)).size() != 0) res = false;
        }
    } else {            // Horizontal case
        
        // Offset
        x -= (ship_size - 1) / 2;

        for(int i = x; i < x + ship_size; i++) {
            if (i < 1 || i > 12) { res = false; break; }
            if(this->ships_in(Position(i, pos.y())).size() != 0) res = false;
        }
    }
    
    return res;
}

std::vector<Ship*> DefenseGrid::ships_in(Position pos) const {
    std::vector<Ship*> res;
    int index = this->at(pos) - '0';
    if(index >= 0 && index <= 7) res.push_back(ships_.at(index).get());
    return res;
}

// square_side has to be an ODD integer
std::vector<Ship*> DefenseGrid::ships_in(Position pos, int square_side) const {
    std::vector<Ship*> res;

    // Offset for start searching in from the top-left corner,
    int offset = (square_side - 1) / 2;
    int x = pos.x_grid_coord() - offset;
    int y = pos.y_grid_coord() - offset;

    // Check all the area
    for(int i = y; i < y + square_side; i++) {
        if (i < 0 || i > 11) continue;
        for(int j = x; j < x + square_side; j++) {
            if (j < 0 || j > 11) continue;
            int index = grid().at(j).at(i) - '0';
            if(index >= 0 && index <= 7) res.push_back(ships_[index].get());
        }
    }
    return res;
}

Grid DefenseGrid::get_base_grid() const {
    Grid grid = static_cast<Grid>(*this);

    for (int i = 0; i < ships().size(); i++) {
        const Ship& ship = *(ships()[i]);
        std::vector<Position> ship_positions = ship.get_ship_positions();

        for (int j = 0; j < ship_positions.size(); j++) {
            char& c = grid.at(ship_positions[j]);
            if(c >= '0' && c <= '2') j < ship.armor() ? c = 'C' : c = 'c';
            else if(c >= '3' && c <= '5') j < ship.armor() ? c = 'S' : c = 's';
            else if(c >= '6' && c <= '7') j < ship.armor() ? c = 'E' : c = 'e';
        }
    }
    return grid;
}

std::ostream& operator<<(std::ostream& os, DefenseGrid& def_grid) {
    // Conversion to base class Grid to benefit of the already written
    // std::ostream& operator<<(std::ostream& os, Grid& grid)
    Grid grid = def_grid.get_base_grid();
    return os << grid;
}
