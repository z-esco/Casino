#include "gameRun.h"

#include <iostream>

char welcome(){
    char input;
    bool valid;
    //prints welcome message
    std::cout << "\nWelcome to our casino!\n\nPlease select a menu option:";
    std::cout << "\n(A) Blackjack\n(B) Five-Card Draw\n(C) Texas Hold 'Em\n"; //add for every game
    do{//checks input validity
    std::cin >> input;
    input = toupper(input);
    switch(input){//add to every game
        case 'A': 
        case 'B':
            valid = true;
            break;
        default:
            valid = false;
            std::cout << input << " is not a valid menu option. Try again\n";
            break;
    }
    }while(!valid);

    return input;
}