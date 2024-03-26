// PAOLO CONTI, mat. 2032506

#ifndef SUPPORT_SHIP_H
#define SUPPORT_SHIP_H

#include "ship.h"
#include "constant.h"

class SupportShip : public Ship {
  public:

    // Constructor
    SupportShip() : Ship(kDefaultLPSupportShip, kDefaultLPSupportShip, Position()) {}

    // Setter
    void set_max_armor() override { set_armor(kDefaultLPSupportShip); }

    void action(Position, GridContainer&, GridContainer&) override;
    
    
};

#endif