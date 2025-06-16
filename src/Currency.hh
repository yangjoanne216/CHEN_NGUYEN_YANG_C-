#pragma once
#include <string>
#include <stdexcept>
using namespace std;

enum Currency
{
    EUR, // Euro
    USD, // US Dollar
    JPY, // Japanese Yen
};

#include <map>
#include <utility>

inline const std::map<std::pair<Currency, Currency>, double> exchangeRates = {
    {{EUR, USD}, 1.08},
    {{USD, EUR}, 0.925},
    {{EUR, JPY}, 165.0},
    {{JPY, EUR}, 0.0061},
    {{USD, JPY}, 152.0},
    {{JPY, USD}, 0.0066}};

inline string currencyToString(Currency cur)
{
    switch (cur)
    {
    case EUR:
        return "EUR";
    case USD:
        return "USD";
    case JPY:
        return "JPY";
    default:
        return "Unknown Currency";
    }
}
