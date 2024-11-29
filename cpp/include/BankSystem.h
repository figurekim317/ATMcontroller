#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <string>
#include <unordered_map>
#include "Account.h"
#include "Card.h"

// The BankSystem class simulates interaction with a bank's backend system.
class BankSystem {
private:
    std::unordered_map<std::string, Account> accounts; // Maps account IDs to Account objects.
    std::unordered_map<std::string, std::string> pins; // Maps account IDs to PIN codes.

public:
    // Adds a new account to the bank system.
    void add_account(const std::string& account_id, const std::string& pin, int initial_balance = 0);

    // Validates the PIN for a given card.
    bool validate_pin(const Card& card, const std::string& pin) const;

    // Retrieves the Account object associated with a given card.
    Account& get_account(const Card& card);
};

#endif // BANKSYSTEM_H
