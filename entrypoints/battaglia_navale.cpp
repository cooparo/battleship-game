#include <cstdlib>
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;

#include "match.h"

class InvalidOptionException : public std::exception {};

Match::MatchOption get_option(std::string option) {
    if (option == "pc")
        return Match::MatchOption::HumanVSComputer;
    else if (option == "cc")
        return Match::MatchOption::ComputerVSComputer;
    else
        throw InvalidOptionException();
}

int main(int argc, char* args[]) {

    if (argc < 2) {
        cout << "Errore: non sono stati passati abbastanza argomenti." << endl;
        return 1;
    }

    std::string arg = args[1];

    Match::MatchOption option;
    bool is_valid_option = false;

    while(!is_valid_option) {
        try {
            option = get_option(arg);
            is_valid_option = true;
        } catch (InvalidOptionException& e) {
            cout << "Argomento non valido. Selezionare un'opzione corretta" << endl;
            return 1;
        }
    }

    std::srand(std::time(NULL));

    Match match (option);
    match.start_match();

    cout << match.get_summary() << endl;

    match.save("log.txt");

    return 0;
}