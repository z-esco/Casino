#include "gameRun.h"

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

Player& Player::operator=(Player p){
    for(int i=0; i<5;i++){
    hand[i] = p.getCard(i);
    }
    return *this;
}