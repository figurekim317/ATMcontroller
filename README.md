# ATM Controller

A simple ATM controller implemented in both Python and C++.

## Clone the Project

Clone the repository using the following command:

```bash
git clone https://github.com/figurekim317/ATMcontroller.git
```

## Requirements

### Python Implementation:
- **Python Version**: Python 3.7.2 or higher.

### C++ Implementation:
- **Compiler**: A C++ compiler supporting C++11 or higher (e.g., GCC, Clang).

## Project Structure

### Python Code:
- **`python/atm.py`**: Contains the ATM controller and related classes.
- **`python/test_atm.py`**: Contains the unit tests for the ATM controller.

### C++ Code:
- **`cpp/atm.cpp`**: Contains the ATM controller and related classes.
- **`cpp/test_atm.cpp`**: Contains the unit tests for the ATM controller.

## How to Build and Run Tests

### Python

1. **Navigate to the `python` directory**:

    ```bash
    cd python
    ```

2. **Run the unit tests**:

    ```bash
    python -m unittest test_atm.py
    ```

### C++

1. **Navigate to the `cpp` directory**:

    ```bash
    cd cpp
    ```

2. **Compile the test program**:

    ```bash
    g++ -std=c++11 -o test_atm atm.cpp test_atm.cpp
    ```

3. **Run the tests**:

    ```bash
    ./test_atm
    ```

## Exception Handling

The code includes exception handling for various error conditions:
- **Negative Amounts**: Attempting to deposit or withdraw negative amounts raises an exception.
- **Insufficient Funds**: Attempting to withdraw more than the available balance raises an exception.
- **Operation Sequence**: Attempting to perform operations without inserting a card or entering the correct PIN raises an exception.
- **Card Duplication**: Attempting to insert a card when one is already inserted raises an exception.

## Testing

The test cases cover:

1. **Card Insertion and Ejection**: 
   - Proper handling of card insertion and ejection.
   - Errors when inserting a second card.

2. **PIN Entry and Validation**: 
   - Correct PIN validation.
   - Handling of incorrect PIN entries.

3. **Account Selection**: 
   - Verification that an account can be selected after successful PIN validation.

4. **Balance Inquiry**: 
   - Correct retrieval of the account balance.

5. **Deposit Functionality**: 
   - Correct updating of balance after deposits.
   - Handling invalid deposit amounts.

6. **Withdrawal Functionality**: 
   - Correct updating of balance after withdrawals.
   - Handling insufficient funds and invalid withdrawal amounts.

7. **Full ATM Flow**: 
   - Testing the entire flow from card insertion to transaction completion.
   - Error handling for operations performed out of sequence.
