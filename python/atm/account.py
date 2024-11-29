class Account:
    """
    Represents a bank account with basic operations.
    
    Attributes:
        account_id (str): Unique identifier for the account.
        balance (int): Current balance in the account.
    """

    def __init__(self, account_id: str, balance: int = 0):
        """
        Initializes an account with an ID and an optional initial balance.
        
        Args:
            account_id (str): The unique ID for the account.
            balance (int, optional): Initial balance. Defaults to 0.
        
        Raises:
            ValueError: If the initial balance is negative.
        """
        if balance < 0:
            raise ValueError("Initial balance cannot be negative.")
        self.account_id: str = account_id
        self.balance: int = balance

    def deposit(self, amount: int) -> int:
        """
        Deposits a specified amount into the account.
        
        Args:
            amount (int): The amount to deposit.
        
        Returns:
            int: Updated account balance.
        
        Raises:
            ValueError: If the amount is non-positive.
        """
        if amount <= 0:
            raise ValueError("Deposit amount must be positive.")
        self.balance += amount
        return self.balance

    def withdraw(self, amount: int) -> int:
        """
        Withdraws a specified amount from the account.
        
        Args:
            amount (int): The amount to withdraw.
        
        Returns:
            int: Updated account balance.
        
        Raises:
            ValueError: If the amount is non-positive or exceeds the balance.
        """
        if amount <= 0:
            raise ValueError("Withdrawal amount must be positive.")
        if amount > self.balance:
            raise ValueError("Insufficient balance.")
        self.balance -= amount
        return self.balance

    def get_balance(self) -> int:
        """
        Retrieves the current account balance.
        
        Returns:
            int: Current balance.
        """
        return self.balance
