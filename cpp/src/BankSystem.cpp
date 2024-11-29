#include "BankSystem.h"
#include <stdexcept>
#include <iostream> // For logging

// Adds a new account to the bank system.
void BankSystem::add_account(const std::string& account_id, const std::string& pin, int initial_balance) {
    if (accounts.find(account_id) != accounts.end()) {
        throw std::invalid_argument("Account with this ID already exists: " + account_id);
    }

    accounts.emplace(account_id, Account(account_id, initial_balance));
    pins[account_id] = pin;

    // Optional logging
    std::cout << "[INFO] Account added. ID: " << account_id << ", Initial Balance: " << initial_balance << std::endl;
}

// Validates the PIN for a given card.
bool BankSystem::validate_pin(const Card& card, const std::string& pin) const {
    auto it = pins.find(card.get_card_number()); // Use getter for encapsulated access
    if (it != pins.end() && it->second == pin) {
        // Optional logging
        std::cout << "[INFO] PIN validation successful for card: " << card.get_card_number() << std::endl;
        return true;
    }

    // Optional logging
    std::cout << "[WARN] PIN validation failed for card: " << card.get_card_number() << std::endl;
    return false;
}

// Retrieves the Account object associated with a given card.
Account& BankSystem::get_account(const Card& card) {
    auto it = accounts.find(card.get_card_number()); // Use getter for encapsulated access
    if (it != accounts.end()) {
        // Optional logging
        std::cout << "[INFO] Account retrieved. ID: " << it->second.get_account_id() << std::endl;
        return it->second;
    } else {
        throw std::invalid_argument("Account does not exist for card: " + card.get_card_number());
    }
}
