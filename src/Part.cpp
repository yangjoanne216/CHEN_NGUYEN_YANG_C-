#include "Part.hh"
Part::Part(const std::string &d, double a, Currency cur) : payDate(d), amount(a), currency(cur) {}

void Part::print(int levelIndent) const
{
    std::cout << std::string(levelIndent, ' ') << "Part Payment Date: " << payDate << std::endl;
    std::cout << std::string(levelIndent, ' ') << "Amount: " << std::fixed << std::setprecision(2)
              << amount << " " << currencyToString(currency) << std::endl;
}

const std::string Part::getPayDate() const
{
    return payDate;
}

double Part::getAmount() const
{
    return amount;
}

Currency Part::getCurrency() const
{
    return currency;
}
