#include "fiveCard.h"

void runFiveCard(){
    //creates necessary variables
    int pNum, winnerInd, BBind, LBind;
    bool keepPlaying;
    double bigBlind;

    //initalizes necessary variables
    pNum = fiveCardWelcome();

    //create objects for every player amt
    Player pList[pNum];

    //creates list of hand Ranks
    Rank handRanks[pNum];
    
    //creates a temporary rank to help store hand ranks
    Rank tempRank;

    //sets randomness for deck
    srand(time(0));

    //randomly sets Big and Little Blinds
    BBind = rand() % 5;
    LBind = (BBind - 1) % 5;

    //set BigBlinds
    bigBlind = 20.00;

    keepPlaying = true;
    while(keepPlaying){
        //creates new deck
        Deck deck;

        //deals five cards to each player
        for(int j = 0; j < 5; j++){
            for(int i = 0; i < pNum; i++)
                deal(pList[i], deck);
        }

        //order all players hands
        for(int i = 0; i < pNum; i++){
            order(pList[i].getHand());
        }

        //display user hand
        std::cout<< "Your hand: ";
        pList[0].printHand();

        swap(pList[0], deck);

        pList[0].printHand();

        //gives a rank to each player
        for(int i = 0; i < pNum; i++){
            tempRank = judgeHand(pList[i].getHand());
            handRanks[i].equals(tempRank.getRank(), tempRank.getHighVal(), tempRank.getLowVal());
        }

        //determines the player with the highest rank
        winnerInd = highestRank(handRanks, tempRank, pNum, pList);

        std::cout << "Player " << winnerInd +1 << " wins!\nThey had a ";
        handRanks[winnerInd].printRank();
        pList[winnerInd].printHand();       

        //clears every  players hand
        for(int i = 0; i < pNum; i++)
            pList[i].clearHand();

        keepPlaying = checkPlayAgain();
    }
}