// PAOLO CONTI, mat. 2032506

#include <vector>
#include "ship/battleship.h"
#include "grid/grid_container.h"

/* Battleship fires on C9: go to enemy def. grid and check if there's a ship:
    -yes: add an X on my attack grid, armor -1 on the damaged ship.
    -no: change nothing on the enemy grids, add O on your attack grid. */
    
void Battleship::action(Position pos, GridContainer& ally, GridContainer& enemy) {
    // Checks if there is a ship in the position given
    std::vector<Ship*> target = enemy.defense_grid().ships_in(pos);
    
    // If the target position is empty we print an "O" on our attack grid.
    if (target.empty()) {
        ally.attack_grid().missed(pos);
    } 
    //  Enemy ship hit
    else {                
        ally.attack_grid().hit(pos);

        // Reduce target's armor.
        target[0]->decreaseLP();

        // If the enemy ship has 0 armor, it will be removed from the enemy defense grid (every position of said ship is set to ' ').
        if (target[0]->armor() == 0) {
            std::vector<Position> ship_positions = target[0]->get_ship_positions();
            for (int i = 0; i < ship_positions.size(); i++) {
                enemy.defense_grid().at(ship_positions[i]) = ' ';
            }
            // Destroyed ship's position is set to default again.
            target[0]->set_position(Position());
        }
    }
}