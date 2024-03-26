// ANDREA PADOVAN, mat. 2043450

#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <stdexcept>
#include <array>
#include "position.h"

class Command {
  public:

    // Constructors
    Command(std::string);
    Command(Position p1, Position p2);
    
    /**
     * @brief Checks if the command is special.
     * @return True if the command is special, false otherwise.
    */
    bool is_special_command() const;
    /**
     * @brief Gives the command as a string.
     * @return string
    */
    std::string command() const { return command_; }
    /**
     * @brief Gives the positions of the command.
     * @return Array of positions.
    */
    std::array<Position, 2> get_command_positions() const;

    class InvalidCommandException : public std::runtime_error
      { public: InvalidCommandException(const std::string& message) : runtime_error(message) {}};
    
  private:
    std::string command_;

    /**
     * @brief Checks if the command is valid.
    */
    static bool is_valid(std::string);

    /**
     * @brief Checks if the command is special.
    */
    static bool is_special(std::string);
    
    /**
     * @brief Gets the positions of the command.
     * @param str Command to be parsed.
     * @return Array of positions.
    */
    static std::array<Position, 2> get_positions(std::string str);
};

#endif