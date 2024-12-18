#include "gameRun.h"

class Rank{
    private:
        int rank, highVal, lowVal;
    public:
        //default constructor
        Rank();

        //high card parameterized constructor
        Rank(int hVal);

        //Copy constructor
        //Rank(Rank& r);
        
        //setters
        void setRank(int r);
        void setHighVal(int v);
        void setLowVal(int v);

        //triple setter combo function
        void equals(int r, int hVal);
        void equals(int r, int hVal, int lVal);

        //getters
        int const getRank();
        int const getHighVal();
        int const getLowVal();

        //display function
        void const printRank();

        //assignment operator overload
        Rank& operator=(Rank r);

};

//Misc function decs
Rank judgeHand(std::vector<Card>& hand);
void raiseAce(std::vector <Card> &hand);
void order(std::vector <Card> &hand);
bool const checkStraight(std::vector<Card>& hand);
bool const checkFlush(std::vector <Card> hand);
void checkPairs(std::vector <Card> hand, int&pairCount1, int& pair1, int& pairCount2, int& pair2);
int const checkMatch(std::vector <Card> hand, int ind);
char getFaceChars(int v);
std::vector<double> betRound(Player pList[], int BB, int pNum, double blind);
double collectPot(std::vector<double> bets);


