#include "Player.h"

Player::Player()
{
    playerName = "";
    money = 0;
    boardPosition = 0;
    gameCharacter = "";
}

Player::Player(string playerName, int money, string gameCharacter)
{
    this->playerName = playerName;
    this->money = money;
    boardPosition = 0;
    this->gameCharacter = gameCharacter;
    timCups = 0;
}

Player::Player(string playerName, int money, int boardPosition, string gameCharacter, int timsCups, int dcline, int dclinepos)
{
    this->playerName = playerName;
    this->money = money;
    this->boardPosition = boardPosition;
    this->gameCharacter = gameCharacter;
    this->timCups = timsCups;
    this->DCline = dcline;
    this->DClinePos = dclinepos;
}

void Player::movePlayer(int turns)
{
    boardPosition = (boardPosition + turns) % 40;
    notify(turns);
}

void Player::recieveMoney(int amount)
{
    money += amount;
}

bool Player::payMoney(int amount)
{
    if(amount > money)
    {
        return false;
    }
    else
    {
        money -= amount;
        return true;
    }
}

bool Player::buyProperty(Property *property)
{
    cout << "Do you want to purchase " << property->getName() << " for $" << property->getPurchaseCost() << "?" << endl;
    cout << "Enter Y to buy or any other to skip" << endl;
    string input;
    cin >> input;
    if(input == "Y" || input == "y")
    {
        if(money < property->getPurchaseCost())
        {
            cout << "You donot have enough money" << endl;
        }
        else
        {
            property->purchaseProperty();
            propertiesOwned.push_back(property);
            money -= property->getPurchaseCost();
            return true;
        }
    }
    return false;
}

void Player::sellProperty(Property *property)
{
    property->sellProperty();
    for (auto i = propertiesOwned.begin(); i != propertiesOwned.end();
         ++i) {
        if ((*i)->getName() == property->getName()) {
            propertiesOwned.erase(i);
            break;
        }
    }
}

void Player::attachObserver(Observer* observer)
{
    this->observer = observer;
}

void Player::notify(int diceRolled)
{
    observer->update(this, diceRolled);
}

string Player::getName()
{
    return playerName;
}

void Player::displayProperties()
{
    for(size_t i = 0; i < propertiesOwned.size(); i++)
    {
        propertiesOwned[i]->displayProperty();
    }
}

int Player::getBoardPosition()
{
    return boardPosition;
}

string Player::getGameCharacter()
{
    return gameCharacter;
}

//Here we check if a player owns a property or not
bool Player::doesOwnProperty(Property* property)
{
    for(size_t i = 0; i < propertiesOwned.size(); i++)
    {
        if(propertiesOwned[i]->getName() == property->getName())
        {
            return true;
        }
    }
    return false;
}

int Player::getSavings()
{
    return money;
}

int Player::getDoubles() {
    return doubles;
}

int Player::getDCline() {
    return DCline;
}

int Player::getDCpos() {
    return DClinePos;
}

int Player::getCups() {
    return timCups;
}

void Player::setDC(int dc) {
    DCline = dc;
}
       
void Player::setDCpos(int p) {
    DClinePos = p;
}

void Player::setDoubles(int d) {
    doubles = d;
}

void Player::changeCups(int c){
    timCups += c;
}

void Player::dc() {
    doubles = 0;
    boardPosition = 10;
    DCline = 1;
    DClinePos = 0;
}

Property *Player::getOwnedProperty(string propertyName)
{
    for(size_t i = 0; i < propertiesOwned.size(); i++)
    {
        if(propertiesOwned[i]->getName() == propertyName)
        {
            return propertiesOwned[i];
        }
    }
    return nullptr;
}

vector<Property *> Player::getOwnedProperties()
{
    return propertiesOwned;
}

vector<Property *> Player::getSimilarMonopolyBlockProperties(Property *property)
{
    vector<Property*> properties;
    for(size_t i = 0; i < propertiesOwned.size(); i++)
    {
        if(property->getMonopolyBlock() == propertiesOwned[i]->getMonopolyBlock())
        {
            properties.push_back(propertiesOwned[i]);
        }
    }
    return properties;
}

void Player::loadPropertyToOwned(Property * property)
{
    propertiesOwned.push_back(property);
}

int Player::getNumberOfOwnedResidences()
{
    int count = 0;
    for(size_t i = 0; i < propertiesOwned.size(); i++)
    {
        if(propertiesOwned[i]->getName() == "MKV" || propertiesOwned[i]->getName() == "UWP" || propertiesOwned[i]->getName() == "V1" || propertiesOwned[i]->getName() == "REV")
        {
            count += 1;
        }
    }
    return count;
}

int Player::getNumberOfGymsOwned()
{
    int count = 0;
    for(size_t i = 0; i < propertiesOwned.size(); i++)
    {
        if(propertiesOwned[i]->getName() == "PAF" || propertiesOwned[i]->getName() == "CIF")
        {
            count += 1;
        }
    }
    return count;
}
