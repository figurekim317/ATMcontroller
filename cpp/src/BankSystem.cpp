#include "BankSystem.h"
#include <stdexcept>
#include <iostream> // For logging

// Adds a new account to the bank system.
void BankSystem::add_account(const std::string& account_id, const std::string& pin, int initial_balance) {
    if (accounts.find(account_id) != accounts.end()) {
        throw std::invalid_argument("Account with this ID already exists: " + account_id);
    }

    accounts.emplace(account_id, Account(account_id, initial_balance));
    pins[account_id] = pin;

    // Optional logging
    std::cout << "[INFO] Account added. ID: " << account_id << ", Initial Balance: " << initial_balance << std::endl;
}

// Validates the PIN for a given card.
bool BankSystem::validate_pin(const Card& card, const std::string& pin) const {
    auto it = pins.find(card.get_card_number()); // Use getter for encapsulated access
    if (it != pins.end() && it->second == pin) {
        // Optional logging
        std::cout << "[INFO] PIN validation successful for card: " << card.get_card_number() << std::endl;
        return true;
    }

    // Optional logging
    std::cout << "[WARN] PIN validation failed for card: " << card.get_card_number() << std::endl;
    return false;
}

// Retrieves the Account object associated with a given card.
Account& BankSystem::get_account(const Card& card) {
    auto it = accounts.find(card.get_card_number()); // Use getter for encapsulated access
    if (it != accounts.end()) {
        // Optional logging
        std::cout << "[INFO] Account retrieved. ID: " << it->second.get_account_id() << std::endl;
        return it->second;
    } else {
        throw std::invalid_argument("Account does not exist for card: " + card.get_card_number());
    }
}

/*
1. 데이터를 직접 접근하지 않고 메서드(getter)를 통한 접근
auto it = pins.find(card.get_card_number()); // Use getter for encapsulated access
auto it = accounts.find(card.get_card_number()); // Use getter for encapsulated access
설명:
card.get_card_number()처럼 getter 메서드를 사용하여 데이터를 접근하고 있습니다.
API와 연동할 경우, 직접 데이터를 접근하지 않고, getter를 호출하여 필요한 데이터를 가져오는 방식은 네트워크 호출(API 요청)으로 대체하기 쉽습니다.
API와의 연계 가능성:
현재는 Card 객체에서 get_card_number()로 카드 번호를 가져오지만, 나중에 API 호출로 카드 번호를 검증하거나, 계좌 정보를 가져오는 로직으로 쉽게 변경할 수 있습니다.
예: API.get_account(card_number)로 호출 대체.

2. 계좌 및 PIN 데이터를 별도 맵핑 구조로 관리
std::unordered_map<std::string, Account> accounts;
std::unordered_map<std::string, std::string> pins;
설명:
계좌 정보와 PIN 정보를 각각 별도로 관리하고 있습니다.
API와 통합할 경우, 이러한 데이터를 실제 서버에서 가져오는 로직으로 쉽게 대체할 수 있습니다.
API와의 연계 가능성:
accounts는 GET /accounts/{account_id}와 같은 API로 계좌 정보를 가져오는 방식으로 전환 가능.
pins는 POST /validate-pin API를 통해 서버에서 PIN을 검증하도록 변경 가능.

3. 메서드로 캡슐화된 데이터 처리 로직
PIN 검증 로직

bool BankSystem::validate_pin(const Card& card, const std::string& pin) const {
    auto it = pins.find(card.get_card_number());
    if (it != pins.end() && it->second == pin) {
        // Optional logging
        std::cout << "[INFO] PIN validation successful for card: " << card.get_card_number() << std::endl;
        return true;
    }

    // Optional logging
    std::cout << "[WARN] PIN validation failed for card: " << card.get_card_number() << std::endl;
    return false;
}
설명:
PIN 검증 로직은 내부 pins 데이터 맵에서 PIN을 확인하는 방식으로 구현되어 있습니다.
이 로직은 서버에 요청을 보내 PIN 검증 API를 호출하는 방식으로 변경 가능.
API와의 연계 가능성:
현재 로직:
auto it = pins.find(card.get_card_number());
return it != pins.end() && it->second == pin;
API 연동 시:
return API.validate_pin(card.get_card_number(), pin);


결론
위 코드에서 향후 API 연동을 염두에 둔 설계는 다음 요소에서 나타납니다:

getter 메서드 사용:
데이터를 직접 접근하지 않고, getter를 사용하여 향후 API 호출로 대체 가능.
맵핑 구조 사용:
계좌 정보와 PIN 정보를 맵으로 관리, 이를 API 호출로 쉽게 대체 가능.
캡슐화된 데이터 처리:
PIN 검증과 계좌 조회를 메서드로 캡슐화하여, 내부 구현을 API 호출로 변경 가능.
로깅 설계:
현재는 콘솔 로깅이지만, API 호출로 로깅을 서버에 기록하도록 확장 가능.
이 설계는 로컬 데이터에서 API 기반으로 확장하기 쉬운 구조를 가지고 있습니다


*/