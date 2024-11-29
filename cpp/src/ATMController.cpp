#include "ATMController.h"
#include <stdexcept>

ATMController::ATMController(BankSystem& bank_system)
    : bank_system(bank_system), current_card(nullptr), current_account(nullptr), authenticated(false) {}

void ATMController::insert_card(Card& card) {
    if (current_card != nullptr) {
        throw std::runtime_error("A card is already inserted.");
    }
    current_card = &card;
    authenticated = false;
    current_account = nullptr;
}

void ATMController::eject_card() {
    current_card = nullptr;
    authenticated = false;
    current_account = nullptr;
}

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

void ATMController::select_account() {
    if (!authenticated) {
        throw std::runtime_error("PIN not validated.");
    }
    if (current_account == nullptr) {
        throw std::runtime_error("No account associated with this card.");
    }
}

int ATMController::view_balance() const {
    if (current_account == nullptr) {
        throw std::runtime_error("Account not selected.");
    }
    return current_account->get_balance();
}

int ATMController::deposit(int amount) {
    if (current_account == nullptr) {
        throw std::runtime_error("Account not selected.");
    }
    return current_account->deposit(amount);
}

int ATMController::withdraw(int amount) {
    if (current_account == nullptr) {
        throw std::runtime_error("Account not selected.");
    }
    return current_account->withdraw(amount);
}
