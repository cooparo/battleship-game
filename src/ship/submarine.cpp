// PAOLO CONTI, mat. 2032506

#include "ship/submarine.h"
#include "grid/grid_container.h"

void Submarine::action(Position pos, GridContainer& ally, GridContainer& enemy) {
    // Submarine moves to a position and checks for enemy ships (enemy defense grid) in a 5x5 square.
    // It then prints Y on my attack grid.

    int pos_x = pos.x();
    char pos_y = pos.y();
    
    ally.defense_grid().move(this, pos);

    // List of all the positions in the 5x5 square; must consider if the ship is in the corner and you can't have the whole grid (es. F12)
    std::vector<Position> square_pos_list;
    
    // Scan on the x-axis of the 5x5 grid.
    for (int i = pos_x - 2; i <= pos_x + 2; i++) {
        // Scan on the y-axis of the 5x5 grid.
        for (int k = int(pos_y) - 2; k <= int(pos_y) + 2; k++ ) {
            // Check if we're still inside the main grid.
            if (i > 0 && i <= 12 && char(k) >= 'A' && char(k) <= 'L')
                // Save the position as part of the 5x5 grid.
                square_pos_list.push_back(Position(i, char(k)));
        }
    }

    const DefenseGrid& enemy_defense_grid = enemy.defense_grid();       

    // Scan all the positions in the 5x5 square.
    for (int i = 0; i < square_pos_list.size(); i++) {
        if( !(enemy_defense_grid.at(square_pos_list[i]) == ' ') ) {
            // If there's any ship on a position we mark Y on our attack grid.
            ally.attack_grid().scanned(square_pos_list[i]);
        } 
                              
        // If the enemy ship isn't there anymore, the previous position marked as 'Y' is set as ' '
        if ( ally.attack_grid().at(square_pos_list[i]) == 'Y' && enemy.defense_grid().at(square_pos_list[i]) == ' ' ) {
            ally.attack_grid().at(square_pos_list[i]) = ' ';
        }
    }
}