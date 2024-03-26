// ANDREA PADOVAN, mat. 2043450

#ifndef MATCH_H
#define MATCH_H

#include <array>
#include "player.h"
#include "constant.h"
using std::string;

class Match {
  public:
    enum class MatchOption {
      HumanVSComputer = 1, ComputerVSComputer
    };
    
    /**
     * @brief Initialises a match without starting it.
     * @param option HumanVSComputer or ComputerVSComputer
    */
    Match(MatchOption option);

    /**
     * @brief Initialises a match without starting it.
     * @note Use this constructor to replay a match saved in a log file.
     * @param option HumanVSComputer or ComputerVSComputer
    */
    Match(string replay_path, bool print_cout = true);

    void set_player_1_name(string name) { players_.at(0)->set_name(name); };
    void set_player_2_name(string name) { players_.at(1)->set_name(name); };

    void start_match();

    /**
     * @brief Gets the 0-based winner index from the players in the array.
    */
    int get_winner_index();
    
    /**
     * @brief Gets a summary of the match with both grids for each player and the winner.
    */
    string get_summary();

    /**
     * @brief Saves logs of the match in a file.
     * @param file_path File's path.
    */
    void save(string file_path);
    
    /**
     * @brief Saves the replay output of the match.
    */
    void save_replay(string file_path);

    /**
     * @brief Returns the players in the match.
    */
    const std::array<std::unique_ptr<Player>, 2>& players() const { return players_; };

  private:
    void play_turn();
    void log_command(Command cmd) { log_ += cmd.command() + "\n"; }
    void log_grids(const GridContainer& grid, string name) { grids_log_ += name + "\n" + grid.get_str_grids() + "\n\n"; }

    int turns_ {1};
    std::array<std::unique_ptr<Player>, 2> players_;

    string log_ {""};
    string grids_log_ {""};
};

#endif