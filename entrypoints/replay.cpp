#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <exception>
using std::cout;
using std::endl;

#include "match.h"

class InvalidOptionException : public std::exception {};

int main(int argc, char* argv[]) {

    if (argc <= 2) {
        cout << "Errore: non sono stati passati abbastanza argomenti." << endl;
        return 1;
    }

    std::string arg = argv[1];
    std::string log_file_name = argv[2];
    
    /* User input can be:
       - v [file name]
       - f [log file name] [output replay file] */

    Match match (log_file_name, arg == "v" ? true : false);
    match.start_match();

    if (arg == "v" && argc == 3) {
        cout << match.get_summary() << endl;
    }
    else if (arg == "f" && argc == 4) {
        std::string output_replay_file_name = argv[3];
        match.save_replay(output_replay_file_name);

    } else { cout << "Opzione non valida" << endl; return 1; };

    return 0;
}