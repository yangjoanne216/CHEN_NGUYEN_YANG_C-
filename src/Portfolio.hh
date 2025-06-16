#pragma once

#include <vector>
#include <iostream>
#include <stdexcept>
#include "Currency.hh"

class Lender; // Forward declaration to avoid circular dependency
class Deal;   // Forward declaration to avoid circular dependency
class Portfolio
{
private:
    std::vector<Deal *> deals;
    Lender *lender;
    Currency currency;

public:
    explicit Portfolio(Currency cur);
    void setLender(Lender *l);
    void addDeal(Deal *d);
    double calculateTotalInterest() const;
    double calculateTotalOriginalValue() const;
    double calculateTotalRemainingValue() const;
    void print(int levelIndent) const;
};