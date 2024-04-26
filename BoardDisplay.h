#ifndef BOARD_DISPLAY_H
#define BOARD_DISPLAY_H
#include "Observer.h"
#include "Square.h"
#include "Player.h"
#include "ImproveableProperty.h"
#include "NonImproveableProperty.h"
#include "SLC.h"
#include "NeedlesHall.h"


class BoardDisplay : public Observer
{
private:
    Square* squares[40];
    vector<Player*> players;
public:
    BoardDisplay();
    ~BoardDisplay();
    void displayBoard();
    void update(Player* currentPlayer, int diceRolled);
    void addPlayer(string playerName, string playerCharacter);
    void loadPlayer(string playerName, string playerCharacter, int money, int boardPosition, int timsCups, int dcline, int dclinepos);
    Square* getSquare(int index);
    Player* getPlayer(int playerId);
    Player* getPlayer(string playerName);
    Player* getPlayerOnCharacter(string gameCharacter);
    int getTotalNumberOfPlayers();
    Player* getPropertyOwner(Property* property);
    vector<Property*> getProperties();
    void attachPropertyToPlayer(string propertyName, string playerName, int improvementLevel, bool isMortgaged);
    void performAuction(Player* currentPlayer, Property* property);
};

#endif
