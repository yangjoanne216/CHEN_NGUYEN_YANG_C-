#include "Agent.hh"
#include "Lender.hh" // Assuming Lender is defined in this header

Agent::Agent(Lender *l) : lender(l) {}

void Agent::print() const
{
    if (lender)
    {
        lender->print(); // Assuming levelIndent is 2 for Agent
    }
    else
    {
        std::cout << "No lender assigned to this agent." << std::endl;
    }
}

const string Agent::getName() const
{
    return lender->getName();
}

Lender *Agent::getLender()
{
    return lender;
}