#ifndef IMPROVEABLE_PROPERTY_H

#define IMPROVEABLE_PROPERTY_H

#include "Property.h"
class ImproveableProperty : public Property 
{
private:
    int tutionFee;
    int improvementLevel;
    int improvementCost;
public:
    ImproveableProperty();
    ImproveableProperty(string name, int purchaseCost, string monopolyBlock, int tutionFee, int improvementCost);
    void setTutionFee(int tutionFee);
    void increaseImprovementLevel(int increment);
    void decreaseImprovementLevel(int decrement);
    int getFee();
    int getImprovementLevel();
    void displayProperty();
    int getImprovementCost();
    void loadImprovementToProperty(int level, int fee);
};
#endif
