// LUCA PAROLINI, mat. 2041811

#include "grid/attack_grid.h"

void AttackGrid::clear_grid() {
    for(int i = 0; i < grid_.size(); i++) {
        for(int j = 0; j < grid_.at(i).size(); j++) {
            if(grid_.at(i).at(j) == 'Y') {
                grid_.at(i).at(j) = ' ';
            }
        }
    }
}