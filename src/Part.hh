#pragma once

#include <string>
#include <iostream>
#include <iomanip>
#include "Currency.hh"

class Part
{
private:
    std::string payDate;
    double amount;
    Currency currency;

public:
    Part(const std::string &d, double a, Currency cur);
    void print(int levelIndent) const;
    const std::string getPayDate() const;
    double getAmount() const;
    Currency getCurrency() const;
};