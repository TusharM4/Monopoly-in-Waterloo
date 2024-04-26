#include "NeedlesHall.h"

NeedlesHall::NeedlesHall() {}
NeedlesHall::NeedlesHall(string name): NonProperty(name) {}

void NeedlesHall::performAction(Player* player)
{
    cout << "Player used Needles Hall" << endl; 
    int randomNumber = 1 + rand() % 100;
    if(randomNumber >= 1 && randomNumber <= 6)
    {
        cout << "Player loses $200 from their savings" << endl;
        player->payMoney(200);
    }
    else if(randomNumber >= 7 && randomNumber <= 17)
    {
        cout << "Player loses $100 from their savings" << endl;
        player->payMoney(100);
    }
    else if(randomNumber >= 18 && randomNumber <= 34)
    {
        cout << "Player loses $50 from their savings" << endl;
        player->payMoney(50);
    }
    else if(randomNumber >= 35 && randomNumber <= 67)
    {
        cout << "Player gain $25 in their savings" << endl;
        player->recieveMoney(25);
    }
    else if(randomNumber >= 68 && randomNumber <= 84)
    {
        cout << "Player gain $50 in their savings" << endl;
        player->recieveMoney(50);
    }
    else if(randomNumber >= 85 && randomNumber <= 95)
    {
        cout << "Player gain $100 in their savings" << endl;
        player->recieveMoney(100);
    }
    else if(randomNumber >= 96 && randomNumber <= 100)
    {
        cout << "Player gain $200 in their savings" << endl;
        player->recieveMoney(200);
    }
}
