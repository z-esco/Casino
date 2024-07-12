#include "gameRun.h"

#include <algorithm>

//insertion operator overload
std::ostream& operator<<(std::ostream& o, Card c){
    char val;

        switch(c.getValue()){
             case 1:
             case 14:
                val = 'A';
                break;
            case 11: 
                val = 'J';
                break;
            case 12:
                val = 'Q';
                break;
            case 13:
                val = 'K';
                break;
       }
    if(c.getValue() >= 2 && c.getValue() <11)
        return std::cout << c.getValue()<< "-" << c.getSuit();
    else
        return std::cout << val << "-" << c.getSuit();

}

//deals one card and removes it from deck
void deal(Player& p, Deck& deck){
    int cardNum;

    //picks a random card and assigns it to player
    cardNum = rand() % deck.getDeck().size();
    p.setHand(deck.pullCard(cardNum));
    deck.removeCard(cardNum);
}
bool const checkPlayAgain(){
    char playAgainChoice;
    bool playAgain;
    
    
    do{
        //displays to ask users if they want to play again
        std::cout << "Do you want to play again? (Y/N)";
        std:: cin >> playAgainChoice;
        playAgainChoice = toupper(playAgainChoice);

        //checks validity
        switch(playAgainChoice){
            case 'Y':
                playAgain = true;
                break;
            case 'N':
                playAgain = false;
                break;
        default: 
                std::cin.clear();
                std::cin.ignore();
                playAgainChoice = 'Z';
                std::cout << "Invalid Choice. Try again.\n";
                break;
        }
    }while(playAgainChoice == 'Z');
    
    return playAgain;
}

unsigned int errorCheckInput(std::string prompt, unsigned int lowerBound, unsigned int upperBound){
    unsigned int input;
    bool valid = false;
    
    do{
        //checks validity of input
        std::cout << prompt;
        std::cin >> input;

        if(std::cin.fail() || input < lowerBound || input > upperBound ){
            std::cin.clear();
            std::cin.ignore();      
        }
        else
            valid = true;
    }while(valid == false);
    
    return input;
}

