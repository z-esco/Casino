#include "poker.h"

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