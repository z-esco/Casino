#include "gameRun.h"

//Deck class defs
//construct deck and assign each card value
Deck::Deck(){
    Card c;
    for(int i=1; i<=13; i++){
        c.setValue(i);
        c.setSuit('D');
        deck.push_back(c);
        c.setValue(i);
        c.setSuit('H');
        deck.push_back(c);
        c.setValue(i);
        c.setSuit('S');
        deck.push_back(c);
        c.setValue(i);
        c.setSuit('C');
        deck.push_back(c);
    }
}

//deck destructor
Deck::~Deck(){
}

//getCard from deck
Card Deck::pullCard(int a) const{
    return deck[a];
}

//prints deck
void Deck::printDeck(){
    for(int i = 0; i< deck.size(); i++)
        std::cout << deck[i];
    std::cout << std::endl;
}

//returns deck object
std::vector<Card> Deck::getDeck(){
    return deck;
}

//removes one card from deck
void Deck::removeCard(int cardNum){
    deck.erase(deck.begin()+cardNum);
}