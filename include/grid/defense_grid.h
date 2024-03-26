// LUCA PAROLINI, mat. 2041811

#ifndef DEFENSE_GRID_H
#define DEFENSE_GRID_H

#include <vector>
#include <array>
#include <memory>
#include "grid.h"
#include "ship/ship.h"

class DefenseGrid : public Grid {
  public:

    // Constructor
    DefenseGrid();
    
    /**
     * @brief Moves the ship from their original position, to the target position.
     * @param index Index of the ship in the array.
     * @param pos Target position.
    */
    void move(int index, Position pos);
    /**
     * @brief Moves the ship from their original position, to the target position.
     * @param ship_ptr Pointer to the ship.
     * @param pos Target position.
    */
    void move(Ship* ship_ptr, Position pos);
    /**
     * @brief Moves the ship from their original position, to the target position.
     * @param index Index of the ship in the array.
     * @param pos Target position.
     * @param is_vertical Orientation.
    */
    void move(int index, Position pos, bool is_vertical);

    /**
     * @brief Check ships in defense_grid_.
     * @param pos grid's coordinates.
     * @return A vector of ship in that position,
     * if there are none, return a empty vector.
     */ 
    std::vector<Ship*> ships_in(Position pos) const;
    
    /**
     * @brief Check ships in defense_grid_.
     * @param pos grid's coordinates.
     * @param square_side for searching in an squared area 
     * with at the center the position. Has to be an ODD integer.
     * @return A vector of ship in that area,
     * if there are none, return a empty vector.
     */  
    std::vector<Ship*> ships_in(Position pos, int square_side) const;

    /**
     * @brief Convert the grid with index of the ships in their positions on the grid,
     * to a grid with the char of the ship in thier positions.
     * @return A grid with the char of the ship in their positions.
    */
    Grid get_base_grid() const;

    /**
     * @brief Get the ships in the defense grid.
     * @return A vector of unique pointer of ships.
    */
    const std::array<std::unique_ptr<Ship>, 8>& ships() const { return ships_; };

  private:
    std::array<std::unique_ptr<Ship>, 8> ships_;

    /**
     * @brief Checks if the position is free.
     * @param pos Target position.
     * @param index Index of the ship in the array.
    */
    bool check_free_position(Position pos, int index);
};

std::ostream& operator<<(std::ostream& os, DefenseGrid& grid);

#endif // DEFENSE_GRID_H