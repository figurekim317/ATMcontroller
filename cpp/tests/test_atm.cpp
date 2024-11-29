#include <iostream>
#include <cassert>
#include "../include/ATMController.h"

// Test inserting a card and handling duplicate insertion
void test_insert_card() {
    std::cout << "[TEST] test_insert_card started." << std::endl;

    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Add an account with initial balance
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);  // Insert the card
    try {
        atm.insert_card(card);  // Attempt to insert again, should throw exception
        assert(false && "Duplicate card insertion should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    std::cout << "[PASS] test_insert_card passed." << std::endl;
}

// Test ejecting a card and ensuring operations fail after ejection
void test_eject_card() {
    std::cout << "[TEST] test_eject_card started." << std::endl;

    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Add an account
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);  // Insert the card
    atm.eject_card();       // Eject the card
    try {
        atm.enter_pin("1234");  // Should throw exception since card is ejected
        assert(false && "Operations after card ejection should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    std::cout << "[PASS] test_eject_card passed." << std::endl;
}

// Test entering PIN and handling incorrect PIN entries
void test_enter_pin() {
    std::cout << "[TEST] test_enter_pin started." << std::endl;

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
        assert(false && "Entering incorrect PIN should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    std::cout << "[PASS] test_enter_pin passed." << std::endl;
}

// Test viewing the account balance
void test_view_balance() {
    std::cout << "[TEST] test_view_balance started." << std::endl;

    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Add an account with balance 100
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);       // Insert the card
    atm.enter_pin("1234");       // Enter correct PIN
    atm.select_account();        // Select the account
    int balance = atm.view_balance();  // View balance
    assert(balance == 100 && "Balance should be 100.");
    
    std::cout << "[PASS] test_view_balance passed." << std::endl;
}

// Test depositing money into the account
void test_deposit() {
    std::cout << "[TEST] test_deposit started." << std::endl;

    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Initial balance is 100
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);       // Insert the card
    atm.enter_pin("1234");       // Enter correct PIN
    atm.select_account();        // Select the account
    int new_balance = atm.deposit(50);  // Deposit 50
    assert(new_balance == 150 && "New balance should be 150.");

    try {
        atm.deposit(-10);        // Attempt to deposit negative amount
        assert(false && "Depositing negative amount should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    std::cout << "[PASS] test_deposit passed." << std::endl;
}

// Test withdrawing money from the account
void test_withdraw() {
    std::cout << "[TEST] test_withdraw started." << std::endl;

    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Initial balance is 100
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);        // Insert the card
    atm.enter_pin("1234");        // Enter correct PIN
    atm.select_account();         // Select the account
    int new_balance = atm.withdraw(30);  // Withdraw 30
    assert(new_balance == 70 && "New balance should be 70.");

    try {
        atm.withdraw(1000);       // Attempt to withdraw more than balance
        assert(false && "Overdrawing should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    try {
        atm.withdraw(-20);        // Attempt to withdraw negative amount
        assert(false && "Withdrawing negative amount should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    std::cout << "[PASS] test_withdraw passed." << std::endl;
}

// Test the full ATM operation flow
void test_full_flow() {
    std::cout << "[TEST] test_full_flow started." << std::endl;

    BankSystem bank;
    bank.add_account("12345", "1234", 100);  // Initial balance is 100
    ATMController atm(bank);
    Card card("12345");

    try {
        atm.view_balance();       // No card inserted, should throw exception
        assert(false && "Viewing balance without a card should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    atm.insert_card(card);        // Insert the card

    try {
        atm.view_balance();       // PIN not entered, should throw exception
        assert(false && "Viewing balance without PIN should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    atm.enter_pin("1234");        // Enter correct PIN
    atm.select_account();         // Select the account
    int balance = atm.view_balance();
    assert(balance == 100 && "Balance should be 100.");

    atm.deposit(50);              // Deposit 50
    balance = atm.view_balance();
    assert(balance == 150 && "Balance should be 150.");

    atm.withdraw(70);             // Withdraw 70
    balance = atm.view_balance();
    assert(balance == 80 && "Balance should be 80.");

    atm.eject_card();             // Eject the card

    try {
        atm.view_balance();       // No card inserted, should throw exception
        assert(false && "Viewing balance after card ejection should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    std::cout << "[PASS] test_full_flow passed." << std::endl;
}

int main() {
    try {
        test_insert_card();
        test_eject_card();
        test_enter_pin();
        test_view_balance();
        test_deposit();
        test_withdraw();
        test_full_flow();

        std::cout << "All tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "[FAILURE] A test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
