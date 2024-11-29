#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <string>
#include <unordered_map>
#include "Account.h"
#include "Card.h"

class BankSystem {
private:
    std::unordered_map<std::string, Account> accounts;
    std::unordered_map<std::string, std::string> pins;

public:
    void add_account(const std::string& account_id, const std::string& pin, int initial_balance = 0);
    bool validate_pin(const Card& card, const std::string& pin) const;
    Account& get_account(const Card& card);
};

#endif // BANKSYSTEM_H
