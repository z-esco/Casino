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

//Five Card Functions
int fiveCardWelcome();
void swap(Player& p, Deck& deck);
bool repeatCheck(const int& size, int& repeat, int swaps[]);
int highestRank(Rank handRanks[], Rank tempRank, int size, Player pList[]);

//Misc function decs
Rank judgeHand(std::vector<Card>& hand);
void raiseAce(std::vector <Card> &hand);
void order(std::vector <Card> &hand);
bool const checkStraight(std::vector<Card>& hand);
bool const checkFlush(std::vector <Card> hand);
void checkPairs(std::vector <Card> hand, int&pairCount1, int& pair1, int& pairCount2, int& pair2);
int const checkMatch(std::vector <Card> hand, int ind);
char getFaceChars(int v);

double* betRound(Player pList[], int BB, int pNum, double blind){
    double callAmt;
    double pBet[pNum];
    int action = (BB +1) % pNum ;
    int playerResponse;

    bool allPlayersPlayed = false;

    for(int i = 0; i<pNum; i++)
        pBet[i] = 0.00;

    callAmt = blind;
    while(!allPlayersPlayed){
        //sets all computers to call
        if(action != 0){
            pBet[action] = callAmt;
        }
        //asks player for move and then conducts move
        else{
            std::cout <<"The current bet is " << callAmt << std::endl;
            char acceptableResponses[] = {'C', 'R', 'F'};
            
            if(callAmt == pBet[0])
                playerResponse = 'C';
            else
                playerResponse = errorCheckInput("\nWould you like to:\n(C)\tCall\n(R)\tRaise\n(F)\tFold\n\n", acceptableResponses, 3);

            switch(playerResponse){
                case 'C':
                    pBet[action] = callAmt;
                    allPlayersPlayed = true;
                    break;
                case 'R':
                    pBet[action] = pList[action].bet(callAmt);
                    callAmt = pBet[action];
                    break;
                case 'F':
                    pBet[action] = 0;
                    allPlayersPlayed = true;
                    break;
                default:
                    std::cout << "Input error. Try again.\n\n";
                    action = (action -1) % pNum;
                    break;
            } 
        }
        action = (action +1) % pNum;
    }         

    return pBet;
}