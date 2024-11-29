#include <iostream>
#include <cassert>
#include "../include/ATMController.h"

// Test inserting a card and handling duplicate insertion
void test_insert_card() {
    std::cout << "[TEST] test_insert_card started." << std::endl;

    BankSystem bank;
    bank.add_account("4539578763621486", "1234", 100);  // 유효한 카드 번호로 계정 추가
    ATMController atm(bank);
    Card card("4539578763621486");  // 유효한 카드 번호

    atm.insert_card(card);  // 카드 삽입
    try {
        atm.insert_card(card);  // 중복 삽입 시도, 예외 발생 예상
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
    bank.add_account("4539578763621486", "1234", 100);  // 계정 추가
    ATMController atm(bank);
    Card card("4539578763621486");  // 유효한 카드 번호

    atm.insert_card(card);  // 카드 삽입
    atm.eject_card();       // 카드 배출
    try {
        atm.enter_pin("1234");  // 카드 배출 후 PIN 입력 시도, 예외 발생 예상
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
    bank.add_account("4539578763621486", "1234", 100);  // 계정 추가
    ATMController atm(bank);
    Card card("4539578763621486");  // 유효한 카드 번호

    atm.insert_card(card);       // 카드 삽입
    atm.enter_pin("1234");       // 올바른 PIN 입력
    atm.select_account();        // 계정 선택
    atm.eject_card();            // 카드 배출

    atm.insert_card(card);       // 카드 재삽입
    try {
        atm.enter_pin("0000");   // 잘못된 PIN 입력 시도, 예외 발생 예상
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
    bank.add_account("4539578763621486", "1234", 100);  // 초기 잔액 100으로 계정 추가
    ATMController atm(bank);
    Card card("4539578763621486");  // 유효한 카드 번호

    atm.insert_card(card);       // 카드 삽입
    atm.enter_pin("1234");       // PIN 입력
    atm.select_account();        // 계정 선택
    int balance = atm.view_balance();  // 잔액 조회
    assert(balance == 100 && "Balance should be 100.");

    std::cout << "[PASS] test_view_balance passed." << std::endl;
}

// Test depositing money into the account
void test_deposit() {
    std::cout << "[TEST] test_deposit started." << std::endl;

    BankSystem bank;
    bank.add_account("4539578763621486", "1234", 100);  // 초기 잔액 100으로 계정 추가
    ATMController atm(bank);
    Card card("4539578763621486");  // 유효한 카드 번호

    atm.insert_card(card);       // 카드 삽입
    atm.enter_pin("1234");       // PIN 입력
    atm.select_account();        // 계정 선택
    int new_balance = atm.deposit(50);  // 50 입금
    assert(new_balance == 150 && "New balance should be 150.");

    try {
        atm.deposit(-10);        // 음수 금액 입금 시도, 예외 발생 예상
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
    bank.add_account("4539578763621486", "1234", 100);  // 초기 잔액 100으로 계정 추가
    ATMController atm(bank);
    Card card("4539578763621486");  // 유효한 카드 번호

    atm.insert_card(card);        // 카드 삽입
    atm.enter_pin("1234");        // PIN 입력
    atm.select_account();         // 계정 선택
    int new_balance = atm.withdraw(30);  // 30 출금
    assert(new_balance == 70 && "New balance should be 70.");

    try {
        atm.withdraw(1000);       // 잔액 초과 출금 시도, 예외 발생 예상
        assert(false && "Overdrawing should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    try {
        atm.withdraw(-20);        // 음수 금액 출금 시도, 예외 발생 예상
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
    bank.add_account("4539578763621486", "1234", 100);  // 초기 잔액 100으로 계정 추가
    ATMController atm(bank);
    Card card("4539578763621486");  // 유효한 카드 번호

    try {
        atm.view_balance();       // 카드 미삽입 상태에서 잔액 조회 시도, 예외 발생 예상
        assert(false && "Viewing balance without a card should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    atm.insert_card(card);        // 카드 삽입

    try {
        atm.view_balance();       // PIN 미입력 상태에서 잔액 조회 시도, 예외 발생 예상
        assert(false && "Viewing balance without PIN should throw an exception.");
    } catch (const std::exception& e) {
        std::cout << "[INFO] Expected exception: " << e.what() << std::endl;
    }

    atm.enter_pin("1234");        // PIN 입력
    atm.select_account();         // 계정 선택
    int balance = atm.view_balance();
    assert(balance == 100 && "Balance should be 100.");

    atm.deposit(50);              // 50 입금
    balance = atm.view_balance();
    assert(balance == 150 && "Balance should be 150.");

    atm.withdraw(70);             // 70 출금
    balance = atm.view_balance();
    assert(balance == 80 && "Balance should be 80.");

    atm.eject_card();             // 카드 배출

    try {
        atm.view_balance();       // 카드 배출 후 잔액 조회 시도, 예외 발생 예상
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
