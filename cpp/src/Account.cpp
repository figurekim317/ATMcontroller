#include "Account.h"
#include <stdexcept>

Account::Account(const std::string& account_id, int balance)
    : account_id(account_id), balance(balance) {}

int Account::deposit(int amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Deposit amount must be positive.");
    }
    balance += amount;
    return balance;
}

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

int Account::get_balance() const {
    return balance;
}

std::string Account::get_account_id() const {
    return account_id;
}
