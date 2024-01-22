#include "poker.h"

void runFiveCard(){
    //creates necessary variables
    int pNum, winnerInd;
    bool keepPlaying;

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

int fiveCardWelcome(){
    int playerNum;
    bool valid;
    
    std::cout << "Welcome to Five-Card Draw\n1 Round no-limit game\n";
    //gets amount of players    
    while(!valid){
        std::cout << "Please input number of players(2-5)";
        std::cin >> playerNum;

        if(playerNum >= 2 && playerNum <= 5 && std::cin.fail()!=true)
            valid = true;
        else{
            std::cout << "Invalid input. Try again.\n";
            std::cin.clear();
            std::cin.ignore();
        }
    }

    return playerNum;
}

void swap(Player& p, Deck& deck){
    int toSwitch;
    bool valid;

    do{
        //checks validity of input
        std::cout << "\nHow many card would you like to replace? (0-5)\n";
        std::cin >> toSwitch;

        if(std::cin.fail() || toSwitch > 5 || toSwitch < 0 ){
            std::cin.clear();
            std::cin.ignore();      
        }
        else
            valid = true;
    }while(valid == false);
    valid = false;

    //gets indicies of the cards to switch
    if(toSwitch > 0){
        int swaps[toSwitch];
        std::cout << "Input the indices of the cards to switch(0-4)\n";
        for(int i = 0; i< toSwitch; i++){
            while(valid != true){
                std::cin >> swaps[i];
                if(std::cin.fail() || toSwitch > 4 || toSwitch < 0 ){
                    std::cin.clear();
                    std::cin.ignore(); 
                    valid = false;      
                }
                else
                    valid = true; 
            }
            valid = false;
        }
        //makes sure none of the indices repeat
        int repeatInd = 0;
        bool repeat;
        repeat = repeatCheck(toSwitch, repeatInd, swaps);
        while(repeat){
            while(!valid){
                std::cout << "You repeated " << swaps[repeat] << ". Input a new index (0-4)";
                std::cin>> swaps[repeat];
                if(std::cin.fail() ||  swaps[repeat] < 0 || swaps[repeat] > 4){
                    std::cin.clear();
                    std::cin.ignore();
                }
                else
                    valid = true;
            }
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