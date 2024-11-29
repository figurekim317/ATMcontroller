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

    @staticmethod
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

        Returns:
            str: The masked card number (e.g., "****-****-****-1234").
        """
        return "****-****-****-" + self.card_number[-4:]
