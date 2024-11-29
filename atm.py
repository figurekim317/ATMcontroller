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

class Account:
    """
    Class representing a bank account.
    Attributes:
        account_id (str): Unique identifier for the account.
        balance (int): Current balance in the account.
    """
    def __init__(self, account_id, balance=0):
        """
        Initializes an account with an ID and an optional initial balance.
        Args:
            account_id (str): The unique ID for the account.
            balance (int, optional): Initial balance. Defaults to 0.
        """
        self.account_id = account_id
        self.balance = balance

    def deposit(self, amount):
        pass

    def withdraw(self, amount):
        pass

    def get_balance(self):
        pass

class BankSystem:
    """
    Mock class simulating interaction with a bank's backend system.
    Attributes:
        accounts (dict): Dictionary mapping account IDs to Account objects.
        pins (dict): Dictionary mapping account IDs to PIN codes.
    """
    def __init__(self):
        """
        Initializes the BankSystem with empty accounts and PIN storage.
        """
        self.accounts = {}
        self.pins = {}

    
class ATMController:
    """
    Controller class that manages ATM operations and user interactions.
    Attributes:
        bank_system (BankSystem): The mock bank system for handling accounts.
        current_card (Card): The currently inserted card (if any).
        current_account (Account): The currently selected account (if any).
        authenticated (bool): Whether the user has been authenticated.
    """
    def __init__(self, bank_system):
        """
        Initializes the ATMController with a given bank system.
        Args:
            bank_system (BankSystem): The bank system to use for account management.
        """
        self.bank_system = bank_system
        self.current_card = None
        self.current_account = None
        self.authenticated = False
