import unittest
from atm import Card, BankSystem, ATMController

class TestATMController(unittest.TestCase):
    def setUp(self):
        # Set up a mock bank system and add an account
        self.bank = BankSystem()
        self.bank.add_account("12345", "1234", initial_balance=100)
        self.atm = ATMController(self.bank)
        self.card = Card("12345")

    def test_insert_card(self):
        # Test inserting a card
        self.atm.insert_card(self.card)
        self.assertIsNotNone(self.atm.current_card)
        # Attempt to insert another card when one is already inserted
        with self.assertRaises(ValueError):
            self.atm.insert_card(self.card)

    def test_eject_card(self):
        # Test ejecting the card
        self.atm.insert_card(self.card)
        self.atm.eject_card()
        self.assertIsNone(self.atm.current_card)

    def test_enter_pin(self):
        # Test entering the correct PIN
        self.atm.insert_card(self.card)
        self.atm.enter_pin("1234")
        self.assertTrue(self.atm.authenticated)
        # Test entering an incorrect PIN
        self.atm.eject_card()
        self.atm.insert_card(self.card)
        with self.assertRaises(ValueError):
            self.atm.enter_pin("0000")

    def test_select_account(self):
        # Test selecting an account after PIN validation
        self.atm.insert_card(self.card)
        with self.assertRaises(ValueError):
            self.atm.select_account()  # PIN not validated yet
        self.atm.enter_pin("1234")
        account = self.atm.select_account()
        self.assertIsNotNone(account)
        self.assertEqual(account.account_id, "12345")

    def test_view_balance(self):
        # Test viewing the account balance
        self.atm.insert_card(self.card)
        self.atm.enter_pin("1234")
        balance = self.atm.view_balance()
        self.assertEqual(balance, 100)

    def test_deposit(self):
        # Test depositing money into the account
        self.atm.insert_card(self.card)
        self.atm.enter_pin("1234")
        new_balance = self.atm.deposit(50)
        self.assertEqual(new_balance, 150)
        # Test depositing a negative amount
        with self.assertRaises(ValueError):
            self.atm.deposit(-10)

    def test_withdraw(self):
        # Test withdrawing money from the account
        self.atm.insert_card(self.card)
        self.atm.enter_pin("1234")
        new_balance = self.atm.withdraw(30)
        self.assertEqual(new_balance, 70)
        # Test withdrawing more than the balance
        with self.assertRaises(ValueError):
            self.atm.withdraw(1000)
        # Test withdrawing a negative amount
        with self.assertRaises(ValueError):
            self.atm.withdraw(-20)

    def test_full_flow(self):
        # Test the full ATM operation flow
        self.atm.insert_card(self.card)
        # Attempt to view balance without entering PIN
        with self.assertRaises(ValueError):
            self.atm.view_balance()
        # Attempt to withdraw without entering PIN
        with self.assertRaises(ValueError):
            self.atm.withdraw(10)
        self.atm.enter_pin("1234")
        account = self.atm.select_account()
        balance = self.atm.view_balance()
        self.assertEqual(balance, 100)
        self.atm.deposit(50)
        balance = self.atm.view_balance()
        self.assertEqual(balance, 150)
        self.atm.withdraw(70)
        balance = self.atm.view_balance()
        self.assertEqual(balance, 80)
        self.atm.eject_card()
        # Attempt to view balance after ejecting card
        with self.assertRaises(ValueError):
            self.atm.view_balance()

if __name__ == '__main__':
    unittest.main()
