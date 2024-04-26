#include "WatopolyGame.h"

WatopolyGame::WatopolyGame(int numberOfPlayers, string* playerNames, string* playerCharacters)
{
    srand(time(0));
    for(int i = 0; i < numberOfPlayers; i++)
    {
        board.addPlayer(playerNames[i], playerCharacters[i]);
    }
    currentPlayerTurn = 0;
}

WatopolyGame::WatopolyGame(string fileName)
{
    srand(time(0));
    ifstream inputFile;
    inputFile.open(fileName);
    string line;
    getline(inputFile, line);
    int numberOfPlayers = stoi(line);
    for(int i = 0; i < numberOfPlayers; i++)
    {
        getline(inputFile, line);   
        string name = "";
        size_t j = 1;
        for(;line[j] != '\''; j++)
        {
            name += line[j];
        }
        string gameCharacter;
        for(j+= 2;line[j] != ' '; j++)
        {
            gameCharacter += line[j];
        }
        string timsCups = "";
        for(j++;line[j] != ' '; j++)
        {
            timsCups += line[j];
        }
        string money;
        for(j++;line[j] != ' '; j++)
        {
            money += line[j];
        }
        string position;
        for(j++;j < line.length() && line[j] != ' '; j++)
        {
            position += line[j];
        }
        if(position == "10" && line[j] == ' ')
        {
            string dcline = "";
            string dclinePos = "";
            for(j++;j < line.length() && line[j] != ' '; j++)
            {
                dcline += line[j];
            }
            if(dcline == "1" && line[j] == ' ')
            {
                
                for(j++;j < line.length(); j++)
                {
                    dclinePos += line[j];
                }
            }
            board.loadPlayer(name, gameCharacter, stoi(money), stoi(position), stoi(timsCups), stoi(dcline), stoi(dclinePos));
        }
        else
        {
            board.loadPlayer(name, gameCharacter, stoi(money), stoi(position), stoi(timsCups), 0, 0);
        }
    }
    while(getline(inputFile, line))
    {
        string propertyName = "";
        int j = 0;
        for(;line[j] != ' '; j++)
        {
            propertyName += line[j];
        }
        string playerName = "";
        for(j+=2;line[j] != '\''; j++)
        {
            playerName += line[j];
        }
        string improvement = "";
        for (std::string::size_type j = j + 2; j < line.length(); j++)
        {
            improvement += line[j];
        }
        if(playerName == "BANK")
        {
            continue;
        }
        if(improvement == "-1")
        {
            board.attachPropertyToPlayer(propertyName, playerName, stoi(improvement), true);
        }
        else
        {
            board.attachPropertyToPlayer(propertyName, playerName, stoi(improvement), false);
        }
    }


    inputFile.close();
}

void WatopolyGame::inDC(int r1, int r2, Player* currentPlayer) {
    if (r1 == r2) {
        currentPlayer->setDC(0);
        currentPlayer->setDCpos(0);
        currentPlayer->setDoubles(0);
        cout << "You're free!" << endl;
        return;
    }
    if (currentPlayer->getDCpos() == 2) {
        if (currentPlayer->getCups() > 0) {
            cout << "You must pay $50 or use a Tims cup. Type 'pay' or 'cup'" << endl;
            string s;
            cin >> s;
            if (s == "cup") {
                currentPlayer->changeCups(-1);
            } else {
                currentPlayer->recieveMoney(-50);
            }
        } else {
            cout << "You have payed $50" << endl;
            currentPlayer->recieveMoney(-50);
        }
        currentPlayer->setDC(0);
        currentPlayer->setDCpos(0);
    } else {
        currentPlayer->setDCpos(currentPlayer->getDCpos() + 1);
    }   
}

void WatopolyGame::rollDice(bool testing)
{
    if (rolledOnce) {
        cout << "You have already rolled the dice in this turn. Use next to proceed to next player" << endl;
    } else {
        rolledOnce = true;
        Player* currentPlayer = board.getPlayer(currentPlayerTurn);
        int dice1 = 0;
        int dice2 = 0;
        if(testing)
        {
            cin >> dice1;
            cin >> dice2;
            if (dice1 == dice2) {
                currentPlayer->setDoubles(currentPlayer->getDoubles() + 1);
            } else {
                currentPlayer->setDoubles(0);
            }
            if (currentPlayer->getDCline() == 1) {
                inDC(dice1, dice2, currentPlayer);
                if (currentPlayer->getDCline() == 1) {
                    next();
                    return;
                }
            }
        }
        else
        {
            dice1 = 1 + rand() % 6;
            dice2 = 1 + rand() % 6;
            if (dice1 == dice2) {
                currentPlayer->setDoubles(currentPlayer->getDoubles() + 1);
            } else {
                currentPlayer->setDoubles(0);
            }
            if (currentPlayer->getDCline() == 1) {
                inDC(dice1, dice2, currentPlayer);
                if (currentPlayer->getDCline() == 1) {
                    next();
                    return;
                }
            }
        }
        int result = dice1 + dice2;

        if (currentPlayer->getDoubles() == 3) {
            currentPlayer->dc();
            board.displayBoard();
            cout << "Dice 1 rolled out: " << dice1 << endl;
            cout << "Dice 2 rolled out: " << dice2 << endl;
            cout << "You're stuck in DC Line :(" << endl;
            next();
        } else {
            cout << "Dice 1 rolled out: " << dice1 << endl;
            cout << "Dice 2 rolled out: " << dice2 << endl;
            currentPlayer->movePlayer(result);
            board.displayBoard();
        }
    }
}

void WatopolyGame::trade(string name, string give, string recieve)
{
    if(board.getPlayerOnCharacter(name) == nullptr)
    {
        cout << "No player with Game Character " << name << " found." << endl;
        return;
    }
    name = board.getPlayerOnCharacter(name)->getName();
    if(recieve[0] <= '9' && recieve[0] >= '0' && give[0] <= '9' && give[0] >= '0')
    {
        cout << "You cannot trade money for money" << endl;
    }
    else if(give[0] <= '9' && give[0] >= '0')
    {
        int giveAmount = stoi(give);
        if(board.getPlayer(currentPlayerTurn)->getSavings() < giveAmount)
        {
            cout << "You donot have enough money to perform the trade" << endl;
            return; 
        }
        if(board.getPlayer(name)->getOwnedProperty(recieve) == nullptr)
        {
            cout << "Player " << name << " doesnot own " << recieve << endl;
            return;
        }
        vector<Property*> properties = board.getPlayer(name)->getSimilarMonopolyBlockProperties(board.getPlayer(name)->getOwnedProperty(recieve));
        for(size_t i = 0; i < properties.size(); i++)
        {
            if(dynamic_cast<ImproveableProperty*>(properties[i])->getImprovementLevel() != 0)
            {
                cout << recieve << " or a property in its monopoly block has improvements. Those improvements need to be sold to continue" << endl;
                return;
            }
        }
        cout << "Player " << name << ", Player " << board.getPlayer(currentPlayerTurn)->getName() << " is offering you $" << give << " for your property " << recieve << endl;
        cout << "Enter Y to accept trade or any other to skip" << endl;
        string input;
        cin >> input;
        if(input == "Y" || input == "y")
        {
            Property* prop = board.getPlayer(name)->getOwnedProperty(recieve);
            board.getPlayer(name)->sellProperty(prop);
            prop->purchaseProperty();
            board.getPlayer(currentPlayerTurn)->loadPropertyToOwned(prop);
            board.getPlayer(name)->recieveMoney(giveAmount);
            board.getPlayer(currentPlayerTurn)->payMoney(giveAmount);
    
        }
    }
    else if(recieve[0] <= '9' && recieve[0] >= '0')
    {
        int recievemount = stoi(recieve);
        if(board.getPlayer(currentPlayerTurn)->getOwnedProperty(give) == nullptr)
        {
            cout << "You do not own " << give << endl;
            return;
        }
        if(board.getPlayer(name)->getSavings() < recievemount)
        {
            cout << "Player " << name << " does not have enough money to perform the trade" << endl;
            return; 
        }
        vector<Property*> properties = board.getPlayer(currentPlayerTurn)->getSimilarMonopolyBlockProperties(board.getPlayer(currentPlayerTurn)->getOwnedProperty(give));
        for(size_t i = 0; i < properties.size(); i++)
        {
            if(dynamic_cast<ImproveableProperty*>(properties[i])->getImprovementLevel() != 0)
            {
                cout << give << " or a property in its monopoly block has improvements. Those improvements need to be sold to continue" << endl;
                return;
            }
        }
        cout << "Player " << name << ", Player " << board.getPlayer(currentPlayerTurn)->getName() << " is offering you his property " << give << " for $" << recieve << endl;
        cout << "Enter Y to accept trade or any other to skip" << endl;
        string input;
        cin >> input;
        if(input == "Y" || input == "y")
        {
            Property* prop = board.getPlayer(currentPlayerTurn)->getOwnedProperty(give);
            board.getPlayer(currentPlayerTurn)->sellProperty(prop);
            prop->purchaseProperty();
            board.getPlayer(name)->loadPropertyToOwned(prop);
            board.getPlayer(currentPlayerTurn)->recieveMoney(recievemount);
            board.getPlayer(name)->payMoney(recievemount);
    
        }
    }
    else
    {
        if(board.getPlayer(currentPlayerTurn)->getOwnedProperty(give) == nullptr)
        {
            cout << "You do not own " << give << endl;
            return;
        }
        if(board.getPlayer(name)->getOwnedProperty(recieve) == nullptr)
        {
            cout << "Player " << name << " doesnot own " << recieve << endl;
            return;
        }
        vector<Property*> properties = board.getPlayer(name)->getSimilarMonopolyBlockProperties(board.getPlayer(name)->getOwnedProperty(recieve));
        for(size_t i = 0; i < properties.size(); i++)
        {
            if(dynamic_cast<ImproveableProperty*>(properties[i])->getImprovementLevel() != 0)
            {
                cout << recieve << " or a property in its monopoly block has improvements. Those improvements need to be sold to continue" << endl;
                return;
            }
        }
        properties = board.getPlayer(currentPlayerTurn)->getSimilarMonopolyBlockProperties(board.getPlayer(currentPlayerTurn)->getOwnedProperty(give));
        for(size_t i = 0; i < properties.size(); i++)
        {
            if(dynamic_cast<ImproveableProperty*>(properties[i])->getImprovementLevel() != 0)
            {
                cout << give << " or a property in its monopoly block has improvements. Those improvements need to be sold to continue" << endl;
                return;
            }
        }
        cout << "Player " << name << ", Player " << board.getPlayer(currentPlayerTurn)->getName() << " is offering you his property " << give << " for you property " << recieve << endl;
        cout << "Enter Y to accept trade or any other to skip" << endl;
        string input;
        cin >> input;
        if(input == "Y" || input == "y")
        {
            Property* propGive = board.getPlayer(currentPlayerTurn)->getOwnedProperty(give);
            board.getPlayer(currentPlayerTurn)->sellProperty(propGive);
            propGive->purchaseProperty();

            Property* propRecieve = board.getPlayer(name)->getOwnedProperty(recieve);
            board.getPlayer(name)->sellProperty(propRecieve);
            propRecieve->purchaseProperty();

            board.getPlayer(name)->loadPropertyToOwned(propGive);
            board.getPlayer(currentPlayerTurn)->loadPropertyToOwned(propRecieve);
        }
    }
}

void WatopolyGame::improve(string propertyName, bool toBeBought)
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
    Property* prop = board.getPlayer(currentPlayerTurn)->getOwnedProperty(propertyName);
    vector<Property*> monopolyProperties = board.getPlayer(currentPlayerTurn)->getSimilarMonopolyBlockProperties(prop);
    if((monopolyProperties.size() == 3 || (monopolyProperties.size() == 2 && prop->getMonopolyBlock() == "Arts1") || (monopolyProperties.size() == 2 && prop->getMonopolyBlock() == "Math")))
    {
        
    }
    else
    {
        cout << "You donot own monopoly of these properties" << endl;
        return;
    }
    if(prop == nullptr)
    {
        cout << "You cannot improve this property becuase you donot own any property with such name" << endl;
    }
    else
    {
        if(dynamic_cast<ImproveableProperty*>(prop) != nullptr)
        {
            ImproveableProperty* improveableProp = dynamic_cast<ImproveableProperty*>(prop);
            if(toBeBought)
            {
                if(improveableProp->getImprovementLevel() == 5)
                {
                    cout << "Max improvements already made. Cant make more improvements" << endl;
                    return;
                }
                int feeIncrement = 0;
                for(int i = 0; i < 22; i++)
                {
                    if(names[i] == propertyName)
                    {
                        feeIncrement = rents[i][improveableProp->getImprovementLevel() + 1] - rents[i][improveableProp->getImprovementLevel()];
                        break;
                    }
                }
                if(board.getPlayer(currentPlayerTurn)->getSavings() < improveableProp->getImprovementCost())
                {
                    cout << "You donot have enough money to improve your property" << endl;
                    return;
                }
                board.getPlayer(currentPlayerTurn)->payMoney(improveableProp->getImprovementCost());
                improveableProp->increaseImprovementLevel(feeIncrement);
                cout << propertyName << " improvement has been bought" << endl;
            }
            else
            {
                if(improveableProp->getImprovementLevel() == 0)
                {
                    cout << "No improvements found. Cant sell any improvements" << endl;
                    return;
                }
                int feeDecrement = 0;
                for(int i = 0; i < 22; i++)
                {
                    if(names[i] == propertyName)
                    {
                        feeDecrement = rents[i][improveableProp->getImprovementLevel()] - rents[i][improveableProp->getImprovementLevel() - 1];
                        break;
                    }
                }
                board.getPlayer(currentPlayerTurn)->recieveMoney(improveableProp->getImprovementCost() / 2);
                improveableProp->decreaseImprovementLevel(feeDecrement);
                cout << propertyName << " improvement has been sold" << endl;
            }
        }
        else
        {
            cout << "Property is not an improveable property" << endl;
        }
    }
}

void WatopolyGame::mortgage(string propertyName)
{
    //Check if the property exists and turn property rent off
    if (board.getPlayer(currentPlayerTurn)->getOwnedProperty(propertyName) == nullptr){
        cout << "You do not own this property!" << endl;
    }
    else {
        Property* prop = board.getPlayer(currentPlayerTurn)->getOwnedProperty(propertyName);
        if(dynamic_cast<ImproveableProperty*>(prop) != nullptr && dynamic_cast<ImproveableProperty*>(prop)->getImprovementLevel() != 0){
            cout << "Sell improvements before mortgaging!" << endl;
        } else if (prop->getIsOwned() && board.getPlayer(currentPlayerTurn)->doesOwnProperty(prop)){
            if(!prop->getMortgaged()){
                cout << "The property is now mortgaged and you have recieved $" << prop->getPurchaseCost()/2<< endl;
                board.getPlayer(currentPlayerTurn)->recieveMoney(prop->getPurchaseCost()/2);
                prop->mortgageProperty();
            } else{
                cout << "This property is already mortgaged!" << endl;
            }
        } else if (!board.getPlayer(currentPlayerTurn)->doesOwnProperty(prop) || !prop->getIsOwned()){
            cout << "You do not own this property!" << endl;
        }
    }
}

void WatopolyGame::unmortgage(string propertyName)
{
    //Check if the property exists
    if (board.getPlayer(currentPlayerTurn)->getOwnedProperty(propertyName) == nullptr){
        cout << "You do not own this property!" << endl;
    }
    else {
        Property* prop = board.getPlayer(currentPlayerTurn)->getOwnedProperty(propertyName);
        if (prop->getIsOwned() && board.getPlayer(currentPlayerTurn)->doesOwnProperty(prop)){
            if(prop->getMortgaged()){
                cout << "You have to pay $" << prop->getPurchaseCost()/2 * 0.6 << " to unmortgaged the property." << endl;
                if(prop->getPurchaseCost() * 0.6 > board.getPlayer(currentPlayerTurn)->getSavings()){
                    cout << "You do not have enough money!" << endl;
                } else{
                    board.getPlayer(currentPlayerTurn)->payMoney(prop->getPurchaseCost() * 0.6);
                    prop->unmortgageProperty();
                    cout << "The property is now unmortgaged!" << endl;
                }
            } else{
                cout << "This property is already unmortgaged!" << endl;
            }
        } else if (!board.getPlayer(currentPlayerTurn)->doesOwnProperty(prop) || !prop->getIsOwned()){
            cout << "You do not own this property!" << endl;
        } 
    } 
}

void WatopolyGame::assets()
{
    cout << "Savings: $" << board.getPlayer(currentPlayerTurn)->getSavings() << endl;
    board.getPlayer(currentPlayerTurn)->displayProperties();
}

void WatopolyGame::save(string filename)
{
    ofstream outputFile(filename);
    outputFile << board.getTotalNumberOfPlayers() << endl;
    for(int i = 0; i < board.getTotalNumberOfPlayers(); i++)
    {
        Player* p = board.getPlayer(i);
        outputFile << "'" << p->getName() <<  "' " << p->getGameCharacter() << " " << p->getCups() << " " << p->getSavings() << " " << p->getBoardPosition();
        if(p->getBoardPosition() == 10)
        {
            if (p->getDCline() == 1) {
            outputFile << " " << p->getDCline() << " " << p->getDCpos() << endl;
            } else {
                outputFile << " " << p->getDCline() << endl;
            }
        }
        else
        {
            outputFile << endl;
        }
    }
    vector<Property*> properties = board.getProperties();
    for(size_t i = 0; i < properties.size(); i++)
    {
        if(dynamic_cast<const ImproveableProperty*>(properties[i]) != nullptr)
        {
            ImproveableProperty* prop = dynamic_cast<ImproveableProperty*>(properties[i]);
            int improvement = prop->getImprovementLevel();
            if(prop->getMortgaged())
            {
                improvement = -1;
            }
            if(board.getPropertyOwner(prop) != nullptr)
            {
                outputFile << prop->getName() << " '" << board.getPropertyOwner(prop)->getName() << "' " << improvement << endl;
            }
            else
            {
                outputFile << prop->getName() << " 'BANK' " << improvement << endl;
            }
        }
        else
        {
            NonImproveableProperty* prop = dynamic_cast<NonImproveableProperty*>(properties[i]);
            int improvement = 0;
            if(prop->getMortgaged())
            {
                improvement = -1;
            }
            if(board.getPropertyOwner(prop) != nullptr)
            {
                outputFile << prop->getName() << " '" << board.getPropertyOwner(prop)->getName() << "' " << improvement << endl;
            }
            else
            {
                outputFile << prop->getName() << " 'BANK' " << improvement << endl;
            }
        }
    }
    cout << "Game Saved in " << filename << endl;
    outputFile.close();
}

BoardDisplay* WatopolyGame::getBoard()
{
    return &board;
}

void WatopolyGame::next()
{
    rolledOnce = false;
    currentPlayerTurn += 1;
    currentPlayerTurn = currentPlayerTurn % board.getTotalNumberOfPlayers();
    cout << board.getPlayer(currentPlayerTurn)->getName() << ", its your turn" << endl;
    Player* currentPlayer = board.getPlayer(currentPlayerTurn);
    string input;
    if (currentPlayer->getDCline() == 1) {
        bool payed = false;
        cout << "You are in the DC line.\nPay $50? Type 'yes' or 'no'." << endl;
        cin >> input;
        if (input == "yes") {
            currentPlayer->payMoney(-50);
            currentPlayer->setDC(0);
            currentPlayer->setDCpos(0);
            next();
            return;
            payed = true;
        } 
        if (currentPlayer->getCups() > 0 && payed == false) {
            cout << "Use a Tims Cup? Type 'yes' or 'no'." << endl;
            cin >> input;
            if (input == "yes") {
                currentPlayer->changeCups(-1);
                currentPlayer->setDC(0);
                currentPlayer->setDCpos(0);
                next();
            }
        }
        cout << "Roll for doubles" << endl;
    }
}

Player *WatopolyGame::getCurrentPlayer()
{
    return board.getPlayer(currentPlayerTurn);
}

void WatopolyGame::all()
{
    for(int i = 0; i < board.getTotalNumberOfPlayers(); i++)
    {
        cout << "Player Name: " << board.getPlayer(i)->getName() << endl;
        cout << "Savings: $" << board.getPlayer(i)->getSavings() << endl;
        board.getPlayer(i)->displayProperties();
        cout << endl;
    }
}
