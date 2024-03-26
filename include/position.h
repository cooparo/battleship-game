// ANDREA PADOVAN, mat. 2043450

#ifndef POSITION_H
#define POSITION_H

#include <string>
#include <stdexcept>
#include "constant.h"

class Position {
  public:
    Position() : x_{kDefaultXPosition}, y_{kDefaultYPosition} {}
    Position(std::string p);
    Position(int x, char y);

    int x() const { return x_; }
    char y() const { return y_; }

    /**
     * @brief Conversion for x vector coordinate
    */
    int x_grid_coord() const { return x_-1; }
    /**
     * @brief Conversion for y vector coordinate
    */
    int y_grid_coord() const { return y_-'A'; }

    bool is_default_position() const { return x_ == kDefaultXPosition && y_ == kDefaultYPosition; };
    std::string to_string() const;

    class InvalidPositionException : public std::runtime_error
      { public: InvalidPositionException(const std::string& message) : runtime_error(message) {}};

  private:
    int x_;
    char y_;

    /**
     * @brief Check if the position is in the grid 
     * 
    */
    static bool is_valid(int x, char y);
};

#endif