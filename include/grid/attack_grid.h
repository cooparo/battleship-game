// LUCA PAROLINI, mat. 2041811

#ifndef ATTACK_GRID_H
#define ATTACK_GRID_H

#include "grid.h"

class AttackGrid : public Grid {
  public:

    // Constructor
    AttackGrid() {}

    /**
     * @brief Erase all 'Y' sign on the attack grid.
    */
    void clear_grid();

    /**
     * @brief Write 'O' in the position.
     * @param pos Position target.
    */
    void missed(Position pos) { this->at(pos) = 'O'; }

    /**
     * @brief Write 'X' in the position.
     * @param pos Position target.
    */
    void hit(Position pos) { this->at(pos) = 'X'; }

    /**
     * @brief Write 'Y' in the position.
     * @param pos Position target.
    */
    void scanned(Position pos) { this->at(pos) = 'Y'; }
};

#endif // ATTACK_GRID_H