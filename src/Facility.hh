#pragma once

#include <string>
#include <vector>
#include "Status.hh"
#include "Currency.hh"

class Lender; // Forward declaration
class Part;   // Forward declaration

// A Facility represents a tranche of the overall deal, with its own schedule and lenders.
class Facility
{
private:
    std::string startDate;
    std::string endDate;
    double originalAmount;
    int nbParts;
    Currency currency;
    double interestRate; // e.g. 0.05 = 5 % per month

    std::vector<Lender *> lenders;
    std::vector<Part *> paidParts;
    Status status;

public:
    Facility(const std::string &s, const std::string &e,
             double amt, const Currency cur, double rate,
             int nbParts, const std::vector<Lender *> &l);

    double calculateInterest() const;
    double getRemainingAmount() const;
    int getNbRemainingParts() const;
    double getNominalAmountPart() const;

    void print(int levelIndent) const;

    // Getters
    const std::string getStartDate() const;
    const std::string getEndDate() const;
    double getOriginalAmount() const;
    const Currency getCurrency() const;
    double getInterestRate() const;
    const std::vector<Lender *> getLenders() const;
    const std::vector<Part *> getPaidParts() const;
    Status getStatus() const;
    int getNbParts() const;

    void payParts(const std::string &date, int nbParts);
    void setStatus(const Status &st);
    void printPaidParts(int levelIndent) const;
};
