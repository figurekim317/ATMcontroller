#include <iostream>
#include <cassert>
#include "../include/ATMController.h"

// Test inserting a card and handling duplicate insertion
void test_insert_card() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Add an account with initial balance
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);  // Insert the card
    try {
        atm.insert_card(card);  // Attempt to insert again, should throw exception
        assert(false);  // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }
}

// Test ejecting a card and ensuring operations fail after ejection
void test_eject_card() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Add an account
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);  // Insert the card
    atm.eject_card();       // Eject the card
    try {
        atm.enter_pin("1234");  // Should throw exception since card is ejected
        assert(false);          // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }
}

// Test entering PIN and handling incorrect PIN entries
void test_enter_pin() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Add an account
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);       // Insert the card
    atm.enter_pin("1234");       // Enter correct PIN
    atm.select_account();        // Select the account
    atm.eject_card();            // Eject the card

    atm.insert_card(card);       // Re-insert the card
    try {
        atm.enter_pin("0000");   // Enter incorrect PIN
        assert(false);           // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }
}

// Test viewing the account balance
void test_view_balance() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Add an account with balance 100
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);       // Insert the card
    atm.enter_pin("1234");       // Enter correct PIN
    atm.select_account();        // Select the account
    int balance = atm.view_balance();  // View balance
    assert(balance == 100);      // Check if balance is correct
}

// Test depositing money into the account
void test_deposit() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Initial balance is 100
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);       // Insert the card
    atm.enter_pin("1234");       // Enter correct PIN
    atm.select_account();        // Select the account
    int new_balance = atm.deposit(50);  // Deposit 50
    assert(new_balance == 150);  // New balance should be 150
    try {
        atm.deposit(-10);        // Attempt to deposit negative amount
        assert(false);           // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }
}

// Test withdrawing money from the account
void test_withdraw() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Initial balance is 100
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);        // Insert the card
    atm.enter_pin("1234");        // Enter correct PIN
    atm.select_account();         // Select the account
    int new_balance = atm.withdraw(30);  // Withdraw 30
    assert(new_balance == 70);    // New balance should be 70
    try {
        atm.withdraw(1000);       // Attempt to withdraw more than balance
        assert(false);            // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }
    try {
        atm.withdraw(-20);        // Attempt to withdraw negative amount
        assert(false);            // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }
}

// Test the full ATM operation flow
void test_full_flow() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Initial balance is 100
    ATMController atm(bank);
    Card card("12345");

    try {
        atm.view_balance();       // No card inserted, should throw exception
        assert(false);            // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }

    atm.insert_card(card);        // Insert the card

    try {
        atm.view_balance();       // PIN not entered, should throw exception
        assert(false);            // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }

    atm.enter_pin("1234");        // Enter correct PIN
    atm.select_account();         // Select the account
    int balance = atm.view_balance();
    assert(balance == 100);       // Balance should be 100

    atm.deposit(50);              // Deposit 50
    balance = atm.view_balance();
    assert(balance == 150);       // Balance should be 150

    atm.withdraw(70);             // Withdraw 70
    balance = atm.view_balance();
    assert(balance == 80);        // Balance should be 80

    atm.eject_card();             // Eject the card

    try {
        atm.view_balance();       // No card inserted, should throw exception
        assert(false);            // Should not reach here
    } catch (const std::exception& e) {
        // Expected exception
    }
}

int main() {
    test_insert_card();
    test_eject_card();
    test_enter_pin();
    test_view_balance();
    test_deposit();
    test_withdraw();
    test_full_flow();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
