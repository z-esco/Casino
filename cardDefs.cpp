#include "gameRun.h"

//Card class defs
//default constructor
Card::Card(){
    value = 0;
    suit = 'n';
}

//paramaterized constructor
Card::Card(int val, char suit){
    value = val;
    this -> suit = suit;
}

/*Card::Card(const Card& c){
    value = c.value;
    suit = c.suit;
}*/

//get card value
int Card::getValue() const{
    return value;
}

//get card suit
char Card::getSuit() const{
    return suit;
}

//set card value
void Card::setValue(int val){
    value = val;
}

//set card suit
void Card::setSuit(char suit){
    this -> suit = suit;
}

/*Card& Card::operator=(Card& c){
    value = c.value;
    suit = c.suit;
    return *this; 
}*/

