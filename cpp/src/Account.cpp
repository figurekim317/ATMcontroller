#include "Account.h"
#include <stdexcept>

// Constructor initializes the account with an ID and initial balance.
Account::Account(const std::string& account_id, int balance)
    : account_id(account_id), balance(balance) {}

// Deposits a specified amount into the account.
// Returns the updated account balance.
int Account::deposit(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
    balance += amount;
    return balance;
}

// Withdraws a specified amount from the account.
// Returns the updated account balance.
int Account::withdraw(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Withdrawal amount must be positive.");
    }
    if (amount > balance) {
        throw std::invalid_argument("Insufficient balance.");
    }
    balance -= amount;
    return balance;
}

// Retrieves the current balance of the account.
int Account::get_balance() const {
    return balance;
}

// Retrieves the account ID.
std::string Account::get_account_id() const {
    return account_id;
}
