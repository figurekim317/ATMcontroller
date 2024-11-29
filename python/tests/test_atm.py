# tests/test_atm.py

import unittest
from atm import Card, BankSystem, ATMController

class TestATMController(unittest.TestCase):
    def setUp(self):
        # Create a mock bank system and add an account
        self.bank = BankSystem()
        self.bank.add_account("12345", "1234", initial_balance=100)
        self.atm = ATMController(self.bank)
        self.card = Card("12345")

    def test_insert_card(self):
        # Test inserting a card
        self.atm.insert_card(self.card)
        self.assertIsNotNone(self.atm.current_card)
        with self.assertRaises(ValueError):
            self.atm.insert_card(self.card)  # Insert card when one is already inserted

    def test_eject_card(self):
        self.atm.insert_card(self.card)
        self.atm.eject_card()
        self.assertIsNone(self.atm.current_card)

    def test_enter_pin(self):
        self.atm.insert_card(self.card)
        self.atm.enter_pin("1234")
        self.assertTrue(self.atm.authenticated)
        # Test invalid PIN
        self.atm.eject_card()
        self.atm.insert_card(self.card)
        with self.assertRaises(ValueError):
            self.atm.enter_pin("0000")

    def test_select_account(self):
        self.atm.insert_card(self.card)
        with self.assertRaises(ValueError):
            self.atm.select_account()  # PIN not validated yet
        self.atm.enter_pin("1234")
        account = self.atm.select_account()
        self.assertIsNotNone(account)
        self.assertEqual(account.account_id, "12345")

    def test_view_balance(self):
        self.atm.insert_card(self.card)
        self.atm.enter_pin("1234")
        balance = self.atm.view_balance()
        self.assertEqual(balance, 100)

    def test_deposit(self):
        self.atm.insert_card(self.card)
        self.atm.enter_pin("1234")
        new_balance = self.atm.deposit(50)
        self.assertEqual(new_balance, 150)
        with self.assertRaises(ValueError):
            self.atm.deposit(-10)  # Negative amount

    def test_withdraw(self):
        self.atm.insert_card(self.card)
        self.atm.enter_pin("1234")
        new_balance = self.atm.withdraw(30)
        self.assertEqual(new_balance, 70)
        with self.assertRaises(ValueError):
            self.atm.withdraw(1000)  # Insufficient funds
        with self.assertRaises(ValueError):
            self.atm.withdraw(-20)  # Negative amount

    def test_full_flow(self):
        # Test the full ATM flow
        self.atm.insert_card(self.card)
        with self.assertRaises(ValueError):
            self.atm.view_balance()  # PIN not entered
        with self.assertRaises(ValueError):
            self.atm.withdraw(10)  # PIN not entered
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
        with self.assertRaises(ValueError):
            self.atm.view_balance()  # No card inserted

if __name__ == '__main__':
    unittest.main()
