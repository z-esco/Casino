#ifndef GAME_RUN_H
#define GAME_RUN_H

#include <iostream>
#include <vector>

class Card
{

    public:
    //constructors
    Card();
    // Card(const Card& c);
    Card(int val, char suit);
    
    //getters
    int getValue() const;
    char getSuit()const ;

    //setters
    void setValue(int val);
    void setSuit(char suit);

    //operator overloads
    // Card& operator=(Card& c);

    private: 
    int value;
    char suit;
};

class Deck{
    public:
    //constructors
    Deck();
    // destrcutor
    ~Deck();
    //getters
    std::vector<Card> getDeck();
    Card pullCard(int a)const;
    //remove from deck
    void removeCard(int cardNum);
    void printDeck();
    
    private:
    std::vector<Card> deck;
 
};

class Player{
    //friend function to order cards
    Player& operator=(Player p);
    public:
    //constructors
    Player();
    //destructor
    ~Player();

    //getters
    Card getCard(int i);
    std::vector<Card>& getHand();
    double getFunds();
    
    //display functions
    void printFunds();
    void printHand();
    void printHand(int score);
    
    //setters
    void setFunds(double amt);
    void setHand(Card c);


    //card clear functions
    void removeCard(int i);
    void clearHand();

    //player "move" functions
    double bet();
    double bet(double min);
     
    void rakeIn(double amt);

    private:
    std::vector<Card> hand;
    double funds;
};

//extra function declarations
char welcome();
std::ostream& operator<<(std::ostream& o, Card c);
void deal(Player& p, Deck& deck);
void runBlackjack();
void runFiveCard();
bool const checkPlayAgain();
unsigned int errorCheckInput(std::string prompt, unsigned int lowerBound, unsigned int upperBound);
char errorCheckInput(std::string prompt, char acceptableResponses[], int length);


#endif