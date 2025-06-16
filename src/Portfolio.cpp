#include "Portfolio.hh"
#include "Deal.hh"
#include "Lender.hh"

Portfolio::Portfolio(Currency cur) : currency(cur) {}

void Portfolio::setLender(Lender *l)
{
    lender = l;
}
void Portfolio::addDeal(Deal *d)
{
    if (d == nullptr)
    {
        throw std::runtime_error("Cannot add a null deal to the portfolio.");
    }
    deals.push_back(d);
}

double Portfolio::calculateTotalInterest() const
{
    double totalInterest = 0.0;
    if (deals.empty())
    {
        return totalInterest; // Return 0 if there are no deals
    }
    for (Deal *deal : deals)
    {
        for (const Facility &facility : deal->getFacilities())
        {
            std::vector<Lender *> lenders = facility.getLenders();
            auto it = std::find(lenders.begin(), lenders.end(), lender);
            if (it != lenders.end())
            {
                totalInterest += exchange(facility.calculateInterest() / lenders.size(), facility.getCurrency(), currency);
            }
        }
    }
    return totalInterest;
}

double Portfolio::calculateTotalOriginalValue() const
{
    double totalValue = 0.0;
    if (deals.empty())
    {
        return totalValue;
    }
    for (Deal *deal : deals)
    {
        for (const Facility &facility : deal->getFacilities())
        {
            std::vector<Lender *> lenders = facility.getLenders();
            auto it = std::find(lenders.begin(), lenders.end(), lender);
            if (it != lenders.end())
            {
                totalValue += exchange(facility.getOriginalAmount() / lenders.size(), facility.getCurrency(), currency);
            }
        }
    }
    return totalValue;
}

double Portfolio::calculateTotalRemainingValue() const
{
    double totalValue = 0.0;
    if (deals.empty())
    {
        return totalValue;
    }
    for (Deal *deal : deals)
    {
        for (const Facility &facility : deal->getFacilities())
        {
            std::vector<Lender *> lenders = facility.getLenders();
            auto it = std::find(lenders.begin(), lenders.end(), lender);
            if (it != lenders.end())
            {
                totalValue += exchange(facility.getRemainingAmount() / lenders.size(), facility.getCurrency(), currency);
            }
        }
    }
    return totalValue;
}

void Portfolio::print(int levelIndent) const
{
    std::cout << std::string(levelIndent, ' ') << "Portfolio of Lender: " << (lender ? lender->getName() : "Unknown") << std::endl;
    std::cout << std::string(levelIndent + 2, ' ') << "Currency: " << currencyToString(currency) << std::endl;
    std::cout << std::string(levelIndent + 2, ' ') << "Number of Deals: " << deals.size() << std::endl;

    int activeDeals = 0;
    for (const Deal *deal : deals)
    {
        if (deal->getStatus() != Status::TERMINATED)
        {
            ++activeDeals;
        }
    }
    std::cout << std::string(levelIndent + 2, ' ') << "Number of Active Deals: " << activeDeals << std::endl;
    std::cout << std::string(levelIndent + 2, ' ') << "Total Interest: "
              << std::fixed << std::setprecision(2) << calculateTotalInterest() << " " << currencyToString(currency) << std::endl;
    std::cout << std::string(levelIndent + 2, ' ') << "Total Original Value: "
              << std::fixed << std::setprecision(2) << calculateTotalOriginalValue() << " " << currencyToString(currency) << std::endl;
    std::cout << std::string(levelIndent + 2, ' ') << "Total Remaining Value: "
              << std::fixed << std::setprecision(2) << calculateTotalRemainingValue() << " " << currencyToString(currency) << std::endl;
}