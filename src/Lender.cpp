#include "Lender.hh"
#include <iostream>

Lender::Lender(const std::string n, Portfolio p) : name(n), portfolio(p)
{
    portfolio.setLender(this);
}

void Lender::print() const
{
    std::cout << "Lender: " << name << std::endl;
}

const std::string Lender::getName() const
{
    return name;
}

Portfolio *Lender::getPortfolio()
{
    return &portfolio; // Return a pointer to the portfolio
}