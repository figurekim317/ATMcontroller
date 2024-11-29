#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

// The Account class represents a bank account with basic operations.
class Account {
private:
    std::string account_id; // Unique identifier for the account.
    int balance;            // Current balance of the account.

public:
    // Constructor to initialize an account with an ID and optional initial balance.
    Account(const std::string& account_id, int balance = 0);

    // Deposits a specified amount into the account.
    // Returns the updated account balance.
    int deposit(int amount);

    // Withdraws a specified amount from the account.
    // Returns the updated account balance.
    int withdraw(int amount);

    // Retrieves the current balance of the account.
    int get_balance() const;

    // Retrieves the account ID.
    std::string get_account_id() const;
};

#endif // ACCOUNT_H
