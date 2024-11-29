#include <iostream>
#include <string>
#include <unordered_map>

// Class representing a card with a unique card number
class Card {
public:
    std::string card_number;

    // Constructor to initialize a card with a given card number
    Card(const std::string& card_number);
};

// Class representing a bank account
class Account {
public:
    std::string account_id; // Unique ID for the account
    int balance;            // Current balance of the account

    // Constructor to initialize account ID and optional balance
    Account(const std::string& account_id, int balance = 0);

    // Method to deposit a specific amount into the account
    int deposit(int amount);

    // Method to withdraw a specific amount from the account
    int withdraw(int amount);

    // Method to get the current balance of the account
    int get_balance() const;
};

// Class representing the banking system managing accounts and PINs
class BankSystem {
private:
    std::unordered_map<std::string, Account> accounts; // Map of accounts by ID
    std::unordered_map<std::string, std::string> pins; // Map of card numbers to PINs

public:
    // Method to add a new account to the banking system
    void add_account(const Account& account, const std::string& pin);

    // Method to validate the PIN for a given card
    bool validate_pin(const Card& card, const std::string& pin);

    // Method to retrieve an account associated with a given card
    Account& get_account(const Card& card);
};

// Class managing ATM operations and user interaction
class ATMController {
private:
    BankSystem& bank_system;   // Reference to the bank system
    Card* current_card;        // Currently inserted card
    Account* current_account;  // Currently selected account
    bool authenticated;        // Flag to indicate if the user is authenticated

public:
    // Constructor to initialize the ATM controller with a bank system
    ATMController(BankSystem& bank_system);

    // Method to insert a card into the ATM
    void insert_card(Card& card);

    // Method to eject the currently inserted card
    void eject_card();

    // Method to enter a PIN and validate it against the card
    void enter_pin(const std::string& pin);

    // Method to select an account associated with the authenticated card
    void select_account();

    // Method to view the balance of the selected account
    int view_balance() const;

    // Method to deposit an amount into the selected account
    int deposit(int amount);

    // Method to withdraw an amount from the selected account
    int withdraw(int amount);
};

int main() {
    // Placeholder for testing the ATM system
    std::cout << "ATM System Prototype" << std::endl;
    return 0;
}
