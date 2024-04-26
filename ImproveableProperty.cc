#include "ImproveableProperty.h"

ImproveableProperty::ImproveableProperty()
{
    tutionFee = 0;
    improvementLevel = 0;
    improvementCost = 0;
}

ImproveableProperty::ImproveableProperty(string name, int purchaseCost, string monopolyBlock, int tutionFee, int improvementCost): Property(name, purchaseCost, monopolyBlock)
{
    this->tutionFee = tutionFee;
    improvementLevel = 0;
    this->improvementCost = improvementCost;
}


void ImproveableProperty::setTutionFee(int tutionFee)
{
    this->tutionFee = tutionFee;
}

void ImproveableProperty::increaseImprovementLevel(int increment)
{
    improvementLevel++;
    tutionFee += increment;
}

void ImproveableProperty::decreaseImprovementLevel(int decrement)
{
    improvementLevel--;
    tutionFee -= decrement;
}

int ImproveableProperty::getFee()
{
    return tutionFee;
}

int ImproveableProperty::getImprovementLevel()
{
    return improvementLevel;
}

void ImproveableProperty::displayProperty()
{
    cout << "Property Name: " << name << ", Fee: " << tutionFee << ", Improvement Level: " << improvementLevel << endl;
}

int ImproveableProperty::getImprovementCost()
{
    return improvementCost;
}

void ImproveableProperty::loadImprovementToProperty(int level, int fee)
{
    improvementLevel = level;
    tutionFee = fee;
}
