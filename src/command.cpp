// ANDREA PADOVAN, mat. 2043450

#include "command.h"

bool contains(std::string, char);
int index_of(std::string, char);


Command::Command(std::string cmd) {
    if (!(is_valid(cmd))) throw InvalidCommandException("Comando non valido.");
    command_ = cmd;
}
Command::Command(Position p1, Position p2) :
    Command(p1.to_string() + " " + p2.to_string()) {}


bool Command::is_special_command() const {
    return is_special(command_);
}
std::array<Position, 2> Command::get_command_positions() const {
    return get_positions(command_);
}


bool Command::is_valid(std::string cmd) {
    if (is_special(cmd)) return true;

    try { get_positions(cmd); }
    catch (InvalidCommandException e) { return false; }
    return true;
}
bool Command::is_special(std::string cmd) {
    return cmd == "XX XX" || cmd == "AA AA";
}
std::array<Position, 2> Command::get_positions(std::string cmd) { 
    if (is_special(cmd) || !(contains(cmd, ' '))) throw InvalidCommandException("Comando non valido.");
    
    Position pos1;
    Position pos2;

    int whitespace_index = index_of(cmd, ' ');
    try {
        pos1 = Position(cmd.substr(0, whitespace_index)); // can throw InvalidPositionException (so intended)
        pos2 = Position(cmd.substr(whitespace_index + 1)); 

    } catch (Position::InvalidPositionException e) {
        throw InvalidCommandException("Comando non valido.");
    }
    return std::array<Position, 2> {pos1, pos2};
}

bool contains(std::string s, char c) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) return true;
    }
    return false;
}
int index_of(std::string s, char c) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == c) return i;
    }
    return -1;
}