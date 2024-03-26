// ANDREA PADOVAN, mat. 2043450

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "command.h"
#include "grid/grid_container.h"

class Player {
  public:
    /**
     * @brief Gets the name of the player.
    */
    std::string name() const { return name_; };
    /**
     * @brief Sets the name of the player.
     * @param name The name of the player
    */
    void set_name(std::string name) { name_ = name; };
    /**
     * @brief Returns the GridConatainer data member grids_.
    */
    const GridContainer& grids() const { return grids_; };


    /**
     * @brief Gets a new command in order to position the ship of the specified index.
    */
    virtual Command get_ship_position(int target_index) = 0;
    /**
     * @brief Sets a ship position based on the given command and a 0-based ship index.
    */
    void set_ship_position(Command, int target_index);


    /**
     * @brief Gets a new command for the next move.
    */
    virtual Command get_move() = 0;
    /**
     * @brief Executes the given command onto a target player.
    */
    void execute(Command, Player& target);
    

    /**
     * @brief Clears the attack grid by removing 'Y' characters
    */
    void clear_attack_grid() { grids_.attack_grid().clear_grid(); };
    /**
     * @brief Returns true if the player has ships with armor > 0.
    */
    bool has_ships() const;

    /**
     * @brief Prints the player's grids by using his preferred method.
    */
    virtual void print_grids() const {};
    /**
     * @brief Notice the player of an invalid command.
    */
    virtual void notice_invalid_command(std::string message = "") const {};

  protected:
    // Constructor
    Player() : name_{""} {};
    Player(std::string name) : name_{name} {};

    // Getter
    GridContainer& grids() { return grids_; };

  private:
    std::string name_;
    GridContainer grids_;
};

// --- Player end

// COMPUTER

class Computer : public Player {
  public:

    // Constructor
    Computer() : Player("Computer") {}
    Computer(int i) : Player("Computer " + std::to_string(i)) {}
    Computer(std::string name) : Player(name) {};

    // Getter
    /**
     * @note The algorithm picks a valid position from the list of his ships, links it to a random target position
     * and creates a Command.
    */
    Command get_move() override;
    /**
     * @note Gets a ship index between 0 and 7 (we have 8 ships), picks a random position and then gets the second position
     * (for the "move" command) based on the ship's size (also makes sure that 2nd position is inside the grid).
    */
    Command get_ship_position(int target_index) override;
};

// --- Computer end

// HUMAN

class Human : public Player {
  public:

    // Constructor
    Human() : Player("Human") {}
    Human(int i) : Player("Human " + std::to_string(i)) {}
    Human(std::string name) : Player(name) {};

    /**
     * @brief Gets a new ship position using cout and cin.
    */
    Command get_ship_position(int target_index) override;
    /**
     * @brief Gets next move using cout and cin.
    */
    Command get_move() override;

    void notice_invalid_command(std::string message = "") const override;
    void print_grids() const override;
};

// --- Human end

// REPLAYER

class Replayer : public Player {
  public:
    Replayer(std::vector<std::string> commands) : Player("Player"), commands_{commands} {}
    Replayer(std::vector<std::string> commands, int i) : Player("Player " + std::to_string(i)), commands_{commands} {}
    Replayer(std::vector<std::string> commands, std::string name) : Player(name), commands_{commands} {};

    /**
     * @brief Gets a new ship position, reading the command list saved in command_ data member.
    */
    Command get_ship_position(int target_index) override;
    /**
     * @brief Gets the next move, reading the command list saved in command_ data member.
    */
    virtual Command get_move() override;

  protected:
    std::vector<std::string> commands_;
};

class CoutReplayer : public Replayer {
  public:
    CoutReplayer(std::vector<std::string> commands) : Replayer(commands) {}
    CoutReplayer(std::vector<std::string> commands, int i) : Replayer(commands, i) {}
    CoutReplayer(std::vector<std::string> commands, std::string name) : Replayer(commands, name) {};

    /**
     * @brief Prints the grids in cout and wait for a second.
     * @brief Then, gets the next move, reading the command list saved in command_ data member.
    */
    Command get_move() override;

    void print_grids() const override;
};

// --- Replayer end

#endif