#ifndef SLC_H
#define SLC_H
#include "NonProperty.h"

class SLC : public NonProperty
{
public:
    SLC();
    SLC(string name);
    void performAction(Player* player);
};
#endif
