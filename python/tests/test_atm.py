import unittest
from atm import Card, BankSystem, ATMController

class TestATMController(unittest.TestCase):
    def setUp(self):
        """Set up a mock bank system and add an account."""
        self.bank = BankSystem()
        # Use a valid 16-digit card number that passes the Luhn algorithm
        self.bank.add_account("4539578763621486", "1234", initial_balance=100)
        self.card = Card("4539578763621486")  # Valid card number
        self.atm = ATMController(self.bank)

    def insert_card_and_authenticate(self, pin="1234"):
        """Helper method to insert a card and authenticate with a PIN."""
        self.atm.insert_card(self.card)
        self.atm.enter_pin(pin)

    def test_insert_card_success(self):
        """Test inserting a card successfully."""
        self.atm.insert_card(self.card)
        self.assertIsNotNone(self.atm.current_card)

    def test_insert_card_already_inserted(self):
        """Test inserting a card when one is already inserted."""
        self.atm.insert_card(self.card)
        with self.assertRaises(ValueError):
            self.atm.insert_card(self.card)

    def test_eject_card_success(self):
        """Test ejecting a card successfully."""
        self.atm.insert_card(self.card)
        self.atm.eject_card()
        self.assertIsNone(self.atm.current_card)

    def test_enter_pin_correct(self):
        """Test entering a correct PIN."""
        self.insert_card_and_authenticate()
        self.assertTrue(self.atm.authenticated)

    def test_enter_pin_incorrect(self):
        """Test entering an incorrect PIN."""
        self.atm.insert_card(self.card)
        with self.assertRaises(ValueError):
            self.atm.enter_pin("0000")

    def test_select_account_after_authentication(self):
        """Test selecting an account after successful authentication."""
        self.insert_card_and_authenticate()
        account = self.atm.select_account()
        self.assertIsNotNone(account)
        self.assertEqual(account.account_id, "4539578763621486")

    def test_view_balance_authenticated(self):
        """Test viewing balance after authentication."""
        self.insert_card_and_authenticate()
        balance = self.atm.view_balance()
        self.assertEqual(balance, 100)

    def test_deposit_successful(self):
        """Test depositing money into an account."""
        self.insert_card_and_authenticate()
        new_balance = self.atm.deposit(50)
        self.assertEqual(new_balance, 150)

    def test_deposit_invalid_amount(self):
        """Test depositing a negative amount."""
        self.insert_card_and_authenticate()
        with self.assertRaises(ValueError):
            self.atm.deposit(-10)

    def test_withdraw_successful(self):
        """Test withdrawing money from an account."""
        self.insert_card_and_authenticate()
        new_balance = self.atm.withdraw(30)
        self.assertEqual(new_balance, 70)

    def test_withdraw_exceed_balance(self):
        """Test withdrawing more money than the account balance."""
        self.insert_card_and_authenticate()
        with self.assertRaises(ValueError):
            self.atm.withdraw(1000)

    def test_withdraw_negative_amount(self):
        """Test withdrawing a negative amount."""
        self.insert_card_and_authenticate()
        with self.assertRaises(ValueError):
            self.atm.withdraw(-20)

    def test_full_atm_flow(self):
        """Test the full ATM operation flow."""
        self.insert_card_and_authenticate()
        self.assertEqual(self.atm.view_balance(), 100)
        self.atm.deposit(50)
        self.assertEqual(self.atm.view_balance(), 150)
        self.atm.withdraw(70)
        self.assertEqual(self.atm.view_balance(), 80)
        self.atm.eject_card()
        with self.assertRaises(ValueError):
            self.atm.view_balance()

if __name__ == '__main__':
    unittest.main()
