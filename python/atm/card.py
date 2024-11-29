class Card:
    """
    Class representing a user's ATM card.
    Attributes:
        card_number (str): Unique identifier for the card (e.g., account number).
    """

    def __init__(self, card_number):
        """
        Initializes the card with a given card number.
        Args:
            card_number (str): The unique card number.
        """
        self.card_number = card_number
