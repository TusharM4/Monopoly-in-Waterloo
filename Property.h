#ifndef PROPERTY_H

#define PROPERTY_H
#include "Square.h"
class Property : public Square
{
protected:
    bool mortgaged;
    bool isOwned;
    int purchaseCost;
    string monopolyBlock;
public:
    Property();
    Property(string name, int purchaseCost, string monopolyBlock);
    void mortgageProperty();
    void unmortgageProperty();
    void purchaseProperty();
    void sellProperty();
    void setPurchaseCost(int purchaseCost);
    void setMonopolyBlock(string monopolyBlock);
    bool getMortgaged();
    bool getIsOwned();
    int getPurchaseCost();
    string getMonopolyBlock();
    virtual int getFee() = 0;
    virtual void displayProperty() = 0;
    void notify();
};
#endif
