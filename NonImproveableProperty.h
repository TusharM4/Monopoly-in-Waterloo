#ifndef NONIMPROVEABLE_PROPERTY_H
#define NONIMPROVEABLE_PROPERTY_H
#include "Property.h"

class NonImproveableProperty : public Property
{
private:
    int rent;
public:
    NonImproveableProperty();
    NonImproveableProperty(string name, int purchaseCost, string monopolyBlock, int rent);
    int getFee();
    void displayProperty();
};
#endif
