// PAOLO CONTI, mat. 2032506

#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include "position.h"

class GridContainer;

class Ship {
  public: 

    /**
     * @brief Execute the action of the ship
     * @param pos Position where the battleship fires
     * @param ally Reference to the ally grid 
     * @param enemy Reference to the enemy grid
     */
    virtual void action(Position pos, GridContainer& ally, GridContainer& enemy) = 0;
    
    /**
     * @brief Gives the size of the ship
     * @return int
     */
    int size() const { return size_; }
    /**
     * @brief Gives the armor of the ship
     * @return int
     */
    int armor() const { return armor_; }
    /**
     * @brief Gives the position of the ship
     * @return Position
     */
    Position position() const { return position_; }
    /**
     * @brief Gives the orientation of the ship
     * @return bool
     */
    bool is_vertical() const { return is_vertical_; }
    /**
     * @brief Gives all the positions that the ship occupies
     * @return std::vector<Position>
     */
    std::vector<Position> get_ship_positions() const;
    
    /**
     * @brief Sets the armor of the ship
     * @param armor The new armor
     */
    void set_armor(int armor) { armor_ = armor; }
    /**
     * @brief Decreases the armor of the ship by one
     */
    void decreaseLP() { armor_--; }
    /**
     * @brief Sets the orientation of the ship, true for vertical, false for horizontal
     * @param 
     */
    void set_vertical(bool b) { is_vertical_ = b; }
    /**
     * @brief Sets the position of the ship
     */
    void set_position(Position pos) { position_ = pos; }
    /**
     * @brief Sets the max armor of the ship
     */
    virtual void set_max_armor() = 0;

  protected:
    // Constructor
    Ship(int size, int armor, Position pos) : size_(size), armor_(armor), position_(pos) {}
    
  private:
    int size_;
    int armor_;
    Position position_;
    bool is_vertical_;

    /**
     * @brief Checks if the ship is vertical
     * @return True if the ship is vertical, false if it is horizontal
     */
    static bool is_vertical(Position, Position);
};

#endif  