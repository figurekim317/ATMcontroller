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



'''
TestATMController 클래스 선언:
TestATMController 클래스는 unittest.TestCase를 상속받아 작성되었습니다.
unittest.TestCase를 상속받으면, 테스트 메서드가 자동으로 실행될 수 있는 테스트 클래스가 됩니다.

unittest.main()의 역할:
unittest.main()은 현재 스크립트에서 정의된 모든 테스트 클래스와 메서드를 자동으로 찾아 실행합니다.

unittest는 다음 규칙을 따라 테스트 메서드를 실행합니다:
클래스는 unittest.TestCase를 상속받아야 합니다.
테스트 메서드는 이름이 test_로 시작해야 합니다.
unittest.main()은 실행 결과(통과/실패 여부)를 요약하여 출력합니다.
if __name__ == '__main__'::
Python 스크립트가 직접 실행될 때만 unittest.main()이 호출되도록 보장합니다.
모듈로 임포트될 때는 unittest.main()이 호출되지 않습니다.

**unittest.main()**은 현재 파일에서 unittest.TestCase를 상속받은 클래스들을 모두 탐지합니다.
이 클래스의 메서드 중 이름이 test_로 시작하는 메서드를 자동으로 실행합니다.
2. TestLoader를 통해 테스트 메서드 탐색

unittest.main()은 내부적으로 **TestLoader**를 사용하여 테스트 클래스와 메서드를 탐지합니다.
TestLoader는 다음 기준으로 테스트 메서드를 탐색합니다:
unittest.TestCase를 상속받은 클래스.
이름이 test_로 시작하는 메서드.
3. 실행 순서

테스트 메서드는 알파벳 순서로 실행됩니다.
예를 들어, 다음과 같은 메서드가 있을 경우:
def test_view_balance(self):
    pass

def test_withdraw_successful(self):
    pass

def test_deposit_successful(self):
    pass
실행 순서는 **test_deposit_successful → test_view_balance → test_withdraw_successful**입니다.
4. 테스트 실행

탐지된 테스트 메서드는 각각 독립적으로 실행됩니다.
각 테스트 메서드 실행 전후로 setUp()과 tearDown() 메서드가 호출됩니다(존재할 경우).
정리된 실행 흐름
unittest.main() 호출:
현재 파일에서 unittest.TestCase를 상속받은 클래스를 탐색.
테스트 메서드 탐지:
test_로 시작하는 메서드를 탐지.
테스트 실행:
setUp() → 테스트 메서드 → tearDown()의 순서로 실행.
실행 결과 출력:
각 테스트 메서드의 결과(성공/실패)를 요약하여 출력.

'''