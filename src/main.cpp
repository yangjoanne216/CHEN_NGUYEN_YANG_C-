#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <limits>
#include <fcntl.h>
#include <io.h>
#include "Borrower.hh"
#include "Lender.hh"
#include "Agent.hh"
#include "Pool.hh"
#include "Facility.hh"
#include "Deal.hh"
#include "Currency.hh"

using namespace std;

int main()
{
    std::vector<Borrower *> borrowers = {
        new Borrower("Air France"),
        new Borrower("Lufthansa"),
        new Borrower("British Airways")};
    std::vector<Lender *> lenders = {
        new Lender("BNP Paribas", Portfolio(Currency::EUR)),
        new Lender("Societe Generale", Portfolio(Currency::EUR)),
        new Lender("JPMorgan Chase", Portfolio(Currency::USD))};

    std::vector<Deal *> deals = {
        new Deal("D12345", Agent(lenders[0]), {Pool(lenders[1]), Pool(lenders[2])}, borrowers[0], Currency::EUR, "2023-01-01", "2025-01-01", {Facility("2023-01-01", "2024-01-01", 500000.0, Currency::EUR, 0.05, 10, {lenders[0], lenders[1]}), Facility("2024-06-01", "2025-06-01", 500000.0, Currency::USD, 0.04, 10, {lenders[2]})}),
        new Deal("D67890", Agent(lenders[1]), {Pool(lenders[0]), Pool(lenders[2])}, borrowers[1], Currency::USD, "2023-02-01", "2025-02-01", {Facility("2023-02-01", "2023-12-01", 300000.0, Currency::USD, 0.06, 10, {lenders[1], lenders[2]}), Facility("2024-01-01", "2024-12-01", 300000.0, Currency::EUR, 0.05, 10, {lenders[0]}), Facility("2025-01-01", "2025-02-01", 300000.0, Currency::JPY, 0.07, 10, {lenders[1], lenders[2], lenders[0]})}),
        new Deal("D11223", Agent(lenders[2]), {Pool(lenders[0]), Pool(lenders[1])}, borrowers[2], Currency::JPY, "2023-03-01", "2025-03-01", {Facility("2023-03-01", "2024-03-01", 700000.0, Currency::JPY, 0.07, 10, {lenders[2]}), Facility("2024-08-01", "2025-08-01", 700000.0, Currency::EUR, 0.05, 10, {lenders[0], lenders[1]})})};

    while (true)
    {
    finishMainMenu:
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Get Informations" << std::endl;
        std::cout << "2. Pay Debts" << std::endl;
        std::cout << "3. Create Deal (not implemented yet)" << std::endl;
        std::cout << "Choose an option: ";
        int choice;
        try
        {
            std::cin >> choice;
            if (std::cin.fail() || choice < 1 || choice > 3)
            {
                std::cin.clear();                                                   // Clear the error flag
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                throw std::invalid_argument("Invalid choice");
            }
        }
        catch (const std::exception &e)
        {
            std::cout << "Invalid input" << std::endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            while (true)
            {
            finishInfoChoice:
                std::cout << "Get Informations:" << std::endl;
                std::cout << "1. Borrowers" << std::endl;
                std::cout << "2. Lenders" << std::endl;
                std::cout << "3. Deals" << std::endl;
                std::cout << "0. Return" << std::endl;
                std::cout << "Choose an option: ";
                try
                {
                    std::cin >> choice;
                    if (std::cin.fail() || choice < 0 || choice > 3)
                    {
                        std::cin.clear();                                                   // Clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                        throw std::invalid_argument("Invalid choice");
                    }
                }
                catch (const std::exception &e)
                {
                    std::cout << "Invalid input" << std::endl;
                    continue;
                }

                switch (choice)
                {
                case 0:
                    goto finishMainMenu; // Return to the main menu
                case 1:
                    while (true)
                    {
                    selectBorrowerChoice:
                        std::cout << "Borrowers:" << std::endl;
                        for (int i = 0; i < borrowers.size(); ++i)
                        {
                            std::cout << (i + 1) << ". " << borrowers[i]->getName() << std::endl;
                        }
                        std::cout << "0. Return" << std::endl;
                        std::cout << "Choose an option: ";

                        try
                        {
                            std::cin >> choice;
                            if (std::cin.fail() || choice < 0 || choice > borrowers.size())
                            {
                                std::cin.clear();                                                   // Clear the error flag
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                                throw std::invalid_argument("Invalid choice");
                            }
                        }
                        catch (const std::exception &e)
                        {
                            std::cout << "Invalid input" << std::endl;
                            continue;
                        }
                        switch (choice)
                        {
                        case 0:
                            goto finishInfoChoice; // Return to the main menu
                        default:
                            vector<Deal *> borrowerDeals;
                            for (Deal *deal : deals)
                            {
                                if (deal->getBorrower() == borrowers[choice - 1])
                                {
                                    borrowerDeals.push_back(deal);
                                }
                            }
                            std::cout << "Deals of the borrower: " << std::endl;
                            for (int i = 0; i < borrowerDeals.size(); ++i)
                            {
                                std::cout << (i + 1) << ". " << borrowerDeals[i]->getContractNumber() << std::endl;
                            }
                            std::cout << "0. Return" << std::endl;
                            std::cout << "Choose an option: ";
                            try
                            {
                                std::cin >> choice;
                                if (std::cin.fail() || choice < 0 || choice > borrowerDeals.size())
                                {
                                    std::cin.clear();                                                   // Clear the error flag
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                                    throw std::invalid_argument("Invalid choice");
                                }
                            }
                            catch (const std::exception &e)
                            {
                                std::cout << "Invalid input" << std::endl;
                                continue;
                            }

                            if (choice == 0)
                            {
                                goto selectBorrowerChoice; // Return to the main menu
                            }
                            else
                            {
                                Deal *selectedDeal = borrowerDeals[choice - 1];
                                std::cout << "Selected Borrower: " << borrowers[choice - 1]->getName() << std::endl;
                                std::cout << "Selected Deal: " << selectedDeal->getContractNumber() << std::endl;
                                selectedDeal->print(0);
                            }
                        }
                    }
                case 2:
                    while (true)
                    {
                        std::cout << "Lenders:" << std::endl;
                        for (int i = 0; i < lenders.size(); ++i)
                        {
                            std::cout << (i + 1) << ". " << lenders[i]->getName() << std::endl;
                        }
                        std::cout << "0. Return" << std::endl;
                        std::cout << "Choose an option: ";

                        try
                        {
                            std::cin >> choice;
                            if (std::cin.fail() || choice < 0 || choice > lenders.size())
                            {
                                std::cin.clear();                                                   // Clear the error flag
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                                throw std::invalid_argument("Invalid choice");
                            }
                        }
                        catch (const std::exception &e)
                        {
                            std::cout << "Invalid input" << std::endl;
                            continue;
                        }
                        switch (choice)
                        {
                        case 0:
                            goto finishInfoChoice; // Return to the main menu
                        default:
                            lenders[choice - 1]->print();
                            lenders[choice - 1]->getPortfolio()->print(0);
                            break; // Print borrower information
                        }
                    }
                case 3:
                    while (true)
                    {
                        std::cout << "Deals:" << std::endl;
                        for (int i = 0; i < deals.size(); ++i)
                        {
                            std::cout << (i + 1) << ". " << deals[i]->getContractNumber() << std::endl;
                        }
                        std::cout << "0. Return" << std::endl;
                        std::cout << "Choose an option: ";

                        try
                        {
                            std::cin >> choice;
                            if (std::cin.fail() || choice < 0 || choice > deals.size())
                            {
                                std::cin.clear();                                                   // Clear the error flag
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                                throw std::invalid_argument("Invalid choice");
                            }
                        }
                        catch (const std::exception &e)
                        {
                            std::cout << "Invalid input" << std::endl;
                            continue;
                        }
                        switch (choice)
                        {
                        case 0:
                            goto finishInfoChoice; // Return to the main menu
                        default:
                            deals[choice - 1]->print(0);
                            break;
                        }
                    }
                }
            }
        case 2:
            while (true)
            {
            finishPayChoice:
                std::cout << "Choose borrower to pay debt:" << std::endl;
                for (int i = 0; i < borrowers.size(); ++i)
                {
                    std::cout << (i + 1) << ". " << borrowers[i]->getName() << std::endl;
                }
                std::cout << "0. Return" << std::endl;
                std::cout << "Choose an option: ";
                try
                {
                    std::cin >> choice;
                    if (std::cin.fail() || choice < 0 || choice > borrowers.size())
                    {
                        std::cin.clear();                                                   // Clear the error flag
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                        throw std::invalid_argument("Invalid choice");
                    }
                }
                catch (const std::exception &e)
                {
                    std::cout << "Invalid input" << std::endl;
                    continue;
                }

                if (choice == 0)
                {
                    goto finishMainMenu; // Return to the main menu
                }
                else
                {
                    Borrower *selectedBorrower = borrowers[choice - 1];
                    while (true)
                    {
                    finishSelectBorrowerChoice:
                        std::cout << "Selected Borrower: " << selectedBorrower->getName() << std::endl;
                        std::cout << "Current Deal(s) of the borrower:" << std::endl;

                        vector<Deal *> borrowerDeals;
                        for (Deal *deal : deals)
                        {
                            if (deal->getBorrower() == selectedBorrower && deal->getStatus() != Status::TERMINATED)
                            {
                                borrowerDeals.push_back(deal);
                            }
                        }

                        for (int i = 0; i < borrowerDeals.size(); ++i)
                        {
                            std::cout << (i + 1) << ". " << borrowerDeals[i]->getContractNumber() << std::endl;
                        }
                        std::cout << "0. Return" << std::endl;
                        std::cout << "Choose an option: ";
                        try
                        {
                            std::cin >> choice;
                            if (std::cin.fail() || choice < 0 || choice > borrowerDeals.size())
                            {
                                std::cin.clear();                                                   // Clear the error flag
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                                throw std::invalid_argument("Invalid choice");
                            }
                        }
                        catch (const std::exception &e)
                        {
                            std::cout << "Invalid input" << std::endl;
                            continue;
                        }

                        if (choice == 0)
                        {
                            goto finishSelectBorrowerChoice; // Return to the main menu
                        }
                        else
                        {
                            Deal *selectedDeal = borrowerDeals[choice - 1];
                            while (true)
                            {
                            finishPayPartsChoice:
                                std::cout << "Selected Deal: " << selectedDeal->getContractNumber() << std::endl;
                                selectedDeal->print(2);
                                std::cout << "Enter date (YYYY-MM-DD). Enter 0 to return: " << std::endl;
                                std::string date;
                                std::cin >> date;
                                if (date == "0")
                                {
                                    goto finishPayChoice;
                                }
                                if (!isValidDateFormat(date))
                                {
                                    std::cout << "Invalid date format. Please use YYYY-MM-DD." << std::endl;
                                    goto finishPayPartsChoice; // Skip to the next iteration
                                }
                                std::cout << "Enter number of parts to pay. Enter 0 to return: ";
                                std::cin >> choice;
                                if (choice == 0)
                                {
                                    goto finishPayChoice; // Skip to the next iteration
                                }
                                if (std::cin.fail() || choice <= 0)
                                {
                                    std::cin.clear();                                                   // Clear the error flag
                                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                                    std::cout << "Invalid number of parts. Please enter a positive integer." << std::endl;
                                    goto finishPayPartsChoice; // Skip to the next iteration
                                }

                                try
                                {
                                    selectedDeal->payParts(date, choice);
                                    std::cout << "Payment successful." << std::endl;
                                    selectedDeal->printPaidParts(2);
                                    goto finishPayChoice;
                                }
                                catch (const std::exception &e)
                                {
                                    std::cout << "Error: " << e.what() << std::endl;
                                    goto finishPayPartsChoice; // Skip to the next iteration
                                }
                            }
                        }
                    }
                }
                break;
            }
        case 3:
            std::cout << "Creating a new deal is not implemented yet." << std::endl;
            continue; // Skip to the next iteration
        default:
            std::cout << "Invalid choice. Please try again: ";
            continue; // Skip to the next iteration
        }
    }
}

// g++ Agent.cpp Borrower.cpp Lender.cpp Pool.cpp Facility.cpp main.cpp -o main