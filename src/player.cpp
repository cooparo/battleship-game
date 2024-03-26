// ANDREA PADOVAN, mat. 2043450

#include "player.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <thread>

using std::cout;
using std::endl;
using std::cin;

// PLAYER

void Player::execute(Command command, Player& target) {
    const std::array<Position, 2> positions = command.get_command_positions();
    std::vector<Ship*> ships = grids_.defense_grid().ships_in(positions.at(0));
    if (ships.size() == 0) throw Command::InvalidCommandException("Nessuna nave nella prima posizione data.");
    ships.at(0)->action(positions.at(1), grids_, target.grids_);
}

void Player::set_ship_position(Command cmd, int target_index) {
    if (target_index < 0 || target_index > 8)
        throw std::runtime_error("Invalid target_index.");

    DefenseGrid& defense_grid = grids().defense_grid();
    const Ship& ship = *(defense_grid.ships().at(target_index));

    std::array<Position, 2> positions = cmd.get_command_positions();

    bool is_vertical = positions[0].x() == positions[1].x();
    bool is_horizontal = positions[0].y() == positions[1].y();

    if (!(is_vertical || is_horizontal))
        throw Command::InvalidCommandException("Puoi predisporre la nave in orizzontale o in verticale.");
    
    int delta_x = positions[1].x() - positions[0].x() + 1;
    int delta_y = positions[1].y() - positions[0].y() + 1;

    if ( !((ship.size() == delta_x) || (ship.size() == delta_y)) ) {
        throw Command::InvalidCommandException("La dimensione di questa nave dev'essere di " + std::to_string(ship.size()) + ".");
    }

    int x = (positions[0].x() + positions[1].x()) / 2;
    int y = (positions[0].y() + positions[1].y()) / 2;
    
    defense_grid.move(target_index, Position(x, y), is_vertical);
}

bool Player::has_ships() const {
    const std::array<std::unique_ptr<Ship>, 8>& ships = grids_.defense_grid().ships();
    for (int i = 0; i < ships.size(); i++) {
        if (ships[i]->armor() > 0) return true;
    }
    return false;
}

// --- Player end

// HUMAN

Command Human::get_move() {
    cout << "Giovane avventuriero, qual è la tua prossima mossa?" << endl;
    std::string cmd;
    std::getline(std::cin, cmd);
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
    return Command(cmd);
}

/**
 * @brief Gets the ship type by the dimension.
*/
std::string get_ship_type(int dimension) {
    if (dimension == 1)
        return "Submarine";
    else if (dimension == 3)
        return "Nave di supporto";
    else if (dimension == 5)
        return "Corazzata";
    throw std::runtime_error("Error in get_ship_type()!");
}

Command Human::get_ship_position(int target_index) {
    int dimension = grids().defense_grid().ships().at(target_index)->size();
    cout << endl << "Dove vuoi posizionare '" << get_ship_type(dimension) << " " << target_index % 3 + 1 << "'?" << endl;
    std::string cmd;
    std::getline(std::cin, cmd);
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper); //To uppercase
    return Command(cmd);
}

void Human::notice_invalid_command(std::string message) const {
    cout << message << " Riprova!" << endl;
}

void Human::print_grids() const {
    cout << endl << grids() << endl << endl;
}

// --- Human end

// COMPUTER

char r_letter(char up_limit = 'L');
int r_number(int up_limit = 12);
Position r_position();
Position r_position(int x_limit, char y_limit);

Command Computer::get_move() {
    const Ship& r_ship = *(grids().defense_grid().ships().at(std::rand() % 8));
    return Command(r_ship.position(), r_position());
}

Command Computer::get_ship_position(int target_index) {

    int dimension = grids().defense_grid().ships().at(target_index)->size();
    bool is_vertical = std::rand() % 2;  // OPTIMIZE: implicit conversion

    Position first_pos = is_vertical
        ? r_position(12 - dimension, 'L')
        : r_position(12, 'L' - dimension);

    Position second_pos = is_vertical
        ? Position(first_pos.x() + dimension - 1, first_pos.y())
        : Position(first_pos.x(), first_pos.y() + dimension - 1);
    
    return Command(first_pos, second_pos);
}


// Random Position
Position r_position() {
    return Position(r_number(), r_letter());
}
Position r_position(int x_limit, char y_limit) {
    return Position(r_number(x_limit), r_letter(y_limit));
}

// Random Uppercase Letter, range 'A' - 'L'
char r_letter(char up_limit) { // OPTIMIZE: here a lot of implicit conversions. Is it ok?
    if (up_limit < 'A' || up_limit > 'L') throw std::runtime_error("Invalid up_limit in r_letter()");
    char r = std::rand() % (up_limit + 1 - 'A') + 'A';
    return r; // 12 cells
}
// Random Number, range 1 - 12
int r_number(int up_limit) {
    return std::rand() % up_limit + 1; // 12 cells
}

// --- Computer end

// REPLAYER

Command Replayer::get_move() {
    std::string cmd = commands_.at(0);
    commands_.erase(commands_.begin());
    return Command(cmd);
};
Command Replayer::get_ship_position(int) {
    return get_move();
};

Command CoutReplayer::get_move() {
    print_grids();
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for 
    
    std::string cmd = commands_.at(0);
    commands_.erase(commands_.begin());
    return Command(cmd);
};

void CoutReplayer::print_grids() const {
    cout << name() << endl << grids() << endl << endl;
};

// --- Replayer end