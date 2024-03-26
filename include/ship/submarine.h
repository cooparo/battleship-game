// PAOLO CONTI, mat. 2032506

#ifndef SUBMARINE_H
#define SUBMARINE_H

#include "ship.h"
#include "constant.h"

class Submarine : public Ship {
  public:

    // Constructor 
    Submarine() : Ship(kDefaultLPSubmarine, kDefaultLPSubmarine, Position()) {}

    /**
     * @brief Set the armor to the max value
     */
    void set_max_armor() override { set_armor(kDefaultLPSubmarine); }

    /**
     * @brief Submarine moves in the given position and search in the enemy grid
     * in a area 5x5 from his position
     * @param pos Position where the subamrine moves, 
     * @param ally Ally grid 
     * @param enemy Enemy grid
    */
    void action(Position, GridContainer&, GridContainer&) override;
};

#endif