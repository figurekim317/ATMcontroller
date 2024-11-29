// include/Account.h

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string account_id;
    int balance;

public:
    Account(const std::string& account_id, int balance = 0);

    int deposit(int amount);
    int withdraw(int amount);
    int get_balance() const;
    std::string get_account_id() const;
};

#endif // ACCOUNT_H
