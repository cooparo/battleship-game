#include <cstdlib>
#include <ctime>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include "match.h"

int main() {
    std::srand(std::time(NULL));
    
    cout << "Benvenuti a BATTAGLIA NAVALE!" << endl;
    cout << "In che modalità vuoi giocare?" << endl;
    cout << "1. Giocatore VS Computer" << endl;
    cout << "2. Computer VS Computer" << endl;
    cout << "Opzione n°: ";
    
    int option = 0;
    cin >> option;
    cin.ignore();

    if (option < 1 || option > 2) {
        cout << "Opzione non valida." << endl;
        return 1;
    }
    cout << endl << "Cominciamo!" << endl << endl << endl;
    
    Match match (static_cast<Match::MatchOption>(option));
    match.start_match();
    
    cout << match.get_summary() << endl;

    std::string log_file = "log.txt"; 
    match.save(log_file);
    cout << "Partita salvata in ./" << log_file << endl;

    return 0;
}