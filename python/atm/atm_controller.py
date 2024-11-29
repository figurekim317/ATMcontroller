from .bank_system import BankSystem
from .card import Card
from .account import Account


class ATMController:
    """
    Controller class that manages ATM operations and user interactions.

    Attributes:
        bank_system (BankSystem): The mock bank system for handling accounts.
        current_card (Card | None): The currently inserted card (if any).
        current_account (Account | None): The currently selected account (if any).
        authenticated (bool): Whether the user has been authenticated.
    """

    def __init__(self, bank_system: BankSystem):
        """
        Initializes the ATMController with a given bank system.

        Args:
            bank_system (BankSystem): The bank system to use for account management.
        """
        self.bank_system: BankSystem = bank_system
        self.current_card: Card | None = None
        self.current_account: Account | None = None
        self.authenticated: bool = False

    def insert_card(self, card: Card) -> None:
        """
        Simulates inserting a card into the ATM.

        Args:
            card (Card): The card to insert.

        Raises:
            ValueError: If a card is already inserted.
        """
        if self.current_card is not None:
            raise ValueError("A card is already inserted.")
        self.current_card = card
        self.authenticated = False
        self.current_account = None

    def eject_card(self) -> None:
        """
        Simulates ejecting the currently inserted card.
        """
        self.current_card = None
        self.authenticated = False
        self.current_account = None

    def enter_pin(self, pin: str) -> None:
        """
        Validates the PIN for the inserted card.

        Args:
            pin (str): The PIN entered by the user.

        Raises:
            ValueError: If no card is inserted or the PIN is invalid.
        """
        if not self.current_card:
            raise ValueError("No card inserted.")
        if self.bank_system.validate_pin(self.current_card, pin):
            self.authenticated = True
            self.current_account = self.bank_system.get_account(self.current_card)
        else:
            raise ValueError("Invalid PIN.")

    def select_account(self) -> Account:
        """
        Selects the account associated with the current card after PIN validation.

        Returns:
            Account: The selected account.

        Raises:
            ValueError: If PIN has not been validated or no account is associated with the card.
        """
        if not self.authenticated:
            raise ValueError("PIN not validated.")
        if not self.current_account:
            raise ValueError("No account associated with this card.")
        return self.current_account

    def view_balance(self) -> int:
        """
        Displays the balance of the selected account.

        Returns:
            int: The account balance.

        Raises:
            ValueError: If no account is selected.
        """
        if not self.current_account:
            raise ValueError("Account not selected.")
        return self.current_account.get_balance()

    def deposit(self, amount: int) -> int:
        """
        Deposits a specified amount into the selected account.

        Args:
            amount (int): The amount to deposit.

        Returns:
            int: Updated account balance.

        Raises:
            ValueError: If no account is selected or amount is invalid.
        """
        if not self.current_account:
            raise ValueError("Account not selected.")
        return self.current_account.deposit(amount)

    def withdraw(self, amount: int) -> int:
        """
        Withdraws a specified amount from the selected account.

        Args:
            amount (int): The amount to withdraw.

        Returns:
            int: Updated account balance.

        Raises:
            ValueError: If no account is selected or amount is invalid.
        """
        if not self.current_account:
            raise ValueError("Account not selected.")
        return self.current_account.withdraw(amount)
