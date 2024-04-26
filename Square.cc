#include "Square.h"

Square::Square()
{
    name = "";
}

Square::~Square(){}

Square::Square(string name)
{
    this->name = name;
}

string Square::getName()
{
    return name;
}

void Square::setName(string name)
{
    this->name = name;
}
