#include "blackjack.h"

#include <iostream>
#include <vector>

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

//adds up value of all cards in hand
int const addHand(std::vector<Card> hand){
    int score;

    score = 0;
    //turns face cards into 10 pts
    for(int i = 0; i< hand.size(); i++){
        if(hand[i].getValue()>=10)
            score += 10;
        else if(hand[i].getValue()>=2)
            score += hand[i].getValue();
        //deals with ace=1/11 case
        else if(hand[i].getValue() == 1){
            if(score + 11  > 21)
                score +=1;
            else
                score += 11;
        }
    }
    
    return score;
}
//checks to see if player has blackjack
bool const checkBlackjack(std::vector<Card> hand){
    return (addHand(hand)==21);
}

//checks to see if player was dealt doubles
bool const checkSplit(std::vector<Card> hand){
    char ans;
    bool split, valid;
    int val;

    split = false;
    valid = false;
    val = hand[0].getValue();
    if(val == hand[1].getValue()){
        //asks players if they want to split
        std::cout << "Do you want to split your ";
        switch(val){
            case 11:
                std::cout << "J";
                break;
            case 12:
                std::cout << "Q";
                break;
            case 13:
                std::cout << "K";
                break;
            case 1:
                std::cout << "A";
                break;
            default:
                std::cout<<val;
                break;
        }
        std::cout << "'s?\n(Y/N):";        
        while(!valid){      
        std::cin >> ans;
        ans = toupper(ans);
        //checks input validity
        if(ans == 'Y'){
            valid = true;
            split = true;
        }
        else if(ans == 'N'){
            split = false;
            valid = true;
        }
        else
            std::cin.clear();
            std::cin.ignore();
            std::cout << "Invalid input try again\n(Y/N):";
        }
    }
    return split;

}

void dealAndCheck(Player& p1, Player& dealer, Deck& deck, bool& split, bool& blackjack){
    //deal 2 cards to each player
   for(int i=0; i<2; i++){
        deal(p1, deck);
        deal(dealer, deck);
    }
        //display dealt cards
    p1.printHand(addHand(p1.getHand()));
    std::cout << "Dealer's Up Card: " << dealer.getCard(0) << std:: endl;
    //check blackjack and ask for split option
    if(checkBlackjack(p1.getHand())&&!checkBlackjack(dealer.getHand()))
        blackjack = true;
    else if(checkSplit(p1.getHand())){
        //creates temporary card and replaces hand after split round
        split = true;
    }
}

//actually runs hand, most relevant part of code
void playHand(Player& p1, Player& dealer, Deck& deck, double bet){
    bool stand, bust, win, tie, surrender;
    int pScore, dScore, deckSize;
    char choice;

    deckSize = 52;
    stand = false;
    bust = false;
    win = false;
    tie = false;
    surrender = false;

    //asks for player moves and checks validity until stand or surreder
    while(!stand && !win && !surrender){
        std::cout << "Hit, Stand, or Surrender\n(H,S, or L):";
        std::cin >> choice;
        choice = toupper(choice);
        //deals another card if they chose to hit
        if(choice == 'H'){
            deal(p1, deck);
            pScore= addHand(p1.getHand());
            std::cout<<std::endl;
            p1.printHand(pScore);
        }
        else if(choice == 'S')
            stand = true;
        else if(choice == 'L')
            surrender = true;
        else{
            std::cout << "Invalid Input.\nChoose H,S, or L.\n";
            std::cin.clear();
        }
        //gathers score after turn
        pScore = addHand(p1.getHand());

        //checks for bust and goes through other win conditions
        if(pScore > 21){
            stand = true;
            bust = true;
        }
        if(pScore == 21)
            win = true;
    }
    //shows bust before dealers cards are added
    if(bust){
        std::cout << "You Bust!\n";
        win = false;
    }
    else{
        //adds up dealers hand until its >=17
        std::cout << "Dealer's Hand: ";
        dealer.printHand(addHand(dealer.getHand()));
        dScore = addHand(dealer.getHand());
        while(dScore < 17){
            deal(dealer, deck);
            dScore = addHand(dealer.getHand());
            dealer.printHand(dScore);
        }
    //compares player and dealer score 
    if(dScore == pScore && pScore <=21)
        tie = true;
    //displays scores
    std::cout << "Your score: " << pScore << "\nDealer's Score: " << dScore << std::endl << std::endl;
    //checks win conditions and displays status
    if(surrender){
        win = false;
        std::cout << "You surrendered here is half of your bet back\n";
        p1.rakeIn(bet/2.0);
    }
    else if(dScore > 21){
        win = true;
        std::cout << "Dealer Busted!\nYou win!\n";
    }
    else if(tie){
        std::cout << "You tied. Here's your bet back\n";
    }
    else if(dScore < pScore && !bust){
        win = true;
        std::cout << "You Win this hand!!\n";
    }
    else{
        win = false;
        std::cout << "You lose this hand :(\n";
    }       
    }
    if(win)
            p1.rakeIn(2.0*bet);
        else if(tie)
            p1.rakeIn(bet); 
    p1.printFunds(); 

    //clears deck and players hands to  restart
        p1.clearHand();
        dealer.clearHand();

}

bool const checkBroke(double funds){
    //checks broketitude and returns bool
    if(funds == 0){
        std::cout << "Too Bad. You broke.\nHope you had fun.\n";
        return true;
    }
    else
        return false;
}

double doubleDown(Player& p, double& bet){
    int total;
    char ans;
    bool valid;
    //adds up initial hand and check if its 9, 10, or 11
    total = p.getCard(0).getValue() + p.getCard(1).getValue();
    if(total>=9 && total <=11){
        //if true, asks user if they want to double their bet
        while(valid != true){
            std::cout << "Do you want to double down on your bet?(Y/N)";
            std::cin >> ans;
            ans = toupper(ans);
            //checks validity
            switch(ans){
                case 'Y':
                    p.rakeIn(-bet);
                    bet = 2.0 * bet;
                    valid = true;
                    break;
                case 'N':
                    valid = true;
                    break;
                default:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Your input was invalid.\n";
                    break;
            } 
        }
    }
    return bet;
}

void insurance(Player& p1, Player dealer, double& bet){
    bool validAns, validBet;
    double sideBet;
    char ans;

    //if dealer has an ace, ask the user if they want to make an insurance side bet
    if(dealer.getCard(0).getValue() == 1){
        do{
            std::cout << "The Dealer has an Ace.\nWould you like insurance against a natural blackjack?\n(Y/N): ";
            std::cin >> ans;
            ans = toupper(ans);
            //checks validity
            switch(ans){
                case 'Y':
                case 'N':
                    validAns = true;
                    break;
                default:
                    std::cin.clear();
                    std::cin.ignore();
                    std::cout << "Invalid Input. Try again\n";
                    break;
            }
        }while(validAns==false);
        if(ans == 'Y'){
            //check validity of side bet
            while(!validBet){
                validBet = true;
                std::cout << "Input bet between 0 and " << bet/2.0 << ": ";
                std::cin >> sideBet;
                if(std::cin.fail()){
                    std::cin.clear();
                    std::cin.ignore();
                    validBet = false;
                    }
                if(sideBet > 0 && sideBet <= bet/2.0)
                    validBet = true;
                else
                    std::cout << "Invalid Input. Try again.\n";
            }
            //removes side bet from funds
            p1.rakeIn(-sideBet);

            //returns double value if the side bet hits
            if(dealer.getCard(1).getValue() >= 10){
                p1.rakeIn(3.0*sideBet);
                std::cout << "The dealer's got blackjack. Your side bet cashes out.\n";
            }
            else
                std::cout << "Blackjack didn't come. You lost the side bet.\n";
        }
    }
}