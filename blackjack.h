#include "gameRun.h"

//Extra function declarations for blackjack game
int const addHand(std::vector<Card> hand);
bool const checkBlackjack(std::vector<Card> hand);
bool const checkSplit(std::vector<Card> hand);
void dealAndCheck(Player& p1, Player& dealer, Deck& deck, bool& split, bool& blackjack);
void playHand(Player& p1, Player& dealer, Deck& deck, const double bet);
bool const checkBroke(double funds);
double doubleDown(Player& p, double& bet);
void insurance(Player& p1, Player dealer, double& bet);