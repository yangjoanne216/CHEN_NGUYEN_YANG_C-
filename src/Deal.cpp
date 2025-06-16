#include "Deal.hh"

Deal::Deal(const std::string &num, Agent ag,
           const std::vector<Pool> &p, Borrower *b, Currency cur,
           const std::string &sig, const std::string &end,
           const std::vector<Facility> fac)
    : contractNumber(num), agent(ag), pools(p), borrower(b),
      currency(cur), signatureDate(sig),
      endDate(end), facilities(fac)
{
    if (!isValidDateFormat(signatureDate))
    {
        throw std::runtime_error("Signature date format is invalid. Expected YYYY-MM-DD.");
    }
    if (!isValidDateFormat(endDate))
    {
        throw std::runtime_error("End date format is invalid. Expected YYYY-MM-DD.");
    }

    for (const Facility &facility : facilities)
    {
        if (dateStringToInt(facility.getStartDate()) > dateStringToInt(facility.getEndDate()))
        {
            throw std::runtime_error("Facility start date cannot be after end date");
        }
        if (facility.getOriginalAmount() <= 0)
        {
            throw std::runtime_error("Facility amount must be greater than zero");
        }
        if (facility.getNbParts() <= 0)
        {
            throw std::runtime_error("Facility must have at least one part");
        }
    }

    status = Status::ACTIVE;
    facilities[0].setStatus(Status::ACTIVE); // Set the first facility as active

    agent.getLender()->getPortfolio()->addDeal(this);
    for (Pool &pool : pools)
    {
        pool.getLender()->getPortfolio()->addDeal(this);
    }
}

void Deal::print(int levelIndent) const
{
    std::cout << std::string(levelIndent, ' ') << "+--------------------------+--------------------------+" << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Field                    | Value                    |" << std::endl;
    std::cout << std::string(levelIndent, ' ') << "+--------------------------+--------------------------+" << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Contract Number          | " << contractNumber << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Agent                    | " << agent.getName() << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Borrower                 | " << borrower->getName() << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Original Amount          | " << std::fixed << std::setprecision(2)
              << getDealOriginalAmount() << " " << currencyToString(currency) << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Signature Date           | " << signatureDate << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| End Date                 | " << endDate << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Status                   | " << statusToString(status) << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Remaining Amount         | " << std::fixed << std::setprecision(2)
              << getRemainingAmount() << " " << currencyToString(currency) << std::endl;
    std::cout << std::string(levelIndent, ' ') << "| Total Interest           | " << std::fixed << std::setprecision(2)
              << getTotalInterest() << " " << currencyToString(currency) << std::endl;
    std::cout << std::string(levelIndent, ' ') << "+--------------------------+--------------------------+" << std::endl;

    if (!pools.empty())
    {
        std::cout << "Pools involved:" << std::endl;
        for (const Pool &pool : pools)
        {
            std::cout << std::string(levelIndent + 2, ' ') << pool.getName() << std::endl;
        }
    }

    if (!facilities.empty())
    {
        std::cout << "Facilities involved:" << std::endl;

        for (int i = 0; i < facilities.size(); ++i)
        {
            std::cout << std::string(levelIndent + 2, ' ') << "\n+-------------------------- Facility " << i + 1 << " Summary --------------------------+\n";
            facilities[i].print(levelIndent + 2);
        }
    }
}

Facility &Deal::getCurrentFacility()
{
    if (facilities.empty())
    {
        std::cerr << "No facilities available." << std::endl;
        throw std::runtime_error("No facilities available");
    }
    if (status != Status::ACTIVE)
    {
        std::cerr << "Deal is not active." << std::endl;
        throw std::runtime_error("Deal is not active");
    }
    for (Facility &facility : facilities)
    {
        if (facility.getStatus() == Status::ACTIVE)
        {
            return facility;
        }
    }
    std::cerr << "No active facility found." << std::endl;
    throw std::runtime_error("No active facility found");
}

// Getters
const std::string Deal::getContractNumber() const
{
    return contractNumber;
}
const Agent &Deal::getAgent() const
{
    return agent;
}
const std::vector<Pool> &Deal::getPools() const
{
    return pools;
}
const Borrower *Deal::getBorrower() const
{
    return borrower;
}

Currency Deal::getCurrency() const
{
    return currency;
}
const std::string Deal::getSignatureDate() const
{
    return signatureDate;
}
const std::string Deal::getEndDate() const
{
    return endDate;
}
Status Deal::getStatus() const
{
    return status;
}
const std::vector<Facility> &Deal::getFacilities() const
{
    return facilities;
}

double Deal::getDealOriginalAmount() const
{
    double totalAmount = 0.0;
    for (const Facility &facility : facilities)
    {
        totalAmount += exchange(facility.getOriginalAmount(), facility.getCurrency(), currency);
    }
    return totalAmount;
}

double Deal::getRemainingAmount() const
{
    double totalRemaining = 0.0;
    for (const Facility &facility : facilities)
    {
        totalRemaining += exchange(facility.getRemainingAmount(), facility.getCurrency(), currency);
    }
    return totalRemaining;
}

int Deal::getNbRemainingFacilities() const
{
    int count = 0;
    for (const Facility &facility : facilities)
    {
        if (facility.getStatus() != Status::TERMINATED)
        {
            count++;
        }
    }
    return count;
}

double Deal::getTotalInterest() const
{
    double totalInterest = 0.0;
    for (const Facility &facility : facilities)
    {
        totalInterest += exchange(facility.calculateInterest(), facility.getCurrency(), currency);
    }
    return totalInterest;
}

void Deal::payParts(const std::string &date, double nbParts)
{
    if (!isValidDateFormat(date))
    {
        std::cerr << "Invalid date format. Expected YYYY-MM-DD." << std::endl;
        throw std::runtime_error("Invalid date format");
    }
    if (nbParts <= 0)
    {
        std::cerr << "Number of parts to pay must be greater than zero." << std::endl;
        throw std::runtime_error("Invalid number of parts");
    }
    if (getNbRemainingFacilities() == 0)
    {
        std::cerr << "No remaining facilities to pay parts." << std::endl;
        throw std::runtime_error("No remaining facilities");
    }

    if (status != Status::ACTIVE)
    {
        std::cerr << "Deal is not active. Cannot pay parts." << std::endl;
        throw std::runtime_error("Deal is not active");
    }
    Facility &currentFacility = getCurrentFacility();
    if (nbParts > currentFacility.getNbRemainingParts())
    {
        std::cerr << "Cannot pay more parts than remaining in the current facility." << std::endl;
        throw std::runtime_error("Not enough remaining parts");
    }
    if (dateStringToInt(date) < dateStringToInt(currentFacility.getStartDate()) ||
        dateStringToInt(date) > dateStringToInt(currentFacility.getEndDate()))
    {
        std::cerr << "Payment date must be within the facility's start and end dates." << std::endl;
        throw std::runtime_error("Invalid payment date");
    }
    if (currentFacility.getStatus() == Status::TERMINATED)
    {
        std::cerr << "Cannot pay parts for a terminated facility." << std::endl;
        throw std::runtime_error("Facility is terminated");
    }
    currentFacility.payParts(date, nbParts);

    if (getNbRemainingFacilities() == 0)
    {
        status = Status::TERMINATED;
        std::cout << "All facilities have been paid. Deal is now terminated." << std::endl;
    }
    else
    {
        facilities[facilities.size() - getNbRemainingFacilities()].setStatus(Status::ACTIVE);
    }
}

void Deal::setStatus(const Status &st)
{
    status = st;
}

void Deal::printPaidParts(int levelIndent) const
{
    for (const Facility &facility : facilities)
    {
        std::cout << std::string(levelIndent, ' ') << "Facility from "
                  << facility.getStartDate() << " to " << facility.getEndDate()
                  << " (Status: " << statusToString(facility.getStatus()) << ")" << std::endl;
        if (facility.getStatus() != Status::PENDING)
        {
            facility.printPaidParts(levelIndent + 2);
        }
    }
}