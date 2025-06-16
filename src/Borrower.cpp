#include "Borrower.hh"

Borrower::Borrower(const string n) : name(n) {}
void Borrower::print(int levelIndent) const
{
    std::cout << std::string(levelIndent, ' ') << "Borrower: " << name << std::endl;
}
const string Borrower::getName() const
{
    return name;
}
