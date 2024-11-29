#include "ATMController.h"
#include <stdexcept>

// Constructor initializes the ATMController with a given bank system.
ATMController::ATMController(BankSystem& bank_system)
    : bank_system(bank_system), current_card(nullptr), current_account(nullptr), authenticated(false) {}

// Simulates inserting a card into the ATM.
void ATMController::insert_card(Card& card) {
    if (current_card != nullptr) {
        throw std::runtime_error("A card is already inserted.");
    }
    current_card = &card;
    authenticated = false;
    current_account = nullptr;
}

// Simulates ejecting the currently inserted card.
void ATMController::eject_card() {
    current_card = nullptr;
    authenticated = false;
    current_account = nullptr;
}

// Validates the PIN for the inserted card.
void ATMController::enter_pin(const std::string& pin) {
    if (current_card == nullptr) {
        throw std::runtime_error("No card inserted.");
    }
    if (bank_system.validate_pin(*current_card, pin)) {
        authenticated = true;
        current_account = &bank_system.get_account(*current_card);
    } else {
        throw std::invalid_argument("Invalid PIN.");
    }
}

// Selects the account associated with the current card after PIN validation.
void ATMController::select_account() {
    if (!authenticated) {
        throw std::runtime_error("PIN not validated.");
    }
    if (current_account == nullptr) {
        throw std::runtime_error("No account associated with this card.");
    }
}

// Displays the balance of the selected account.
int ATMController::view_balance() const {
    if (current_account == nullptr) {
        throw std::runtime_error("Account not selected.");
    }
    return current_account->get_balance();
}

// Deposits a specified amount into the selected account.
int ATMController::deposit(int amount) {
    if (current_account == nullptr) {
        throw std::runtime_error("Account not selected.");
    }
    return current_account->deposit(amount);
}

// Withdraws a specified amount from the selected account.
int ATMController::withdraw(int amount) {
    if (current_account == nullptr) {
        throw std::runtime_error("Account not selected.");
    }
    return current_account->withdraw(amount);
}
