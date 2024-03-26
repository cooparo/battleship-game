// LUCA PAROLINI, mat. 2041811

#ifndef GRID_H
#define GRID_H

#include <vector>
#include <ostream>
#include "position.h"

class Grid {
  public:

    // Constructor
    Grid();

    /**
     * @brief Gives access to the grid.
     * @param pos The position of the cell.
     * @return const char&
    */
    const char& at(Position) const;
    /**
     * @brief Gives access to the grid.
     * @param pos The position of the cell.
     * @return char&
    */
    char& at(Position);

    /**
     * @brief Gets the width of the grid.
     * @return int
    */
    int width() const { return width_; }
    /**
     * @brief Gets the height of the grid.
     * @return int
    */
    int height() const { return height_; }
    /**
     * @brief Gets the grid.
     * @return const std::vector<std::vector<char>>&
    */
    const std::vector<std::vector<char>>& grid() const { return grid_; }
  
  protected:
    int width_;
    int height_;
    std::vector<std::vector<char>> grid_;
};

/**
 * @brief Print a Grid 12x12, with:
 * on the first column there are letters of the rows;
 * on the last line there are the numbers of the columns.
 * @note Like this (with ' ' instead of '-'):
 * 
 *  A  -  -  -  -  -  -  -  -  -   -   -   
 *  B  -  -  -  -  -  -  -  -  -   -   -   
 *  C  -  -  -  -  -  -  -  -  -   -   -   
 *  D  -  -  -  -  -  -  -  -  -   -   -   
 *  E  -  -  -  -  -  -  -  -  -   -   -   
 *  F  -  -  -  -  -  -  -  -  -   -   -   
 *  G  -  -  -  -  -  -  -  -  -   -   -   
 *  H  -  -  -  -  -  -  -  -  -   -   -   
 *  I  -  -  -  -  -  -  -  -  -   -   -   
 *  L  -  -  -  -  -  -  -  -  -   -   -   
 *  M  -  -  -  -  -  -  -  -  -   -   -   
 *  N  -  -  -  -  -  -  -  -  -   -   -   
 *  1  2  3  4  5  6  7  8  9  10  11  12
**/
std::ostream& operator<<(std::ostream& os, Grid& grid);

#endif // GRID_H