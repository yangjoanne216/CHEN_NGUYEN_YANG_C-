#pragma once
#include <string>
#include <iomanip>
#include <regex>
#include <stdexcept>
#include <map>
#include <utility>
#include <iostream>
#include "Currency.hh"

using namespace std;

int roughMonthsBetween(string startDate, string endDate);
int dateStringToInt(const string &date);
bool isValidDateFormat(const std::string &date);
double exchange(double amount, Currency from, Currency to);