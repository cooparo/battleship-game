// PAOLO CONTI, mat. 2032506

#include "ship/support_ship.h"
#include "grid/grid_container.h"

void SupportShip::action(Position pos, GridContainer& ally, GridContainer& enemy) {
    // Support ship moves in a position (es. C10), scans for ally ships in a 3x3 square and sets their armor back to max.

    // Moves the submarine to the new position.
    ally.defense_grid().move(this, pos);

    // Looks for enemy ships in a 3x3 square.
    std::vector<Ship*> nearby_ships = ally.defense_grid().ships_in(pos, 3);

    // Fixes all nearby ships.
    if (!nearby_ships.empty()) {
        for (int i = 0; i < nearby_ships.size(); i++) {
            // Doesn't repair itself.
            if (nearby_ships[i] == this) continue;
            nearby_ships[i]->set_max_armor();
        }
    }
}
