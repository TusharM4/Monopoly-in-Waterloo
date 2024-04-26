#ifndef NEEDLES_HALL_H
#define NEEDLES_HALL_H
#include "NonProperty.h"

class NeedlesHall : public NonProperty
{
public:
    NeedlesHall();
    NeedlesHall(string name);
    void performAction(Player* player);
};
#endif
