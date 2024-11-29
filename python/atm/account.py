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
        """
        Deposits a specified amount into the account.
        Args:
            amount (int): The amount to deposit.
        Returns:
            int: Updated account balance.
        Raises:
            ValueError: If amount is non-positive.
        """
        if amount <= 0:
            raise ValueError("Deposit amount must be positive.")
        self.balance += amount
        return self.balance

    def withdraw(self, amount):
        """
        Withdraws a specified amount from the account.
        Args:
            amount (int): The amount to withdraw.
        Raises:
            ValueError: If amount exceeds balance or is non-positive.
        Returns:
            int: Updated account balance.
        """
        if amount <= 0:
            raise ValueError("Withdrawal amount must be positive.")
        if amount > self.balance:
            raise ValueError("Insufficient balance.")
        self.balance -= amount
        return self.balance

    def get_balance(self):
        """
        Retrieves the current account balance.
        Returns:
            int: Current balance.
        """
        return self.balance
