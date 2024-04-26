#ifndef SQUARE_H
#define SQUARE_H
#include <iostream>

using namespace std;

class Square
{
protected:
    string name;
public:
    Square();
    virtual ~Square();
    Square(string name);
    string getName();
    void setName(string name);
    virtual int getFee() = 0;
};
#endif
