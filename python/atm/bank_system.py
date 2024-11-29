from .account import Account
from .card import Card


class BankSystem:
    """
    Mock class simulating interaction with a bank's backend system.

    Attributes:
        accounts (dict[str, Account]): Dictionary mapping account IDs to Account objects.
        pins (dict[str, str]): Dictionary mapping account IDs to PIN codes.
    """

    def __init__(self) -> None:
        """
        Initializes the BankSystem with empty accounts and PIN storage.
        """
        self.accounts: dict[str, Account] = {}
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
        """
        account_id = card.card_number
        if account_id not in self.accounts:
            raise ValueError(f"Account with ID {account_id} does not exist.")
        return self.accounts[account_id]
