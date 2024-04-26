#ifndef PLAYER_H

#define PLAYER_H
#include "Property.h"
#include "Observer.h"
#include <vector>

class BoardDisplay;
class Player
{
private:
    string gameCharacter;
    string playerName;
    int boardPosition;
    int money;
    int timCups = 0;
    int DCline = 0;     // This stores if the player is in the line. 0 = not in line and 1 = in line
    int DClinePos = 0;  // Stores the position in the line 0-2. 
    int doubles = 0;
    vector<Property*> propertiesOwned;
    Observer* observer;
public:
    Player();
    Player(string playerName, int money, string gameCharacter);
    Player(string playerName, int money, int boardPosition, string gameCharacter, int timsCups, int dcline, int dclinepos);
    void movePlayer(int turns);
    void recieveMoney(int amount);
    bool payMoney(int amount);
    bool buyProperty(Property* property);
    void sellProperty(Property* property);
    void attachObserver(Observer* observer);
    void notify(int diceRolled);
    string getName();
    void displayProperties();
    int getBoardPosition();
    string getGameCharacter();
    bool doesOwnProperty(Property* property);
    int getSavings();
    int getDoubles(); 
    void setDoubles(int d);
    int getDCline(); 
    void setDC(int dc);       
    void setDCpos(int p);
    int getDCpos();
    int getCups();
    void changeCups(int c); 
    void dc(); 
    Property* getOwnedProperty(string propertyName);
    vector<Property*> getOwnedProperties();
    vector<Property*> getSimilarMonopolyBlockProperties(Property* property);
    void loadPropertyToOwned(Property* property);
    int getNumberOfOwnedResidences();
    int getNumberOfGymsOwned();
};

#include "BoardDisplay.h"
#endif
