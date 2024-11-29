from atm import Card, Account, BankSystem, ATMController
import unittest

class TestATMController(unittest.TestCase):
    def setUp(self):
        # Create a mock bank system and add an account
        self.bank = BankSystem()
        self.bank.add_account("12345", "1234", initial_balance=100)
        self.atm = ATMController(self.bank)
        self.card = Card("12345")

    def test_enter_pin(self):
        pass

    def test_select_account(self):
        pass

    def test_view_balance(self):
        pass

    def test_deposit(self):
        pass

    def test_withdraw(self):
        pass


if __name__ == '__main__':
    unittest.main()