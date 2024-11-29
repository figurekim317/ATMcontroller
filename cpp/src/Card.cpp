#include "Card.h"
#include <stdexcept>
#include <cctype>

// Constructor that initializes the card with a given card number.
Card::Card(const std::string& card_number) {
    // Check if the card number is empty or contains non-digit characters
    if (card_number.empty() || card_number.length() != 16 || !std::all_of(card_number.begin(), card_number.end(), ::isdigit)) {
        throw std::invalid_argument("Invalid card number: must be a 16-digit numeric string.");
    }

    // Validate the card number using the Luhn algorithm
    if (!is_valid_card_number(card_number)) {
        throw std::invalid_argument("Invalid card number: failed Luhn algorithm check.");
    }

    this->card_number = card_number;
}

// Validates the card number using the Luhn algorithm.
bool Card::is_valid_card_number(const std::string& card_number) const {
    int sum = 0;
    bool alternate = false;
    for (int i = card_number.length() - 1; i >= 0; --i) {
        int digit = card_number[i] - '0';
        if (alternate) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        alternate = !alternate;
    }
    return (sum % 10 == 0);
}

// Retrieves the card number.
std::string Card::get_card_number() const {
    return card_number;
}

// Retrieves the masked version of the card number (e.g., "****-****-****-1234").
std::string Card::get_masked_card_number() const {
    return "****-****-****-" + card_number.substr(12, 4);
}
