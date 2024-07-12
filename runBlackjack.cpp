#include "blackjack.h"

void runBlackjack(){
    //creates player & dealer
    Player p1, dealer;
    //initializes player, dealer
    //initialize necessary variables
    bool playAgain, blackjack, split;
    int deckSize;
    char choice; 
    double bet;
    
    deckSize = 52;
    playAgain = true;

    //set random seed credits to my beautiful girlfriend: Laura Saravia
    srand(time(0));

    //outputs welcome and rules
    std::cout << "You chose Blackjack!\nRules:\n3:2"; 
    std::cout << " Bet Return\nDealer Stands on 17\n\n";
    
    //creates repeating game
    while(playAgain){
        //makes sure player has money
        if(!checkBroke(p1.getFunds())){
            Deck deck;
            p1.printFunds();

            //gets bet
            bet = p1.bet();
            
            //beginds round
            dealAndCheck(p1, dealer, deck, split, blackjack);

            //ask to double down
            if(!blackjack)
                doubleDown(p1, bet);

            //ask for insurance side bet
            insurance(p1, dealer, bet);
            
            if(blackjack){
                //checks for dealers blackjack and sets tie
                if(checkBlackjack(dealer.getHand())){
                    std::cout << "You both got blackjack! Here is your bet back.\n\n";
                    p1.rakeIn(bet);
                    p1.clearHand();
                    dealer.clearHand();
                }
                //regular blackjack procession
                else{   
                    std::cout<< "BlackJack!! You win\n";
                    //3:2 payout
                    p1.rakeIn(2.5*bet);
                    p1.printFunds();
                    p1.clearHand();
                    dealer.clearHand();            
                }
            }
            else if(split){
                //split bet betweeen both split cards
                bet = bet/2.0;
                
                //create temp vector and copy cards into it
                std::vector<Card> splitCards;
                splitCards.push_back(p1.getCard(0));
                splitCards.push_back(p1.getCard(1));
                
                //clear/refil player hand
                p1.clearHand();
                p1.setHand(splitCards[0]);

                //play first hand
                p1.printHand();
                playHand(p1, dealer, deck, bet);
                
                //reset after hand
                p1.clearHand();
                dealer.clearHand();
                
                //reset cards and bet
                p1.setHand(splitCards[1]);
                deal(dealer, deck);
                deal(dealer, deck);
                p1.printHand();
                playHand(p1, dealer, deck, bet);
            }
            else
                playHand(p1, dealer, deck, bet);

            split = false;
            blackjack = false;
            //checks to see if user wants to continue
            playAgain = checkPlayAgain();
        }
        else
            playAgain = false;
    }
}   