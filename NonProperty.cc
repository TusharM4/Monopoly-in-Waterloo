#include "NonProperty.h"

NonProperty::NonProperty() {}

NonProperty::NonProperty(string name) : Square(name) {}

int NonProperty::getFee()
{
    return 0;
}

void NonProperty::performAction(Player* cur_player)
{
    if(name == "COLLECT OSAP"){
        cout << "You collected $200 from OSAP!" << endl;
        cur_player->recieveMoney(200);
    }
    else if(name == "TUITION"){
        cout << "Would you like to pay $300 or " << 0.10 * cur_player->getSavings() << "? Enter 300 or other."  <<endl;
        string s;
        cin >> s;
        if (s == "300") {
            if(300 > cur_player->getSavings()){
                cout << "You do not have enough money!" << endl;
                //bankrupt(cur_player);
            } else{
                cout << "You payed $300!" << endl;
                cur_player->payMoney(300);
            }
        }
        else{
            cout << "You payed $" << 0.10 * cur_player->getSavings() << endl;
            cur_player->payMoney(0.10 * cur_player->getSavings());    
        }        
    }
    else if(name == "DC TIMS LINE"){
        cout << "Why are you visiting the DC times line?" << endl;
    }
    else if(name == "GOOSE NESTING"){
        cout << "You are safe from the geese!" << endl;
    }
    else if(name == "GO TO TIMS"){
        cout << "You are being sent to the DC tims line!" << endl;
        cur_player->dc();
    }
    else if(name == "COOP FEE"){
        cout << "You have to pay $150 for your CO-OP fee!" << endl;
        if(150 > cur_player->getSavings()){
            cout << "You do not have enough money!" << endl;
            //bankrupt(cur_player);
        }
        cur_player->payMoney(150);
    }
}


