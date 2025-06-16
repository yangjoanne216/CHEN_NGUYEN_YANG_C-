#include "utils.hh"

int roughMonthsBetween(string startDate, string endDate)
{
    // Assuming startDate and endDate are in the format "YYYY-MM-DD"
    int startYear = stoi(startDate.substr(0, 4));
    int startMonth = stoi(startDate.substr(5, 2));
    int endYear = stoi(endDate.substr(0, 4));
    int endMonth = stoi(endDate.substr(5, 2));

    // Calculate the difference in months
    return (endYear - startYear) * 12 + (endMonth - startMonth);
}

int dateStringToInt(const string &date)
{
    // Assuming date is in the format "YYYY-MM-DD"
    return stoi(date.substr(0, 4)) * 10000 + stoi(date.substr(5, 2)) * 100 + stoi(date.substr(8, 2));
}

bool isValidDateFormat(const std::string &date)
{
    // Checks for YYYY-MM-DD format
    static const std::regex pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    return std::regex_match(date, pattern);
}

double exchange(double amount, Currency from, Currency to)
{
    if (from == to)
    {
        return amount; // No conversion needed
    }
    auto it = exchangeRates.find({from, to});
    if (it != exchangeRates.end())
    {
        return amount * it->second; // Convert using the exchange rate
    }
    else
    {
        throw std::runtime_error("Exchange rate not defined for the given currencies.");
    }
}