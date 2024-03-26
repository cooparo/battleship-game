// LUCA PAROLINI, mat. 2041811

#ifndef GRID_CONTAINER_H
#define GRID_CONTAINER_H

#include <ostream>
#include "defense_grid.h"
#include "attack_grid.h"

class GridContainer {
  public:
    
    // Constructor
    GridContainer() {}

    /**
     * @brief Gets the defense grid
     * @return DefenseGrid& 
    */
    DefenseGrid& defense_grid() { return defense_grid_; }
    /**
     * @brief Gets the attack grid
     * @return AttackGrid& 
    */
    AttackGrid& attack_grid() { return attack_grid_; }
    /**
     * @brief Gets the defense grid
     * @return const DefenseGrid& 
    */
    const DefenseGrid& defense_grid() const { return defense_grid_; }
    /**
     * @brief Gets the attack grid
     * @return const AttackGrid& 
    */
    const AttackGrid& attack_grid() const { return attack_grid_; }
    /**
     * @brief Gets the attack and defense grids as a string
     * @return A string containing the attack and defense grids
    */
    std::string get_str_grids() const;
    
  private:
    DefenseGrid defense_grid_;
    AttackGrid attack_grid_;
};

std::ostream& operator<<(std::ostream&, const GridContainer&);

#endif // GRID_CONTAINER_H