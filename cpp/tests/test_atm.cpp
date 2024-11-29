#include <iostream>
#include <cassert>
#include "../include/ATMController.h"

void test_insert_card() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);
    try {
        atm.insert_card(card);  // Should throw exception
        assert(false);
    } catch (const std::exception& e) {
        // Expected exception
    }
}

void test_eject_card() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);
    atm.eject_card();
    try {
        atm.enter_pin("1234");  // Should throw exception
        assert(false);
    } catch (const std::exception& e) {
        // Expected exception
    }
}

void test_enter_pin() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);
    atm.enter_pin("1234");
    atm.select_account();
    try {
        atm.eject_card();
        atm.insert_card(card);
        atm.enter_pin("0000");  // Invalid PIN
        assert(false);
    } catch (const std::exception& e) {
        // Expected exception
    }
}

void test_view_balance() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);
    atm.enter_pin("1234");
    atm.select_account();
    int balance = atm.view_balance();
    assert(balance == 100);
}

void test_deposit() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);
    atm.enter_pin("1234");
    atm.select_account();
    int new_balance = atm.deposit(50);
    assert(new_balance == 150);
    try {
        atm.deposit(-10);  // Negative amount
        assert(false);
    } catch (const std::exception& e) {
        // Expected exception
    }
}

void test_withdraw() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);
    ATMController atm(bank);
    Card card("12345");

    atm.insert_card(card);
    atm.enter_pin("1234");
    atm.select_account();
    int new_balance = atm.withdraw(30);
    assert(new_balance == 70);
    try {
        atm.withdraw(1000);  // Insufficient funds
        assert(false);
    } catch (const std::exception& e) {
        // Expected exception
    }
    try {
        atm.withdraw(-20);  // Negative amount
        assert(false);
    } catch (const std::exception& e) {
        // Expected exception
    }
}

void test_full_flow() {
    BankSystem bank;
    bank.add_account("12345", "1234", 100);
    ATMController atm(bank);
    Card card("12345");

    try {
        atm.view_balance();  // No card inserted
        assert(false);
    } catch (const std::exception& e) {
        // Expected exception
    }
    atm.insert_card(card);
    try {
        atm.view_balance();  // PIN not entered
        assert(false);
    } catch (const std::exception& e) {
        // Expected exception
    }
    atm.enter_pin("1234");
    atm.select_account();
    int balance = atm.view_balance();
    assert(balance == 100);
    atm.deposit(50);
    balance = atm.view_balance();
    assert(balance == 150);
    atm.withdraw(70);
    balance = atm.view_balance();
    assert(balance == 80);
    atm.eject_card();
    try {
        atm.view_balance();  // No card inserted
        assert(false);
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
