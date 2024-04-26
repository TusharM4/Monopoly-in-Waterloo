#include "Property.h"

Property::Property()
{
    mortgaged = false;
    isOwned = false;
    purchaseCost = 0;
    monopolyBlock = "";
}

Property::Property(string name, int purchaseCost, string monopolyBlock) : Square(name)
{
    mortgaged = false;
    isOwned = false;
    this->purchaseCost = purchaseCost;
    this->monopolyBlock = monopolyBlock;
}

void Property::mortgageProperty()
{
    mortgaged = true;
    notify();
}

void Property::unmortgageProperty()
{
    mortgaged = false;
    notify();
}

void Property::purchaseProperty()
{
    isOwned = true;
}

void Property::sellProperty()
{
    isOwned = false;
}

void Property::setPurchaseCost(int purchaseCost)
{
    this->purchaseCost = purchaseCost;
}

void Property::setMonopolyBlock(string monopolyBlock)
{
    this->monopolyBlock = monopolyBlock;
}

bool Property::getMortgaged()
{
    return mortgaged;
}

bool Property::getIsOwned()
{
    return isOwned;
}

int Property::getPurchaseCost()
{
    return purchaseCost;
}

string Property::getMonopolyBlock()
{
    return monopolyBlock;
}

void Property::notify()
{
}
