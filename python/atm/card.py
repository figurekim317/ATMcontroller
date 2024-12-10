class Card:
    """
    Represents a user's ATM card.

    Attributes:
        card_number (str): Unique identifier for the card (e.g., account number).
    """

    def __init__(self, card_number: str):
        """
        Initializes the card with a given card number.

        Args:
            card_number (str): The unique card number.

        Raises:
            ValueError: If the card number is invalid.
        """
        if not card_number or not card_number.isdigit() or len(card_number) != 16:
            raise ValueError("Invalid card number: must be a 16-digit numeric string.")
        
        if not self.is_valid_card_number(card_number):
            raise ValueError("Invalid card number: failed Luhn algorithm check.")

        self.card_number: str = card_number

    @staticmethod # 이 함수는 클래스의 인스턴스 없이 호출 가능한 메서드, 클래스 속성이나 인스턴스 속성을 사용하지 않고 card_number로만 동작
    def is_valid_card_number(card_number: str) -> bool:
        """
        Validates the card number using the Luhn algorithm.

        Args:
            card_number (str): The card number to validate.

        Returns:
            bool: True if the card number is valid, False otherwise.
        """
        sum_digits = 0
        alternate = False

        # Process digits from right to left
        # Luhn 알고리즘
        '''
        Luhn 알고리즘 요약
        카드 번호의 오른쪽에서 왼쪽으로 숫자를 순회하며, 교대로 두 배 처리.
        두 배 처리 후 결과가 9보다 크면 자리합을 계산.
        최종 합계를 10으로 나눈 나머지가 0이면 유효한 카드 번호.
        '''
        for digit in reversed(card_number):
            num = int(digit)
            if alternate:
                num *= 2
                if num > 9:
                    num -= 9
            sum_digits += num
            alternate = not alternate

        return sum_digits % 10 == 0

    def get_card_number(self) -> str:
        """
        Retrieves the full card number.

        Returns:
            str: The full card number.
        """
        return self.card_number

    def get_masked_card_number(self) -> str:
        """
        Retrieves the masked version of the card number.
        보안성 유지를 위해. 결제 화면에 카드 표시를 할 때, 은행 앱에서 거래 내역을 확인, 개발자가 카드 관련 기능을 디버깅하거나 문제를 추적할 때

        Returns:
            str: The masked card number (e.g., "****-****-****-1234").
        """
        return "****-****-****-" + self.card_number[-4:]


