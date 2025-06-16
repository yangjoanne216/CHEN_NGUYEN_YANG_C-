#pragma once
#include <string>
#include <iostream>
using namespace std;

class Lender; // Forward declaration
class Agent
{
private:
    Lender *lender;

public:
    explicit Agent(Lender *l);
    void print() const;
    const string getName() const;
    Lender *getLender();
};
