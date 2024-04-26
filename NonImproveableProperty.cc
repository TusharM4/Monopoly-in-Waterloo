#include "NonImproveableProperty.h"

NonImproveableProperty::NonImproveableProperty()
{
    rent = 0;
}

NonImproveableProperty::NonImproveableProperty(string name, int purchaseCost, string monopolyBlock, int rent): Property(name, purchaseCost, monopolyBlock)
{
    this->rent = rent;
}

int NonImproveableProperty::getFee()
{
    return rent;
}

void NonImproveableProperty::displayProperty()
{

    if (rent == -1) {
        cout << "Property Name: " << name << ", Rent: Calculated on Dice Roll" << endl;
    }   
    else {
        cout << "Property Name: " << name << ", Rent: " << rent << endl;    
    }
}
