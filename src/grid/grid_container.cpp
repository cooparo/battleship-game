// LUCA PAROLINI, mat. 2041811

#include "grid/grid_container.h"

// Print the defense grid first and the attack grid last 
std::ostream& operator<<(std::ostream& os, const GridContainer& grid_cont) {

    return os << grid_cont.get_str_grids();
} 

std::string GridContainer::get_str_grids() const {
    std::string str_grid; 
    char letter = 'A';

    std::vector<std::vector<char>> def_grid = defense_grid_.get_base_grid().grid();
    std::vector<std::vector<char>> atk_grid = attack_grid_.grid();

    std::vector<std::vector<char>> sum_grid = def_grid;

    for(int i = 0; i < sum_grid.size(); i++) {
        sum_grid[i].insert(sum_grid[i].end(), atk_grid[i].begin(), atk_grid[i].end());
    }


    //Print the 2 grids
    for(int i = 0; i < sum_grid.size(); i++) {
        // Print the letter of the row at the beginning
        str_grid += std::string(1, letter+i) + " ";

        for(int j = 0; j < sum_grid[i].size(); j++) {
            
            if(j == 12) {
                str_grid += "   "; //space between the grids
                str_grid += std::string(1, letter+i) + " "; //The letter of the row, of the attack grid 
            }

            //char to append
            char c = sum_grid[i][j];
            // Alignment spaces
            std::string space = (j >= 9 && j <= 11) || j >= 21 ? "   " : "  ";
            
            // Append the char to the string 
            str_grid += std::string(1, c) + space;

        }
        str_grid += "\n";
    }

    str_grid += "  1  2  3  4  5  6  7  8  9  10  11  12";
    str_grid += "       1  2  3  4  5  6  7  8  9  10  11  12";
    return str_grid;
}