#ifndef ATMCONTROLLER_H
#define ATMCONTROLLER_H

#include "BankSystem.h"
#include "Card.h"

class ATMController {
private:
    BankSystem& bank_system;
    Card* current_card;
    Account* current_account;
    bool authenticated;

public:
    ATMController(BankSystem& bank_system);

    void insert_card(Card& card);
    void eject_card();
    void enter_pin(const std::string& pin);
    void select_account();
    int view_balance() const;
    int deposit(int amount);
    int withdraw(int amount);
};

#endif // ATMCONTROLLER_H
