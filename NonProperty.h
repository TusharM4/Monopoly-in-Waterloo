#ifndef NON_PROPERTY_H
#define NON_PROPERTY_H
#include <iostream>
#include "Square.h"

class Player;

class NonProperty: public Square
{
public:
    NonProperty();
    NonProperty(string name);
    int getFee();
    virtual void performAction(Player* cur_player);

};
#include "Player.h"

#endif
