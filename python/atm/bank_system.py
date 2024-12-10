from .account import Account
from .card import Card


class BankSystem:
    """
    Mock class simulating interaction with a bank's backend system.

    Attributes:
        accounts (dict[str, Account]): Dictionary mapping account IDs to Account objects.
        pins (dict[str, str]): Dictionary mapping account IDs to PIN codes.

    은행 api를 향후 합칠 예상을 하고 진행을 했다는 사실
    self.account: dict[str, Account] = {}
    계좌 ID를 키로, Account 객체를 값으로 저장
    실제 은행의 DB에서 저장된 계좌정보와 PIN코드를 API 호출을 통해 조회해야 함
    현재는 메모리 내 딕셔너리를 사용해 데이터베이스와 유사한 구조를 모방하고 있음
    향후 이 dictionary대신 은행 API 호출로 데이터를 가져오는 방식으로 변경이 가능
    """

    def __init__(self) -> None:
        """
        Initializes the BankSystem with empty accounts and PIN storage.
        """
        self.accounts: dict[str, Account] = {} # 변수명: 데이터_타입 = 초기값
        self.pins: dict[str, str] = {}

    def add_account(self, account_id: str, pin: str, initial_balance: int = 0) -> None:
        """
        Adds a new account to the bank system.

        Args:
            account_id (str): The unique ID for the account.
            pin (str): The PIN code for the account.
            initial_balance (int, optional): Initial balance. Defaults to 0.

        Raises:
            ValueError: If the account ID already exists.
            ValueError: If the initial balance is negative.
        """
        if account_id in self.accounts:
            raise ValueError(f"Account with ID {account_id} already exists.")
        if initial_balance < 0:
            raise ValueError("Initial balance cannot be negative.")
        self.accounts[account_id] = Account(account_id, initial_balance)
        self.pins[account_id] = pin

    def validate_pin(self, card: Card, pin: str) -> bool:
        """
        Validates the PIN for a given card.
        주어진 카드 번호와 입력된 PIN을 검증합니다.
        현재는 self.pins 딕셔너리에서 PIN을 조회하여 확인하지만, 실제 은행 API에서는 PIN 검증 요청을 서버로 보냅니다.
        Args:
            card (Card): The user's ATM card.
            pin (str): The entered PIN.

        Returns:
            bool: True if the PIN is correct, False otherwise.
        """
        account_id = card.card_number
        return self.pins.get(account_id) == pin

    def get_account(self, card: Card) -> Account:
        """
        Retrieves the Account object associated with a given card.

        Args:
            card (Card): The user's ATM card.

        Returns:
            Account: The associated Account object.

        Raises:
            ValueError: If the account does not exist.

        카드 번호를 기반으로 해당 계좌 객체를 반환합니다.
        현재는 self.accounts 딕셔너리에서 데이터를 가져오지만, 
        실제 은행 시스템에서는 계좌 조회 요청을 통해 서버에서 데이터를 가져옵니다.
        API를 통해 계좌 잔액, 거래 내역 등의 정보를 실시간으로 조회할 수 있습니다.
        예: GET /accounts/{account_id} 엔드포인트 호출.

        """
        account_id = card.card_number
        if account_id not in self.accounts:
            raise ValueError(f"Account with ID {account_id} does not exist.")
        return self.accounts[account_id]


'''
Card 클래스의 활용
Card 객체를 사용하는 방식

account_id = card.card_number
설명:
카드 번호(card.card_number)를 기반으로 계좌 정보를 조회하거나 PIN을 확인합니다.
카드 번호는 은행 시스템에서 계좌를 식별하는 고유 키로 사용됩니다.
은행 API와의 연계 가능성:
카드 번호를 API 호출의 입력값으로 전달하여 계좌와 관련된 정보를 가져올 수 있습니다.
예: GET /accounts?card_number=1234567890123456처럼 카드 번호를 쿼리 매개변수로 전달.


클래스 구조 자체가 API 통합을 염두에 둔 설계
Mock 구현:
현재는 메모리 내 딕셔너리와 간단한 메서드를 사용하여 은행 API를 모방했습니다.
이는 실제 API가 추가되었을 때 코드 수정 없이 API 호출 로직만 추가하면 되도록 설계되었습니다.
유연한 확장 가능성:
현재의 BankSystem 클래스는 은행 API 호출 로직으로 쉽게 대체 가능합니다.
예: self.accounts 딕셔너리를 없애고, API 호출로 계좌 데이터를 가져오도록 수정.

현재 Mock 데이터를 API로 교체:
self.accounts와 self.pins를 은행 API 호출로 대체.
예: self.accounts = API.get_all_accounts().
메서드 구현 변경:
add_account → API를 호출하여 계좌 생성.
validate_pin → API 호출로 PIN 검증.
get_account → API 호출로 계좌 데이터 가져오기.


API(Application Programming Interface)는 응용 프로그램 간의 상호작용을 가능하게 하는 인터페이스입니다.
특히, 웹 API는 클라이언트(요청을 보내는 쪽)와 서버(요청을 처리하는 쪽)가 HTTP 프로토콜을 통해 통신하는 방식입니다.

API의 동작 원리
API 방식에서는 클라이언트가 요청(request)을 보내고, 서버가 응답(response)을 반환합니다.

기본 흐름:

클라이언트:
클라이언트는 HTTP 요청(예: GET, POST 등)을 API 서버로 보냅니다.
요청에는 엔드포인트(endpoint), HTTP 메서드, 그리고 **필요한 데이터(요청 본문, 헤더)**가 포함됩니다.
서버:
서버는 요청을 처리하고, 요청 결과를 클라이언트에게 반환합니다.
반환값은 주로 JSON 형식의 데이터입니다.

API 요청 방식
1. HTTP 메서드

API 요청은 주로 다음과 같은 HTTP 메서드를 사용합니다:

GET: 데이터를 가져오는 요청.
예: 계좌 잔액 확인.
POST: 데이터를 생성하는 요청.
예: 새로운 계좌 생성.
PUT: 데이터를 수정하는 요청.
예: 계좌 정보를 업데이트.
DELETE: 데이터를 삭제하는 요청.
예: 계좌 삭제.
2. 엔드포인트(Endpoint)

API 서버는 고유한 URL 경로를 통해 특정 작업을 처리합니다.

예:
GET /accounts → 모든 계좌 조회.
GET /accounts/{account_id} → 특정 계좌 조회.
POST /accounts → 새 계좌 생성.

Mock 데이터란?
**Mock 데이터(Mock Data)**는 실제 데이터베이스나 시스템과 통합하지 않은 상태에서, 테스트나 개발 과정에서 사용하기 위해 임시로 만든 가짜 데이터를 말합니다.
Mock 데이터는 주로 테스트 환경에서 동작을 검증하거나 기능 개발을 빠르게 진행하기 위해 사용됩니다.

Mock 데이터의 특징
가짜 데이터:
실제 데이터처럼 동작하지만, 실제 시스템이나 데이터베이스와는 연결되지 않은 가상 데이터입니다.
예를 들어, 실제 사용자 정보 대신 {"id": 1, "name": "John Doe", "email": "john@example.com"} 같은 데이터를 사용합니다.
독립성:
Mock 데이터를 사용하면 데이터베이스나 외부 시스템에 의존하지 않고도 테스트나 개발이 가능합니다.
안전성:
실제 데이터를 사용하지 않기 때문에 민감한 정보(예: 사용자 비밀번호, 금융 정보 등)가 유출될 위험이 없습니다.

'''