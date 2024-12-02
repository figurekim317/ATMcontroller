#include "Card.h"
#include <stdexcept>
#include <cctype>
#include <algorithm>

// Constructor that initializes the card with a given card number.
Card::Card(const std::string& card_number) {
    // Check if the card number is empty, not 16 characters, or contains non-digit characters
    if (card_number.empty() || card_number.length() != 16 || 
        !std::all_of(card_number.begin(), card_number.end(), ::isdigit)) {
        throw std::invalid_argument("Invalid card number: must be a 16-digit numeric string.");
    }

    // Set the card number if valid
    this->card_number = card_number;
}

// Validates the card number using the Luhn algorithm.
bool Card::is_valid_card_number(const std::string& card_number) const {
    int sum = 0;
    bool alternate = false;

    // Process digits from right to left
    for (auto it = card_number.rbegin(); it != card_number.rend(); ++it) {
        int digit = *it - '0';  // Convert char to int
        if (alternate) {
            digit *= 2;
            if (digit > 9) digit -= 9;
        }
        sum += digit;
        alternate = !alternate;
    }

    return (sum % 10 == 0);  // Valid if divisible by 10
}

// Retrieves the card number.
std::string Card::get_card_number() const {
    return card_number;
}

// Retrieves the masked version of the card number (e.g., "****-****-****-1234").
std::string Card::get_masked_card_number() const {
    return "****-****-****-" + card_number.substr(12, 4);
}

/*
&의 역할:
매개변수를 참조로 전달하여 복사 비용을 줄이고, 원본 데이터를 직접 참조합니다.
const를 사용하여 데이터를 수정하지 못하게 보호합니다.
Card 클래스가 사용 가능한 이유:
헤더 파일(Card.h)에 Card 클래스가 선언되어 있습니다.
이 헤더 파일을 #include로 포함했기 때문에 소스 파일에서 Card를 사용할 수 있습니다.
Card::Card의 의미:
Card 클래스의 생성자를 정의하며, 전역 함수와 구분하기 위해 클래스 이름을 명시합니다.
C++에서는 이러한 설계가 코드의 재사용성과 유지보수성을 높이는 데 중요한 역할을 합니다. */