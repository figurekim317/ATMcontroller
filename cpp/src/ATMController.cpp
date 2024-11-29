#include "ATMController.h"
#include <stdexcept>
#include <iostream> // For optional logging

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

    // Optional logging
    std::cout << "[INFO] Card inserted: " << card.get_card_number() << std::endl;
}

// Simulates ejecting the currently inserted card.
void ATMController::eject_card() {
    if (current_card == nullptr) {
        throw std::runtime_error("No card to eject.");
    }

    // Optional logging
    std::cout << "[INFO] Card ejected: " << current_card->get_card_number() << std::endl;

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

        // Optional logging
        std::cout << "[INFO] PIN validated for card: " << current_card->get_card_number() << std::endl;
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

    // Optional logging
    std::cout << "[INFO] Account selected: " << current_account->get_account_id() << std::endl;
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
    int new_balance = current_account->deposit(amount);

    // Optional logging
    std::cout << "[INFO] Deposit made. Amount: " << amount << ", New Balance: " << new_balance << std::endl;

    return new_balance;
}

// Withdraws a specified amount from the selected account.
int ATMController::withdraw(int amount) {
    if (current_account == nullptr) {
        throw std::runtime_error("Account not selected.");
    }
    int new_balance = current_account->withdraw(amount);

    // Optional logging
    std::cout << "[INFO] Withdrawal made. Amount: " << amount << ", New Balance: " << new_balance << std::endl;

    return new_balance;
}
