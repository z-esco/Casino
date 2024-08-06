#include "fiveCard.h"

const unsigned int MIN_PLAYERS = 2;
const unsigned int MAX_PLAYERS = 5;
const unsigned int CARDS_PER_HAND = 5;

int fiveCardWelcome(){
    int playerNum;
    bool valid;
    
    std::cout << "Welcome to Five-Card Draw\n1 Round no-limit game\n";
    
    //gets amount of players 
    playerNum = errorCheckInput("Please input number of players(2-5)", MIN_PLAYERS, MAX_PLAYERS);

    return playerNum;
}

void swap(Player& p, Deck& deck){
    int toSwitch;
    bool valid;

    //checks validity of input
       toSwitch = errorCheckInput("\nHow many card would you like to replace? (0-5)\n", 0 , CARDS_PER_HAND);

    //gets indicies of the cards to switch
    if(toSwitch > 0){
        int swaps[toSwitch];    //creates list of indices that user wants to replace
        for(int i = 0; i < toSwitch; i++)
            swaps[i] = errorCheckInput("Input the indices of the cards to switch(0-4)\n", 0, 5);

        //makes sure none of the indices repeat
        int repeatInd = 0;
        bool repeat;
        repeat = repeatCheck(toSwitch, repeatInd, swaps);
        while(repeat){

            std::cout << "You repeated index " << swaps[repeatInd];

            swaps[repeatInd] = errorCheckInput("\nInput a new index (0-4)", 0 , CARDS_PER_HAND);
            repeat = repeatCheck(toSwitch, repeatInd, swaps);
        }
    
        //deals one new card to all indicies
        for(int i = 0; i < toSwitch; i++){
            p.removeCard(swaps[i]);
            deal(p, deck);
        }
    }
}

bool repeatCheck(const int& size, int& repeatInd, int swaps[]){
    bool repeat = false;
    
    for(int i = 0; i< size; i++){
        for(int j = i +1 ; j < size-1; j++){
            if(swaps[i] == swaps[j]){
                repeatInd = j;
                repeat = true;
            }
        }
        if(repeat)
            i = size;
    }

    return repeat;
}

int highestRank(Rank handRanks[], Rank tempRank, int size, Player pList[]){
    int winnerInd = 0;
    tempRank = handRanks[0];
    for(int i = 1; i < size; i++){
        if(handRanks[i].getRank() > tempRank.getRank()){
            winnerInd = i;
            tempRank = handRanks[i];
        }
        else if(handRanks[i].getRank() == tempRank.getRank()){
            if(handRanks[i].getHighVal() > tempRank.getHighVal()){
                winnerInd = i;
                tempRank = handRanks[i];    
            }
            else if(handRanks[i].getHighVal() == tempRank.getHighVal()){
                if(handRanks[i].getLowVal() > tempRank.getLowVal()){
                    winnerInd = i;
                    tempRank = handRanks[i];
                }
                else if(handRanks[i].getLowVal() == tempRank.getLowVal()){
                    bool larger;
                    for(int j = 4; j >= 0; j--){
                        if(pList[i].getCard(j).getValue()>=pList[winnerInd].getCard(j).getValue())
                            winnerInd = i;
                            tempRank = handRanks[i];
                    }
                }
            }
        }
    }

    return winnerInd;
}