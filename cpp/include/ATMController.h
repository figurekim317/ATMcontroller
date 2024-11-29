#ifndef ATMCONTROLLER_H
#define ATMCONTROLLER_H

#include "BankSystem.h"
#include "Card.h"

// The ATMController class manages ATM operations and user interactions.
class ATMController {
private:
    BankSystem& bank_system;     // Reference to the bank system.
    Card* current_card;          // Pointer to the currently inserted card.
    Account* current_account;    // Pointer to the current account.
    bool authenticated;          // Authentication status.

public:
    // Constructor that initializes the ATMController with a given bank system.
    ATMController(BankSystem& bank_system);

    // Simulates inserting a card into the ATM.
    void insert_card(Card& card);

    // Simulates ejecting the currently inserted card.
    void eject_card();

    // Validates the PIN for the inserted card.
    void enter_pin(const std::string& pin);

    // Selects the account associated with the current card after PIN validation.
    void select_account();

    // Displays the balance of the selected account.
    int view_balance() const;

    // Deposits a specified amount into the selected account.
    int deposit(int amount);

    // Withdraws a specified amount from the selected account.
    int withdraw(int amount);
};

#endif // ATMCONTROLLER_H
