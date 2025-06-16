#include "Pool.hh"
#include <iostream>
#include "Lender.hh"

Pool::Pool(Lender *l) : lender(l) {}

void Pool::print() const
{
    std::cout << "Pool managed by: ";
    if (lender)
    {
        lender->print();
    }
    else
    {
        std::cout << "No lender assigned." << std::endl;
    }
}

const std::string Pool::getName() const
{
    return lender->getName();
}

Lender *Pool::getLender()
{
    return lender;
}