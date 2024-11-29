#ifndef CARD_H
#define CARD_H

#include <string>

// The Card class represents a user's ATM card.
class Card {
public:
    std::string card_number; // Unique identifier for the card.

    // Constructor that initializes the card with a given card number.
    Card(const std::string& card_number);
};

#endif // CARD_H
