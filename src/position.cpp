// ANDREA PADOVAN, mat. 2043450

#include "position.h"

Position::Position(std::string pos) {
    // EXAMPLE OF POSITION : C9 || B12
    
    // to avoid recalculations
    const int kPosLength = pos.length();

    // Checks if the string's length is correct.
    if (kPosLength < 2 || kPosLength > 3) 
        throw InvalidPositionException("Posizione non valida.");

    // Changes y to upper case.
    y_ = toupper(pos[0]);
    try { 
        // stoi: string to int
        x_ = std::stoi(pos.substr(1));
    } catch (std::invalid_argument) { throw InvalidPositionException("Posizione non valida."); }

    // Returns an exception with a message for the user if the position isn't valid.
    if (!(is_valid(x_, y_))) throw InvalidPositionException("Posizione non valida.");
}

Position::Position(int x, char y) : x_{x}, y_{y} {
    if (!(is_valid(x, y))) throw InvalidPositionException("Posizione non valida.");
}

std::string Position::to_string() const {
    return std::string(1, y_) + std::to_string(x_);
    // char to string ^         int to string ^
}


bool Position::is_valid(int x, char y) {
    bool y_is_valid = y >= 'A' && y <= 'L';
    bool x_is_valid = x >= 1 && x <= 12;
    return x_is_valid && y_is_valid;
}