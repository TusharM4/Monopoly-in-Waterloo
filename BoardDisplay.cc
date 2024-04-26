#include "BoardDisplay.h"

BoardDisplay::BoardDisplay()
{
    bool isProperty[40] = {false, true, false, true, false, true, true, false, true, true, false, true, true, true, true, true, true, false, true, true, false, true, false, true, true, true, true, true, true, true, false, true, true, false, true, true, false, true, false, true};
    bool isImproveableProperty[40] = {false, true, false, true, false, false, true, false, true, true, false, true, false, true, true, false, true, false, true, true, false, true, false, true, true, false, true, true, false, true, false, true, true, false, true, false, false, true, false, true};
    string names[40] = {"Collect OSAP", "AL", "SLC", "ML", "TUITION", "MKV", "ECH", "NEEDLES HALL", "PAS", "HH", "DC Tims Line", "RCH", "PAC", "DWE", "CPH", "UWP", "LHI", "SLC", "BMH", "OPT", "Goose Nesting", "EV1", "NEEDLES HALL", "EV2", "EV3", "V1", "PHYS", "B1", "CIF", "B2", "GO TO TIMS", "EIT", "ESC", "SLC", "C2", "REV", "NEEDLES HALL", "MC", "COOP FEE", "DC"};
    int purchaseCosts[40] = {0, 40, 0, 60, 0, 200, 100, 0, 100, 120, 0, 140, 150, 140, 160, 200, 180, 0, 180, 200, 0, 220, 0, 220, 240, 200, 260, 260, 150, 280, 0, 300, 300, 0, 320, 200, 0, 350, 0, 400};
    int rents[40] = {0, 2, 0, 4, 0, 25, 6, 0, 6, 8, 0, 10, -1, 10, 12, 25, 14, 0, 14, 16, 0, 18, 0, 18, 20, 25, 22, 22, -1, 24, 0, 26, 26, 0, 28, 25, 0, 35, 0, 50};
    int improvementCosts[40] = {0, 50, 0, 50, 0, 0, 50, 0, 50, 50, 0, 100, 0, 100, 100, 0, 100, 0, 100, 100, 0, 150, 0, 150, 150, 0, 150, 150, 0, 150, 0, 200, 200, 0, 200, 0, 0, 200, 0, 200};
    string monopolyBlocks[40] = {"", "Arts1", "", "Arts1", "", "", "Arts2", "", "Arts2", "Arts2", "", "Eng", "", "Eng", "Eng", "", "Health", "", "Health", "Health", "", "Env", "", "Env", "Env", "", "Sci1", "Sci1", "", "Sci1", "", "Sci2", "Sci2", "", "Sci2", "", "", "Math", "", "Math"};
    for(int i = 0; i < 40; i++)
    {
        if(isProperty[i])
        {
            if(isImproveableProperty[i])
                squares[i] = new ImproveableProperty(names[i], purchaseCosts[i], monopolyBlocks[i], rents[i], improvementCosts[i]);
            else
                squares[i] = new NonImproveableProperty(names[i], purchaseCosts[i], monopolyBlocks[i], rents[i]);
        }
        else
        {
            //Add non property classes
            if(names[i] == "SLC")
            {
                squares[i] = new SLC(names[i]);
            }
            else if(names[i] == "NEEDLES HALL")
            {
                squares[i] = new NeedlesHall(names[i]);
            }
            else
            {
                squares[i] = new NonProperty(names[i]);
            }
            
        }
    }
}

BoardDisplay::~BoardDisplay() {
  for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
  }
  for (size_t i = 0; i < 40; ++i) {
    delete squares[i];
  }
  players.clear();
}

void BoardDisplay::displayBoard()
{
    for(int i = 0 ; i < 11; i++)
    {
        cout << "________";
    }
    cout << endl;
    for(int j = 0; j < 5; j++)
    {
        for(int i = 20 ; i < 31; i++)
        {  
            if(j == 4 || (j == 1 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr))
            {
                cout << "|_______";
            }
            else if((j == 0 && dynamic_cast<const ImproveableProperty*>(squares[i]) == nullptr) || (j == 2 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr))
            {
                string name = squares[i]->getName();
                if(name.length() > 7)
                {
                    name = name.substr(0,7);
                }
                else
                {
                    for(int k = name.length(); k < 7; k++)
                    {
                        name += " ";
                    }
                }
                cout << "|" << name;
            }
            else if(j == 0 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr)
            {
                string toBeAdded = "";
                ImproveableProperty* prop = dynamic_cast<ImproveableProperty*>(squares[i]);
                for(int k = 0; k < prop->getImprovementLevel(); k++)
                {
                    toBeAdded += "I";
                }
                for(int k = toBeAdded.length(); k < 7; k++)
                {
                    toBeAdded += " ";
                }
                cout << "|" << toBeAdded;
            }
            else if(j == 3)
            {
                string toBeAdded = "";
                for(size_t k = 0; k < players.size(); k++)
                {
                    if(players[k]->getBoardPosition() == i)
                    {
                        toBeAdded += players[k]->getGameCharacter();
                    }
                }
                for(int k = toBeAdded.length(); k < 7; k++)
                {
                    toBeAdded += " ";
                }
                cout << "|" << toBeAdded;
            }
            else
            {
                cout << "|       ";
            }
        }
        cout << "|" << endl;
    }
    for(int i = 19; i > 10; i--)
    {
        for(int j = 0; j < 5; j++)
        {
            if(j == 4 || (j == 1 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr))
            {
                cout << "|_______|";
            }
            else if((j == 0 && dynamic_cast<const ImproveableProperty*>(squares[i]) == nullptr) || (j == 2 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr))
            {
                string name = squares[i]->getName();
                if(name.length() > 7)
                {
                    name = name.substr(0,7);
                }
                else
                {
                    for(int k = name.length(); k < 7; k++)
                    {
                        name += " ";
                    }
                }
                cout << "|" << name << "|";
            }
            else if(j == 0 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr)
            {
                string toBeAdded = "";
                ImproveableProperty* prop = dynamic_cast<ImproveableProperty*>(squares[i]);
                for(int k = 0; k < prop->getImprovementLevel(); k++)
                {
                    toBeAdded += "I";
                }
                for(int k = toBeAdded.length(); k < 7; k++)
                {
                    toBeAdded += " ";
                }
                cout << "|" << toBeAdded << "|";
            }
            else if(j == 3)
            {
                string toBeAdded = "";
                for(size_t k = 0; k < players.size(); k++)
                {
                    if(players[k]->getBoardPosition() == i)
                    {
                        toBeAdded += players[k]->getGameCharacter();
                    }
                }
                for(int k = toBeAdded.length(); k < 7; k++)
                {
                    toBeAdded += " ";
                }
                cout << "|" << toBeAdded << "|";
            }
            else
            {
                cout << "|       |";
            }
            for(int k = 0; k < 71; k++)
            {
                if(i == 11 && j == 4)
                {
                    cout << "_";
                }
                else
                {
                    cout << " ";
                }
            }
            if(j == 4 || (j == 1 && dynamic_cast<const ImproveableProperty*>(squares[40 - i + 10]) != nullptr))
            {
                cout << "|_______|" << endl;
            }
            else if((j == 0 && dynamic_cast<const ImproveableProperty*>(squares[40 - i + 10]) == nullptr) || (j == 2 && dynamic_cast<const ImproveableProperty*>(squares[40 - i + 10]) != nullptr))
            {
                string name = squares[40 - i + 10]->getName();
                if(name.length() > 7)
                {
                    name = name.substr(0,7);
                }
                else
                {
                    for(int k = name.length(); k < 7; k++)
                    {
                        name += " ";
                    }
                }
                cout << "|" << name << "|" << endl;
            }
            else if(j == 0 && dynamic_cast<const ImproveableProperty*>(squares[40 - i + 10]) != nullptr)
            {
                string toBeAdded = "";
                ImproveableProperty* prop = dynamic_cast<ImproveableProperty*>(squares[40 - i + 10]);
                for(int k = 0; k < prop->getImprovementLevel(); k++)
                {
                    toBeAdded += "I";
                }
                for(int k = toBeAdded.length(); k < 7; k++)
                {
                    toBeAdded += " ";
                }
                cout << "|" << toBeAdded << "|" << endl;
            }
            else if(j == 3)
            {
                string toBeAdded = "";
                for(size_t k = 0; k < players.size(); k++)
                {
                    if(players[k]->getBoardPosition() == 40 - i + 10)
                    {
                        toBeAdded += players[k]->getGameCharacter();
                    }
                }
                for(int k = toBeAdded.length(); k < 7; k++)
                {
                    toBeAdded += " ";
                }
                cout << "|" << toBeAdded << "|" << endl;
            }
            else
            {
                cout << "|       |"<< endl;;
            }
        }
    }
    for(int j = 0; j < 5; j++)
    {
        for(int i = 10 ; i >= 0; i--)
        {
            if(j == 4 || (j == 1 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr))
            {
                cout << "|_______";
            }
            else if((j == 0 && dynamic_cast<const ImproveableProperty*>(squares[i]) == nullptr) || (j == 2 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr))
            {
                string name = squares[i]->getName();
                if(name.length() > 7)
                {
                    name = name.substr(0,7);
                }
                else
                {
                    for(int k = name.length(); k < 7; k++)
                    {
                        name += " ";
                    }
                }
                cout << "|" << name;
            }
            else if(j == 0 && dynamic_cast<const ImproveableProperty*>(squares[i]) != nullptr)
            {
                string toBeAdded = "";
                ImproveableProperty* prop = dynamic_cast<ImproveableProperty*>(squares[i]);
                for(int k = 0; k < prop->getImprovementLevel(); k++)
                {
                    toBeAdded += "I";
                }
                for(int k = toBeAdded.length(); k < 7; k++)
                {
                    toBeAdded += " ";
                }
                cout << "|" << toBeAdded;
            }
            else if(j == 3)
            {
                string toBeAdded = "";
                for(size_t k = 0; k < players.size(); k++)
                {
                    if(players[k]->getBoardPosition() == i)
                    {
                        toBeAdded += players[k]->getGameCharacter();
                    }
                }
                for(int k = toBeAdded.length(); k < 7; k++)
                {
                    toBeAdded += " ";
                }
                cout << "|" << toBeAdded;
            }
            else
            {
                cout << "|       ";
            }
        }
        cout << "|" << endl;
    }

}

void BoardDisplay::update(Player* currentPlayer, int diceRolled)
{
    int boardPosition = currentPlayer->getBoardPosition();
    cout << "Player " << currentPlayer->getName() << " landed on " << getSquare(boardPosition)->getName() << endl;
    if(dynamic_cast<const Property*>(getSquare(boardPosition)) != nullptr)
    {
        Property* property = dynamic_cast<Property*>(getSquare(boardPosition));
        if(!property->getIsOwned())
        {
            if(!currentPlayer->buyProperty(property))
            {
                performAuction(currentPlayer, property);
            }
        }
        else
        {
            //Here we collect rent
            Player* owner = getPropertyOwner(property);
            vector<Property*> monopolyProperties = owner->getSimilarMonopolyBlockProperties(property);
            if(property->getMortgaged()) 
            {
                cout << "This property is mortgaged, so no rent is collected" << endl;
            }
            else if(dynamic_cast<ImproveableProperty*>(getSquare(boardPosition)) != nullptr)
            {
                if((monopolyProperties.size() == 3 || (monopolyProperties.size() == 2 && property->getMonopolyBlock() == "Arts1") || (monopolyProperties.size() == 2 && property->getMonopolyBlock() == "Math")) && dynamic_cast<const ImproveableProperty*>(getSquare(boardPosition)) != nullptr && dynamic_cast<ImproveableProperty*>(getSquare(boardPosition))->getImprovementLevel() == 0)
                {
                    cout << "You paid $" << property->getFee() * 2 << " as rent to " << owner->getName() << endl;
                    currentPlayer->payMoney(property->getFee() * 2);
                    owner->recieveMoney(property->getFee() * 2);
                }
                else
                {
                    cout << "You paid $" << property->getFee() << " as rent to " << owner->getName() << endl;
                    currentPlayer->payMoney(property->getFee());
                    owner->recieveMoney(property->getFee());
                }
            }
            else
            {
                if(squares[boardPosition]->getName() == "CIF" || squares[boardPosition]->getName() == "PAC")
                {
                    int rent = 4 * diceRolled;
                    if (currentPlayer->getNumberOfGymsOwned() == 2)
                    {
                        rent = 10 * diceRolled;
                    }
                    cout << "You paid $" << rent << " as rent to " << owner->getName() << endl;
                    currentPlayer->payMoney(rent);
                    owner->recieveMoney(rent);
                }
                else
                {
                    int rent = 25;
                    if (currentPlayer->getNumberOfOwnedResidences() == 2)
                    {
                        rent = 50;
                    }
                    else if (currentPlayer->getNumberOfOwnedResidences() == 3)
                    {
                        rent = 100;
                    }
                    else if (currentPlayer->getNumberOfOwnedResidences() == 4)
                    {
                        rent = 200;
                    }
                    cout << "You paid $" << rent << " as rent to " << owner->getName() << endl;
                    currentPlayer->payMoney(rent);
                    owner->recieveMoney(rent);
                }
            }
        }
    }
    else
    {
        NonProperty* nonProperty = dynamic_cast<NonProperty*>(getSquare(boardPosition));
        nonProperty->performAction(currentPlayer);
    }
}

void BoardDisplay::addPlayer(string playerName, string playerCharacter)
{
    Player* player = new Player(playerName, 1500, playerCharacter);
    player->attachObserver(this);
    players.push_back(player);
}

void BoardDisplay::loadPlayer(string playerName, string playerCharacter, int money, int boardPosition, int timsCups, int dcline, int dclinepos)
{
    Player* player = new Player(playerName, money, boardPosition, playerCharacter, timsCups, dcline, dclinepos);
    player->attachObserver(this);
    players.push_back(player);
}

Square *BoardDisplay::getSquare(int index)
{
    return squares[index];
}

Player* BoardDisplay::getPlayer(int playerId)
{
    Player* player = players.at(playerId);
    return player;
}

Player *BoardDisplay::getPlayer(string playerName)
{
    for(size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->getName() == playerName)
        {
            Player* p = players[i];
            return p;
        }
    }
    return nullptr;
}

Player *BoardDisplay::getPlayerOnCharacter(string gameCharacter)
{
    for(size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->getGameCharacter() == gameCharacter)
        {
            Player* p = players[i];
            return p;
        }
    }
    return nullptr; 
}

int BoardDisplay::getTotalNumberOfPlayers()
{
    return players.size();
}

//we get the owner of property from here
Player *BoardDisplay::getPropertyOwner(Property *property)
{
    for(size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->doesOwnProperty(property))
        {
            Player* p = players[i];
            return p;
        }
    }
    return nullptr;
}

vector<Property*> BoardDisplay::getProperties()
{
    vector<Property*> properties;
    for(int i = 0; i < 40; i++)
    {
        if(dynamic_cast<const Property*>(squares[i]) != nullptr)
        {
            properties.push_back(dynamic_cast<Property*>(squares[i]));
        }
    }
    return properties;
}

void BoardDisplay::attachPropertyToPlayer(string propertyName, string playerName, int improvementLevel, bool isMortgaged)
{
    int rents[22][6] = {
        {2, 10, 30, 90, 160, 250},
        {4, 20, 60, 180, 320, 450},
        {6, 30, 90, 270, 400, 550},
        {6, 30, 90, 270, 400, 550},
        {8, 40, 100, 300, 450, 600},
        {10, 50, 150, 450, 625, 750},
        {10, 50, 150, 450, 625, 750},
        {12, 60, 180, 500, 700, 900},
        {14, 70, 200, 550, 750, 950},
        {14, 70, 200, 550, 750, 950},
        {16, 80, 220, 600, 800, 1000},
        {18, 90, 250, 700, 875, 1050},
        {18, 90, 250, 700, 875, 1050},
        {20, 100, 300, 750, 925, 1100},
        {22, 110, 330, 800, 975, 1150},
        {22, 110, 330, 800, 975, 1150},
        {24, 120, 360, 850, 1025, 1200},
        {26, 130, 390, 900, 1100, 1275},
        {26, 130, 390, 900, 1100, 1275},
        {28, 150, 450, 1000, 1200, 1400},
        {35, 175, 500, 1100, 1300, 1500},
        {50, 200, 600, 1400, 1700, 2000},
    };
    string names[22] = {"AL", "ML", "ECH", "PAS", "HH", "RCH", "DWE", "CPH", "LHI", "BMH", "OPT", "EV1", "EV2", "EV3", "PHYS", "B1", "B2", "EIT", "ESC", "C2", "MC", "DC"};
    Player* player;
    for(size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->getName() == playerName)
        {
            player = players[i];
            break;
        }
    }
    for(int i = 0; i < 40; i++)
    {
        if(squares[i]->getName() == propertyName)
        {
            Property* property = dynamic_cast<Property*>(squares[i]);
            property->purchaseProperty();
            if(isMortgaged)
            {
                property->mortgageProperty();
            }
            player->loadPropertyToOwned(property);
            if(dynamic_cast<ImproveableProperty*>(squares[i]) != NULL)
            {
                for(int j = 0; j < 22; j++)
                {
                    if(names[j] == property->getName())
                    {
                        dynamic_cast<ImproveableProperty*>(squares[i])->loadImprovementToProperty(improvementLevel, rents[j][improvementLevel]);
                        break;
                    }
                }
            }
            break;
        }
    }
}

void BoardDisplay::performAuction(Player* currentPlayer, Property* property)
{
    cout << endl << "Performing Auction" << endl;
    vector<Player*> auctionPlayers;
    for(size_t i = 0; i < players.size(); i++)
    {
        if(players[i]->getName() != currentPlayer->getName())
        {
            auctionPlayers.push_back(players[i]);
        }
    }
    int bidAmount = 0;
    size_t ind = 0;
    while(auctionPlayers.size() != 1)
    {
        cout << "Current Bid Amount is " << bidAmount << endl;
        cout << auctionPlayers[ind]->getName() << " place your bid. Enter price higher than current bid amount to continue or otherwise enter an equal or smaller amount to exit: ";
        int proposedBid;
        while(true)
        {
            cin >> proposedBid;
            if(proposedBid > auctionPlayers[ind]->getSavings())
            {
                cout << "You donot have enough money to place this bid. Please enter a lower amount: ";
                continue;
            }
            break;
        }
        if(proposedBid <= bidAmount)
        {
            cout << "Bid not accepted moving out of auction" << endl;
            auctionPlayers.erase(std::next(auctionPlayers.begin(), ind));
            if(ind == auctionPlayers.size())
            {
                ind = 0;
            }
        }
        else
        {
            bidAmount = proposedBid;
            cout << "New Highest Bid placed: " << bidAmount << endl;
            ind++;
            if(ind == auctionPlayers.size())
            {
                ind = 0;
            }
        }
    }
    if(bidAmount == 0)
    {
        cout << auctionPlayers[ind]->getName() << " place your bid. Enter price higher than current bid amount to continue or otherwise enter an equal or smaller amount to exit: ";
        int proposedBid;
        while(true)
        {
            cin >> proposedBid;
            if(proposedBid > auctionPlayers[ind]->getSavings())
            {
                cout << "You donot have enough money to place this bid. Please enter a lower amount: ";
                continue;
            }
            break;
        }
        if(proposedBid <= 0)
        {
            cout << "No one won the bid" << endl;
        }
        else
        {
            bidAmount = proposedBid;
            cout << auctionPlayers[0]->getName() << " won the bid" << endl;
            auctionPlayers[0]->payMoney(bidAmount);
            property->unmortgageProperty();
            property->purchaseProperty();
            auctionPlayers[0]->loadPropertyToOwned(property);
        }
    }
    else
    {
        cout << auctionPlayers[0]->getName() << " won the bid" << endl;
        auctionPlayers[0]->payMoney(bidAmount);
        property->unmortgageProperty();
        property->purchaseProperty();
        auctionPlayers[0]->loadPropertyToOwned(property);
    }
}
