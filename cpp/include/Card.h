#ifndef CARD_H
#define CARD_H

#include <string>

// The Card class represents a user's ATM card.
class Card {
private:
    std::string card_number; // Unique identifier for the card.

    // Validates the card number using the Luhn algorithm.
    bool is_valid_card_number(const std::string& card_number) const;

public:
    // Constructor that initializes the card with a given card number.
    // Throws an exception if the card number is invalid.
    explicit Card(const std::string& card_number);

    // Retrieves the card number.
    std::string get_card_number() const;

    // Retrieves the masked version of the card number (e.g., "****-****-****-1234").
    std::string get_masked_card_number() const;
};

#endif // CARD_H
