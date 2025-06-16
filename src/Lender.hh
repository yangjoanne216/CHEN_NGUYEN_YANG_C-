#pragma once

#include <string>
#include "Portfolio.hh"

class Lender
{
private:
    std::string name;
    Portfolio portfolio;

public:
    explicit Lender(const std::string n, Portfolio p);
    void print() const;
    const std::string getName() const;
    Portfolio *getPortfolio();
};