// ANDREA PADOVAN, mat. 2043450

#include <fstream>
#include "match.h"

/**
 * @brief Gets an array with two players based of the option provided.
*/
std::array<std::unique_ptr<Player>, 2> get_players(Match::MatchOption option) {
    switch(option) {
        case Match::MatchOption::HumanVSComputer:
            return {std::make_unique<Human>(), std::make_unique<Computer>()};
        default: // Match::MatchOption::ComputerVSComputer
            return {std::make_unique<Computer>(1), std::make_unique<Computer>(2)};
    }
}

Match::Match(MatchOption option) : players_{get_players(option)} {}

/**
 * @brief Gets an array with two Replayers and initialises them with a list of commands.
*/
std::array<std::unique_ptr<Player>, 2> get_players(std::string replay_path, bool print_cout = true) {
    std::ifstream file (replay_path);
    if (!(file.is_open())) throw std::runtime_error("Error in opening the file.");

    std::array<std::vector<string>, 2> players_commands;
    std::string line;

    // Sorts commands between the two replayers' commands_ array.
    for (int i = 0; i < kDefaultPlayerNumber; i++) {
        for (int j = 0; j < kDefaultShipNumber && getline(file, line); j++) {
            players_commands[i].push_back(line);
        }
    }
    for (int i = 1; getline(file, line); i++) {
        players_commands[i % 2].push_back(line);
    }
    if (print_cout)
        return {std::make_unique<CoutReplayer>(players_commands[0], 1),
                std::make_unique<CoutReplayer>(players_commands[1], 2)};
    else
        return {std::make_unique<Replayer>(players_commands[0], 1),
                std::make_unique<Replayer>(players_commands[1], 2)};

}

Match::Match(std::string replay_path, bool print_cout) : players_{get_players(replay_path, print_cout)} {}


void Match::start_match() {
    // Sets ships positions
    for (int i = 0; i < players_.size(); i++) {
        Player& player = *(players_.at(i));
        for (int n = 0; n < kDefaultShipNumber; n++) {
            try {
                Command cmd = player.get_ship_position(n);
                if (cmd.command() == "XX XX")
                    { player.print_grids(); n--; continue; }
                
                player.set_ship_position(cmd, n);

                log_command(cmd);
                const Player& player_const = player;
                log_grids(player_const.grids(), player_const.name());
            }
            catch (Command::InvalidCommandException e) {
                std::string message = e.what();
                player.notice_invalid_command(e.what());
                n--;
            }
        }
    }

    // Play turns
    while (turns_ <= kDefaultMaxTurns && get_winner_index() < 0) {
        play_turn();
    }
}

void Match::play_turn() {
    Player& ally = *(players_[turns_ % 2]);
    Player& enemy = *(players_[(turns_ + 1) % 2]);

    bool valid_command = false;
    while (!valid_command) {
        try {
            Command cmd = ally.get_move();
            if (cmd.is_special_command()) {
                if (cmd.command() == "XX XX")
                    ally.print_grids();
                else // == "AA AA"
                    ally.clear_attack_grid();
            } else {
                ally.execute(cmd, enemy);
                valid_command = true;
                turns_++;
                log_command(cmd);
                const Player& ally_const = ally;
                log_grids(ally_const.grids(), ally_const.name());
            }
        } catch (Command::InvalidCommandException e) {
            std::string message = e.what();
            ally.notice_invalid_command();
        }
    }
}

int Match::get_winner_index() {
    bool player0_has_ships = players_[0]->has_ships();
    bool player1_has_ships = players_[1]->has_ships();
    
    if (player0_has_ships && !player1_has_ships) return 0;
    if (!player0_has_ships && player1_has_ships) return 1;
    return -1;
}

string Match::get_summary() {
    string summary = "Riepilogo della partita:\n\n";

    const Player& player1 = *(players_.at(0));
    const Player& player2 = *(players_.at(1));
    
    summary += player1.name() + "\n" + player1.grids().get_str_grids() + "\n\n";
    summary += player2.name() + "\n" + player2.grids().get_str_grids() + "\n\n";

    // Prints winner name
    int winner_index = get_winner_index();
    if (winner_index < 0) {
        summary += "Nessun vincitore!";
    } else {
        summary += players_.at(winner_index)->name() + " vince!";
    }

    return summary;
}

void Match::save(string file_path) {
    std::ofstream file(file_path);
    file << log_;
    file.close();
}

void Match::save_replay(string file_path) {
    std::ofstream file(file_path);
    file << grids_log_;
    file << get_summary();
    file.close();
}