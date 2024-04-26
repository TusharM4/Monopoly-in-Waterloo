#include "SLC.h"

SLC::SLC() {}
SLC::SLC(string name): NonProperty(name) {}

void SLC::performAction(Player* player)
{
    cout << "Player used SLC" << endl; 
    int randomNumber = 1 + rand() % 204;
    if(randomNumber >= 1 && randomNumber <= 25)
    {
        cout << "Players moves back 3 positions" << endl;
        player->movePlayer(-3);
    }
    else if(randomNumber >= 26 && randomNumber <= 59)
    {
        cout << "Players moves back 2 positions" << endl;
        player->movePlayer(-2);
    }
    else if(randomNumber >= 60 && randomNumber <= 93)
    {
        cout << "Players moves back 1 position" << endl;
        player->movePlayer(-1);
    }
    else if(randomNumber >= 94 && randomNumber <= 119)
    {
        cout << "Players moves forward 1 position" << endl;
        player->movePlayer(1);
    }
    else if(randomNumber >= 120 && randomNumber <= 153)
    {
        cout << "Players moves forward 2 positions" << endl;
        player->movePlayer(2);
    }
    else if(randomNumber >= 154 && randomNumber <= 187)
    {
        cout << "Players moves forward 3 positions" << endl;
        player->movePlayer(3);
    }
    else if(randomNumber >= 188 && randomNumber <= 196)
    {
        cout << "Player moves to Go to DC Tims Line" << endl;
        player->movePlayer(50 - player->getBoardPosition());
    }
    else if(randomNumber >= 196 && randomNumber <= 204)
    {
        cout << "Player moves to Advance to Collect OSAP" << endl;
        player->movePlayer(40 - player->getBoardPosition());
    }
    
}
