#include "poker.h"

//Five Card Functions
int fiveCardWelcome();
void swap(Player& p, Deck& deck);
bool repeatCheck(const int& size, int& repeat, int swaps[]);
int highestRank(Rank handRanks[], Rank tempRank, int size, Player pList[]);
