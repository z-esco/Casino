#include "gameRun.h"
#include <iostream>
#include <vector>
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

//Player class defs
//construct player 
Player::Player(){
    setFunds(500.00);
}

//destruct player
Player::~Player(){
}

//get card from players hand
Card Player::getCard(int i){
    return hand[i];
}

std::vector<Card>& Player::getHand(){
    return hand;
}

//return current player funds
double Player::getFunds(){
    return funds;
}

//print player funds
void Player::printFunds(){
    std::cout << "Current Funds: " << funds << std::endl;
}

//change player funds
void Player::setFunds(double amt){
    funds = amt;
}

//put one card into player hand
void Player::setHand(Card c){
    hand.push_back(c);
}
//takes one card from player hand
void Player::removeCard(int n){
    std::vector<Card>::iterator it;
    it = hand.begin() + n;
    this -> hand.erase(it);
}

//empty hand
void Player::clearHand(){
    hand.clear();
}

//bets for player with no minimum
double Player::bet(){
    double amt;
    bool valid;

    while(!valid){
        valid = true;
        //takes in player bet
        std::cout << "Enter bet amount: ";
        std::cin >> amt;
        if(std::cin.fail()){
            std::cin.clear();
            std::cin.ignore();
            valid = false;
        }
        if(amt > funds || amt > 9999.0){
            std::cout << "You don't have the facilities for that\n"; 
            valid = false;
        }
    }
    rakeIn(-amt);
    return amt;
}
//prints hand 
void Player::printHand(){
    for(int i=0; i< hand.size(); i++)
        std::cout << hand[i] << " ";
    std::cout<< std::endl;
}
//prints hand and score
void Player::printHand(int score){
    for(int i=0; i< hand.size(); i++)
        std::cout << hand[i] << " ";
    std::cout<< "Score: " << score << std::endl <<std::endl;
}

//bets for player with a minimum
double Player::bet(double min){
    double amt;
    bool valid;
    do{
    valid = true;
    std::cout << "Enter bet amount: ";
    std::cin >> amt;
    if(std::cin.fail()){
        std::cin.clear();
        std::cin.ignore();
        valid = false;
    }
    if(amt>funds){
        std::cout << "You don't have the facilities for that" << std::endl; 
        valid = false;
    }
    if(funds<min){
        std::cout << "This bet was less thn the minimum required" << std::endl;
        valid = false;
    }
    }while (valid = false);

    rakeIn(-amt);
    return amt;
}

//adds pot to player funds
void Player::rakeIn(double amt){
    setFunds(getFunds() + amt);
}

void order(std::vector <Card> &hand){
    int tempInd;
    Card temp1, temp2;
    
    for(int j = 0; j< hand.size(); j++){
        temp1 = hand[j];
        //gets smallest value
        for(int i = j; i<hand.size(); i++){
            if(hand[i].getValue() < temp1.getValue()){
                temp1 = hand[i];
                tempInd = i;
            }
        }
        //puts smallest value at the front
        temp2 = hand[j];
        hand[j] = temp1;
        hand[tempInd] = temp2;
        
    }
}

Player& Player::operator=(Player p){
    for(int i=0; i<5;i++){
    hand[i] = p.getCard(i);
    }
    return *this;
}