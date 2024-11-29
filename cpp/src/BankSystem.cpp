#include "BankSystem.h"
#include <stdexcept>

void BankSystem::add_account(const std::string& account_id, const std::string& pin, int initial_balance) {
    accounts.emplace(account_id, Account(account_id, initial_balance));
    pins[account_id] = pin;
}

bool BankSystem::validate_pin(const Card& card, const std::string& pin) const {
    auto it = pins.find(card.card_number);
    return it != pins.end() && it->second == pin;
}

Account& BankSystem::get_account(const Card& card) {
    auto it = accounts.find(card.card_number);
    if (it != accounts.end()) {
        return it->second;
    } else {
        throw std::invalid_argument("Account does not exist.");
    }
}
