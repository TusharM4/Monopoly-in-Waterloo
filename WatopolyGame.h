#ifndef WATOPOLYGAME_H
#define WATOPOLYGAME_H
#include <cstdlib> 
#include <iostream> 
#include <string> 
#include <time.h> 
#include "BoardDisplay.h"
#include <fstream> 
using namespace std; 

class BoardDisplay;
class WatopolyGame
{
private:
    BoardDisplay board;
    int currentPlayerTurn;
    int rolledOnce = false;
public:
    WatopolyGame(int numberOfPlayers, string* playerNames, string* playerCharacters);
    WatopolyGame(string fileName);
    void rollDice(bool testing);
    void trade(string name, string give, string recieve);
    void improve(string propertyName, bool toBeBought);
    void mortgage(string propertyName);
    void unmortgage(string propertyName);
    void assets();
    void save(string filename);
    void next();
    void inDC(int r1, int r2, Player* currentPlayer);
    BoardDisplay* getBoard();
    Player* getCurrentPlayer();
    void all();
};
#include "BoardDisplay.h"
#endif
