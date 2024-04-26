#ifndef OBSERVER_H
#define OBSERVER_H

class Player;
class Observer
{
public:
    virtual void update(Player* currentPlayer, int diceRolled) = 0;
};

#endif
