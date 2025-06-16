#include "Facility.hh"
#include <iostream>
#include <iomanip>
#include "Lender.hh"
#include "Part.hh"
#include "utils.hh"
#include "Currency.hh"
#include <sstream>
Facility::Facility(const std::string &s, const std::string &e,
                   double amt, const Currency cur, double rate,
                   int nbParts_, const std::vector<Lender *> &l)
    : startDate(s), endDate(e), originalAmount(amt), nbParts(nbParts_),
      currency(cur), interestRate(rate), lenders(l), status(Status::PENDING)
{
    // todo
}

// Utility function for string conversion with precision
std::string to_string_with_precision(double value, int n = 2)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(n) << value;
    return out.str();
}

double Facility::calculateInterest() const
{
    return originalAmount * interestRate * roughMonthsBetween(startDate, endDate);
}

int Facility::getNbRemainingParts() const
{
    return nbParts - static_cast<int>(paidParts.size());
}

double Facility::getNominalAmountPart() const
{
    return originalAmount / nbParts;
}

double Facility::getRemainingAmount() const
{
    return getNbRemainingParts() * getNominalAmountPart();
}

void Facility::print(int levelIndent) const
{
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::left << std::setw(20) << "Field"
              << "| " << std::left << std::setw(30) << "Value"
              << "|\n";
    std::cout << std::string(levelIndent, ' ') << "+----------------------+--------------------------------+\n";

    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Start Date"
              << "| " << std::setw(30) << startDate << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "End Date"
              << "| " << std::setw(30) << endDate << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Original Amount"
              << "| " << std::setw(27) << (std::to_string(originalAmount) + " " + currencyToString(currency)) << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Interest Rate"
              << "| " << std::setw(27) << (std::to_string(interestRate * 100) + "%") << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Nb Parts"
              << "| " << std::setw(30) << nbParts << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Remaining Parts"
              << "| " << std::setw(30) << getNbRemainingParts() << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Nominal/Part"
              << "| " << std::setw(27) << (to_string_with_precision(getNominalAmountPart(), 2) + " " + currencyToString(currency)) << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Remaining Amount"
              << "| " << std::setw(27) << (to_string_with_precision(getRemainingAmount(), 2) + " " + currencyToString(currency)) << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Status"
              << "| " << std::setw(30) << statusToString(status) << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Nb Periods"
              << "| " << std::setw(30) << roughMonthsBetween(startDate, endDate) << "|\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::setw(20) << "Interest"
              << "| " << std::setw(27) << (to_string_with_precision(calculateInterest(), 2) + " " + currencyToString(currency)) << "|\n";
    std::cout << std::string(levelIndent, ' ') << "+----------------------+--------------------------------+\n";

    // Print lenders in table
    std::cout << std::string(levelIndent, ' ') << "\n+-------------------------- Lenders --------------------------+\n";
    std::cout << std::string(levelIndent, ' ')
              << "| " << std::left << std::setw(3) << "#"
              << "| " << std::left << std::setw(30) << "Lender Name"
              << "|\n";
    std::cout << std::string(levelIndent, ' ') << "+---+------------------------------+\n";
    int idx = 1;
    for (const Lender *lender : lenders)
    {
        std::cout << std::string(levelIndent, ' ')
                  << "| " << std::setw(3) << idx++
                  << "| " << std::setw(30) << lender->getName()
                  << "|\n";
    }
    std::cout << std::string(levelIndent, ' ') << "+---+------------------------------+\n";

    // Print paid parts summary table
    if (!paidParts.empty())
    {
        std::cout << std::string(levelIndent, ' ') << "\n+-------------------------- Paid Parts --------------------------+\n";
        std::cout << std::string(levelIndent, ' ')
                  << "| " << std::left << std::setw(12) << "Pay Date"
                  << "| " << std::left << std::setw(10) << "Nb Parts"
                  << "| " << std::left << std::setw(15) << "Nominal/Part"
                  << "|\n";
        std::cout << std::string(levelIndent, ' ') << "+------------+----------+---------------+\n";
        std::map<std::string, int> partsByDate;
        for (const Part *part : paidParts)
        {
            partsByDate[part->getPayDate()]++;
        }
        for (const auto &entry : partsByDate)
        {
            std::cout << std::string(levelIndent, ' ')
                      << "| " << std::setw(12) << entry.first
                      << "| " << std::setw(10) << entry.second
                      << "| " << std::setw(15) << (to_string_with_precision(getNominalAmountPart(), 2) + " " + currencyToString(currency))
                      << "|\n";
        }
        std::cout << std::string(levelIndent, ' ') << "+------------+----------+---------------+\n";
    }
}

const std::string Facility::getStartDate() const
{
    return startDate;
}
const std::string Facility::getEndDate() const
{
    return endDate;
}
double Facility::getOriginalAmount() const
{
    return originalAmount;
}
const Currency Facility::getCurrency() const
{
    return currency;
}
double Facility::getInterestRate() const
{
    return interestRate;
}
const std::vector<Lender *> Facility::getLenders() const
{
    return lenders;
}
const std::vector<Part *> Facility::getPaidParts() const
{
    return paidParts;
}

Status Facility::getStatus() const
{
    return status;
}

int Facility::getNbParts() const
{
    return nbParts;
}

void Facility::payParts(const std::string &date, int nbPartsToPay)
{
    if (nbPartsToPay <= 0)
    {
        std::cerr << "Error: Number of parts to pay must be greater than zero." << std::endl;
        return;
    }
    if (!isValidDateFormat(date))
    {
        std::cerr << "Error: Invalid date format. Expected YYYY-MM-DD." << std::endl;
        return;
    }
    if (nbPartsToPay > getNbRemainingParts())
    {
        std::cerr << "Error: Cannot pay more parts than remaining." << std::endl;
        return;
    }
    if (status != Status::ACTIVE)
    {
        std::cerr << "Error: Facility is not active. Cannot pay parts." << std::endl;
        return;
    }
    double amountPaid = nbPartsToPay * getNominalAmountPart();
    for (int i = 0; i < nbPartsToPay; ++i)
    {
        paidParts.push_back(new Part(date, getNominalAmountPart(), currency));
    }

    if (getNbRemainingParts() == 0)
    {
        status = Status::TERMINATED;
        std::cout << "Facility " << getStartDate() << " to " << getEndDate()
                  << " has been fully paid and is now terminated." << std::endl;
    }
}
void Facility::printPaidParts(int levelIndent) const
{
    if (paidParts.empty())
    {
        std::cout << std::string(levelIndent, ' ') << "No paid parts." << std::endl;
        return;
    }
    std::cout << std::string(levelIndent, ' ') << "Paid Parts:" << std::endl;

    std::map<std::string, std::vector<const Part *>> partsByDate;
    for (const Part *part : paidParts)
    {
        partsByDate[part->getPayDate()].push_back(part);
    }
    for (const auto &entry : partsByDate)
    {
        std::cout << std::string(levelIndent + 2, ' ') << "Date: " << entry.first << std::endl;
        int nbPartsOnDate = entry.second.size();
        std::cout << std::string(levelIndent + 4, ' ') << "Number of Parts: " << nbPartsOnDate << std::endl;
        std::cout << std::string(levelIndent + 4, ' ') << "Nominal Amount: "
                  << std::fixed << std::setprecision(2) << entry.second[0]->getAmount()
                  << " " << currencyToString(entry.second[0]->getCurrency()) << std::endl;
    }
}

void Facility::setStatus(const Status &st)
{
    status = st;
}