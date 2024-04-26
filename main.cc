#include "WatopolyGame.h"
#include <cstdlib> 
#include <unistd.h>

int main(int argc, char* argv[])
{
    int seed = getpid();   // Setting up random number generation
	srand(seed);
    bool testing = false;
    bool loadfile = false;
    string fileName = ""; 
    if (argc > 1) {
		for (int i = 0; i < argc; ++i) {
			string com = argv[i];
			if (com == "-testing") {     // Process for testing
				testing = true;
			}
            if (com == "-load") {         // Process for load file
				loadfile = true;
				fileName = argv[i + 1];
            }
        }
    }
    WatopolyGame* game;
    if(loadfile)
    {
        game = new WatopolyGame(fileName);
    }
    else
    {
        vector<string> names;
        names.push_back("Goose");
        names.push_back("GRT Bus");
        names.push_back("Tim Hortons Doughnut");
        names.push_back("Professor");
        names.push_back("Student");
        names.push_back("Money");
        names.push_back("Laptop");
        names.push_back("Pink tie");

        vector<string> characters;
        characters.push_back("G");
        characters.push_back("B");
        characters.push_back("D");
        characters.push_back("P");
        characters.push_back("S");
        characters.push_back("$");
        characters.push_back("L");
        characters.push_back("T");
        
        string* playerNames;
        string* playerCharacters;
        int numberOfPlayers;
        while(true)
        {
            cout << "Please enter number of players: ";
            cin >> numberOfPlayers;
            if(numberOfPlayers < 2 || numberOfPlayers > 6)
            {
                cout << "Number of players can be 2 - 6. Please input again" << endl;
            }
            else
            {
                break;
            }
        }
        playerNames = new string[numberOfPlayers];
        playerCharacters = new string[numberOfPlayers];
        for(int i = 1; i <= numberOfPlayers; i++)
        {
            while(1)
            {
                int choice;
                for(size_t j = 0; j < names.size(); j++)
                {
                    cout << "Enter " << j + 1 << " to select " << names[j] << " as your character." << endl;
                }
                cout << "Please choose your character Player # " << i << ": ";
                cin >> choice;
                int size = names.size();
                if(choice < 1 || choice > size)
                {
                    cout << "Invalid choice entered.\n";
                }
                else
                {
                    cout << "Your Game Character is " << characters[choice - 1] << endl;
                    playerNames[i - 1] = names[choice - 1]; 
                    playerCharacters[i - 1] = characters[choice - 1];
                    names.erase(std::next(names.begin(), choice - 1));
                    characters.erase(std::next(characters.begin(), choice - 1));
                    break;
                }
            }
        }
        game = new WatopolyGame(numberOfPlayers, playerNames, playerCharacters);
        delete[] playerCharacters;
        delete[] playerNames;
    }
    game->getBoard()->displayBoard();
    cout << game->getCurrentPlayer()->getName() << ", its your turn" << endl;
    string input;
    while(cin >> input)
    {
        if(input == "roll")
        {
            game->rollDice(testing);
        }
        else if(input == "assets")
        {
            game->assets();
        }
        else if(input == "next")
        {
            game->next();
        }
        else if(input == "improve")
        {
            string propertyName = "";
            cin >> propertyName;
            string improvementType;
            cin >> improvementType;
            if(improvementType == "buy")
            {
                game->improve(propertyName, true);
            }
            else if(improvementType == "sell")
            {
                game->improve(propertyName, false);
            }
            else
            {
                cout << "Invalid improvement type given. Improvement type can only be buy or sell" << endl;
            }
            
        }
        else if(input == "mortgage")
        {
            string propertyName = "";
            cin >> propertyName;
            game->mortgage(propertyName);
        }
        else if(input == "unmortgage")
        {
            string propertyName = "";
            cin >> propertyName;
            game->unmortgage(propertyName);
        }
        else if(input == "save")
        {
            string fileName;
            cin >> fileName;
            cout << fileName << endl;
            game->save(fileName);
        }
        else if(input == "trade")
        {
            string name, give, recieve;
            cin >> name;
            cin >> give;
            cin >> recieve;
            game->trade(name, give, recieve);
        }
        else if(input == "all")
        {
            game->all();
        }
    }
    delete game;
}
