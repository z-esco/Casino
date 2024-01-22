#include "gameRun.h"
#include <iostream>

int main(){
    
    //Get game menu selection
    switch(welcome()){
        case 'A':
            runBlackjack();
            break;
        case 'B':
            runFiveCard();
            break;
    }

    return 0;
}
