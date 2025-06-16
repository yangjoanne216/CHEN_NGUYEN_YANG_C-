#pragma once
#include <iostream>
#include <string>
using namespace std;

class Borrower
{
private:
    string name;

public:
    Borrower(const string n);
    void print(int levelIndent) const;
    const string getName() const;
};