// LUCA PAROLINI, mat. 2041811

#include "grid/grid.h"
#include "constant.h"

Grid::Grid() : width_{kDefaultWideGrid}, height_{kDefaultWideGrid} {
    // Initialize a 12x12 vector with elements that contain ' '
    grid_ = std::vector<std::vector<char>>(kDefaultWideGrid, std::vector<char>(kDefaultWideGrid, ' '));
}

/**
 * @return const char contained in the position of the grid
*/
const char& Grid::at(Position pos) const {
    int x = pos.x_grid_coord();
    int y = pos.y_grid_coord();
    return grid_[y][x];
}

/**
 * @return char contained in the position of the grid
*/
char& Grid::at(Position pos) {
    int x = pos.x_grid_coord();
    int y = pos.y_grid_coord();
    return grid_[y][x];
}


std::ostream& operator<<(std::ostream& os, Grid& grid) {
    const std::vector<std::vector<char>> grid_ = grid.grid();
    std::string str_grid = "";
    char letter = 'A';

    // Print the 2d vector
    for(int i = 0; i < grid_.size(); i++) {
        
        // Print the letter of the row at the beginning
        str_grid += std::string(1, letter+i) + " ";
        
        for(int j = 0; j < grid_.size(); j++) {
            // Alignment spaces
            std::string space = "  ";
            if(j >= 9) space = "   ";

            // Append the char to the string 
            str_grid += std::string(1, grid_[i][j]) + space;
        }
        str_grid += "\n";
    }

    str_grid += "   1  2  3  4  5  6  7  8  9  10  11  12";

    return os << str_grid;
}