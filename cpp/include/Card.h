#ifndef CARD_H
#define CARD_H

#include <string>

class Card {
public:
    std::string card_number;

    Card(const std::string& card_number);
};

#endif // CARD_H
