#pragma once
#include <string>
#include <iostream>

class Lender; // Forward declaration
class Pool
{
private:
    Lender *lender;

public:
    explicit Pool(Lender *l);
    void print() const;
    const std::string getName() const;
    Lender *getLender();
};
