// PAOLO CONTI, mat. 2032506

#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <vector>
#include "ship.h"
#include "constant.h"

class Battleship : public Ship {
  public:

    // Constructor
    Battleship() : Ship(kDefaultLPBattleship, kDefaultLPBattleship, Position()) {}

    /**
     * @brief Set the armor to the max value
     */
    void set_max_armor() override { set_armor(kDefaultLPBattleship); };

    /**
     * @brief Battleship fires in the given position
     * @param pos Position where the battleship fires
     * @param ally Reference to the ally grid 
     * @param enemy Reference to the enemy grid
     */
    void action(Position pos, GridContainer& ally, GridContainer& enemy) override;

    
};

#endif