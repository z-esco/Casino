#include "poker.h"
#include <vector>

//judges hand and returns rank
Rank judgeHand(std::vector<Card>& hand){
    bool flushCheck, straight;
    int pairCount1, pairCount2, pair1, pair2;
    
    //sets aces to 14
    raiseAce(hand);
    //puts the cards in value order
    order(hand);

    //check to see if all suits match
    flushCheck = checkFlush(hand);
    //checks if its a straight  
    straight =  checkStraight(hand);
    
    //checks for pairs
    checkPairs(hand, pairCount1, pair1, pairCount2, pair2);
    Rank rank(hand[hand.size()-1].getValue());

    //Creates rank for straight flush
    if(straight && flushCheck)
        rank.equals(8, hand[hand.size()-1].getValue());
    //Creates rank for four of a kind
    else if(pairCount1== 4)
        rank.equals(7, pair1);
    //Creates rank for full house
    else if(pairCount1 == 3 && pairCount2 == 2)//////Switch pair counter to account for low card being 3 of a kind
        rank.equals(6, pair1, pair2);
    //Creates rank for flush
    else if(!straight && flushCheck)
        rank.equals(5, hand[hand.size()-1].getValue());
    //Creates rank for straight
    else if (straight && !flushCheck)
        rank.equals(4, hand[hand.size()-1].getValue());
    //Creates rank for three of a kind
    else if(pairCount1 == 3 && pairCount2 == 0)
        rank.equals(3, pair1);
    //Creates rank for two pair
    else if (pairCount1 == 2 && pairCount2 == 2)
        rank.equals(2, pair1, pair2);
    //Creates rank for one pair
    else if(pairCount1 == 2 && pairCount2 == 0)
        rank.equals(1, pair1);

    return rank;
}

//raises ace to value 14
void raiseAce(std::vector <Card> &hand){
    for(int i = 0; i< hand.size(); i++){
        if(hand[i].getValue() == 1)
            hand[i].setValue(14);
    }
}

//checks hand for flush
bool const checkFlush(std::vector <Card> hand){
    bool flushCheck = true;
    
    for(int i=0; i<hand.size(); i++){
        if(hand[0].getSuit()!=hand[i].getSuit())
            flushCheck = false;            
    }

    return flushCheck;
}

//checks for straights
bool const checkStraight(std::vector <Card>& hand){
    bool isStraight, lowStraight;

    isStraight = true;

    //checks most cases
    for(int i=0; i< hand.size()-1; i++){
        if(hand[i].getValue() != hand[i+1].getValue()-1){
            isStraight = false;
            break;
        }
    }

    //checks low straight case and changes bool
    if(!isStraight){
        lowStraight = true;
        for(int i = 0; i< hand.size()-2; i++){
            if(hand[i].getValue() != i+2){
                lowStraight = false;
                break;
            }
        }
        if(hand[hand.size()-1].getValue() == 14 && lowStraight){
            Card temp, temp2;
            std::cout << "p\n";
            temp = hand[0];
            hand[0] = hand[hand.size()-1];
            for(int i = 1; i < hand.size() - 1; i++){
                temp2 = hand[i];
                hand[i] = temp;
                temp = temp2;
            }
            hand[hand.size()-1] = temp;
        }
        isStraight = lowStraight;
    }
    return isStraight;
}

//gets the amount of pairs and changes the variables by reference
void checkPairs(std::vector <Card> hand, int&pairCount1, int& pair1, int& pairCount2, int& pair2){
    int count;
    pairCount1 = 0;
    pair1 = 0;
    pairCount2 = 0;
    pair2 = 0;

    //iterates through hand collecting mathces
    for(int i = 0; i < hand.size(); i++){
            count = checkMatch(hand, i);
            i+= count-1;
            //adds to paircount one or moves it down if new pair is greater
            if(pair1==0 && count > 1){
            pair1 = hand[i].getValue();
            pairCount1 = count;
            }
            else if(count > 1 && hand[i].getValue() > pair1 && pairCount1 == count){
                pairCount2 = pairCount1;
                pair2 = pair1;
                pairCount1 = count;
                pair1 = hand[i].getValue();
            }
            else if(count > 1 && count > pairCount1){
                pairCount2 = pairCount1;
                pair2 = pair1;
                pairCount1 = count;
                pair1 = hand[i].getValue();    
            }
            else if(count > 1 && hand[i].getValue() > pair1 && pairCount1 >= count){
                pairCount2 = count;
                pair2 = hand[i].getValue();
            }
            //adds to paircount 2 if its less cards or less valuable
            else if(count > 1 && (count < pairCount1 || hand[i].getValue() < pair1)){
                pairCount2 = count;
                pair2 = hand[i].getValue(); 
            }

    }
}

//counts amount of matches for every input
int const checkMatch(std::vector <Card> hand, int ind){
    int matchCount;
    
    for(int i = ind; i< hand.size(); i++){
        if(hand[i].getValue() == hand[ind].getValue())
            matchCount ++;
    }
    return matchCount;
}

//gets face cards to print out
char getFaceChars(int v){
    char val;

    //switch case to give face cards letters
    switch(v){
        case 14:
            val = 'A';
            break;
        case 13:
            val = 'K';
            break;
        case 12:
            val = 'Q';
            break;
        case 11:
            val = 'J';
            break;
    }

    return val;
}
void Order(std::vector <Card> &hand){
    int tempInd;
    Card temp1, temp2;
    bool change;
    for(int j = 0; j< hand.size(); j++){
        temp1 = hand[j];
        //gets smallest value
        for(int i = j; i<hand.size(); i++){
            if(hand[i].getValue() < temp1.getValue()){
                temp1 = hand[i];
                tempInd = i;
                change = true;
            }
        }
        if(change){
            //puts smallest value at the front
            temp2 = hand[j];
            hand[j] = temp1;
            hand[tempInd] = temp2;
            change = false;
        }
    }
}
//definitons of Rank class

//default constructor
Rank::Rank(){
    rank = 0;
}
//parameterized constructor
Rank::Rank(int hVal){
    highVal = hVal;
    rank = 0;
}
/*Rank::Rank(Rank& r){
    highVal = r.getHighVal();
    lowVal = r.getLowVal();
    rank = r.getRank();
}*/

//setters
void Rank::setRank(int r){
    rank = r;
}

void Rank::setHighVal(int v){
    highVal = v;
}

void Rank::setLowVal(int v){
    lowVal = v;
}

//triple combo setter function
void Rank::equals(int r, int hVal){
    rank = r;
    highVal = hVal;
}

void Rank::equals(int r, int hVal, int lVal){
    rank = r;
    highVal = hVal;
    lowVal = lVal;
}

//getters
int const Rank::getRank(){
    return rank;
}

int const Rank::getHighVal(){
    return highVal;
}

int const Rank::getLowVal(){
    return lowVal;
}

void const Rank::printRank(){ 
    switch(rank){
        case 8:
            if(highVal == 14)
                std::cout << "Royal Flush\n";
            else if(highVal > 10)
                std::cout << getFaceChars(highVal) << " High Straight Flush\n";
            else
                std::cout << highVal << " High Straight Flush\n"; 
            break;
        
        case 7:
        std::cout << "Four of a Kind ";
        if(highVal > 10)
            std::cout << getFaceChars(highVal) << "'s\n";
        else
            std::cout << highVal << "'s\n";
        break;
    
        case 6:
            char high, low;

            if(highVal > 10)
                high = getFaceChars(highVal);
            if(lowVal > 10)
                low = getFaceChars(lowVal);
            std::cout<< "Full House ";
            if(highVal > 10 && lowVal > 10)     
                std::cout << high << "'s and " << low << "'s\n";
            else if(highVal > 10 && lowVal <= 10)
                std::cout << high << "'s and " << lowVal << "'s\n";
            else if (highVal <= 10 && lowVal > 10)
                std::cout << highVal << "'s and " << low << "'s\n";
            else
                std::cout << highVal << "'s and " << lowVal << "'s\n"; 
            break;

        case 5:
        if(highVal > 10)
            std::cout << getFaceChars(highVal);
        else
            std::cout << highVal;
        std::cout << " High Flush\n";
        break;

        case 4:
            if(highVal > 10)
                std::cout << getFaceChars(highVal);
            else
                std::cout << highVal;
            std::cout << " High Straight\n";
            break;

        case 3:
            std::cout << "Three of a Kind ";
            if(highVal > 10)
                std::cout << getFaceChars(highVal);
            else
                std::cout << highVal;
            std::cout << "'s\n";
            break;

        case 2:
            std::cout<< "Two Pair ";
            if(highVal > 10 && lowVal > 10)
                std::cout << getFaceChars(highVal) << "'s and " << getFaceChars(lowVal) << "'s\n";
            else if(highVal >10 && lowVal <=10)
                std::cout << getFaceChars(highVal) << "'s and " << lowVal << "'s\n";
            else     
                std::cout << highVal << "'s and " << lowVal << "'s\n";
            break;
        
        case 1:
            std::cout << "Pair of ";
            if(highVal > 10)
                std::cout << getFaceChars(highVal);
            else
                std::cout << highVal;
            std::cout << "'s\n";
            break;

        default:
            std::cout << "High Card ";
            if( highVal > 10)
                std::cout << getFaceChars(highVal) << std::endl;
            else
                std::cout << highVal << std::endl;
            break;
    }
}

Rank& Rank::operator=(Rank r){
    rank = r.getRank();
    highVal = r.getHighVal();
    lowVal = r.getLowVal();

    return *this;
}