# ATM Controller

A simple ATM controller implemented in both Python and C++.

---

## Table of Contents

1. [Clone the Project](#clone-the-project)
2. [Requirements](#requirements)
3. [Project Structure](#project-structure)
4. [Code Overview](#code-overview)
   - [Python Code](#python-code)
   - [C++ Code](#c++-code)
5. [How to Build and Run Tests](#how-to-build-and-run-tests)
   - [Python](#python)
   - [C++](#c++)
   - [Docker](#docker)
6. [Exception Handling](#exception-handling)
7. [Testing](#testing)
8. [Scripts](#scripts)

---

## Clone the Project

Clone the repository using the following command:

```bash
git clone https://github.com/figurekim317/ATMcontroller.git
```

## Requirements

- **Dependencies**: Install required dependencies from requirements.txt:

```bash
pip install -r requirements.txt
```

### Python Implementation:
- **Python Version**: Python 3.7.2 or higher.

### C++ Implementation:
- **Compiler**: A C++ compiler supporting C++11 or higher (e.g., GCC, Clang).
- **Make Utility**: For building the C++ project using the provided Makefile.

### Docker (Optional):
- **Docker**: Install Docker to run the implementations inside containers.

---


## Project Structure
```
ATMcontroller/
├── python/
│   ├── atm/
│   │   ├── __init__.py
│   │   ├── account.py
│   │   ├── atm_controller.py
│   │   ├── bank_system.py
│   │   ├── card.py
│   │   ├── utils.py             # Shared utility functions
│   │   └── config.py            # Configuration file
│   ├── tests/
│   │   ├── __init__.py
│   │   ├── test_atm.py
│   │   ├── test_card.py
│   │   └── run_tests.sh
│   └── README.md                # Description of the Python folder
├── cpp/
│   ├── include/
│   │   ├── Account.h
│   │   ├── ATMController.h
│   │   ├── BankSystem.h
│   │   ├── Card.h
│   │   └── Utility.h            # Shared utility header
│   ├── src/
│   │   ├── Account.cpp
│   │   ├── ATMController.cpp
│   │   ├── BankSystem.cpp
│   │   ├── Card.cpp
│   │   └── Utility.cpp          # Shared utility implementation
│   ├── tests/
│   │   ├── test_atm.cpp
│   │   └── test_card.cpp
│   ├── Makefile
│   └── run_tests.sh
├── docs/
│   ├── API.md                   # API documentation
│   ├── CHANGELOG.md             # Change log
│   ├── ISSUES.md                # Known issues tracker
│   └── README.md                # Project-wide description
└── .github/
    ├── workflows/
    │   └── ci.yml               # GitHub Actions configuration
```

### Python Code Overview

- **`python/atm/`**: Contains the core implementation of the ATM controller and its related classes.
  - **`__init__.py`**: Initializes the `atm` package.
  - **`account.py`**: Defines the `Account` class to manage account-related operations.
  - **`atm_controller.py`**: Implements the `ATMController` class for controlling ATM operations.
  - **`bank_system.py`**: Includes the `BankSystem` class for managing the bank's backend system.
  - **`card.py`**: Contains the `Card` class for managing card-related operations.

- **`python/tests/`**: Contains unit tests for the ATM controller and its components.
  - **`__init__.py`**: Initializes the `tests` package.
  - **`test_atm.py`**: Provides unit tests to verify the functionality of the ATM system.
  - **`run_tests.sh`**: A script to automate the test execution.


### C++ Code Overview

- **`cpp/include/`**: Contains the header files for defining the classes.
  - **`Account.h`**: Declares the `Account` class.
  - **`ATMController.h`**: Declares the `ATMController` class.
  - **`BankSystem.h`**: Declares the `BankSystem` class.
  - **`Card.h`**: Declares the `Card` class.

- **`cpp/src/`**: Contains the source files for implementing the classes.
  - **`Account.cpp`**: Implements the `Account` class.
  - **`ATMController.cpp`**: Implements the `ATMController` class.
  - **`BankSystem.cpp`**: Implements the `BankSystem` class.
  - **`Card.cpp`**: Implements the `Card` class.

- **`cpp/tests/`**: Contains the test code for the C++ implementation.
  - **`test_atm.cpp`**: Includes unit tests for the ATM controller.

- **`cpp/Makefile`**: A `Makefile` for building the C++ project and managing dependencies.
- **`cpp/run_tests.sh`**: A script to automate the build and test process.

---

## How to Build and Run Tests

### Python

1. **Navigate to the `python` directory**:

    ```bash
    cd python
    ```

2. **Run the unit tests**:

    ```bash
    python -m unittest discover -s tests -v

    ```

3. **Alternatively, run ther test script**:
 
    ```bash
    ./run_tests.sh
    ```

    Note: Ensure the script has execute permissions:
 
    ```bash
    chmod +x run_tests.sh
    ```

---

### C++

1. **Navigate to the `cpp` directory**:

    ```bash
    cd cpp
    ```

2. **Build the project using the Makefile**:
    ```bash
    make
    ```


3. **Run the tests**:

    ```bash
    ./test_atm
    ```

4. **Alternatively, run the test script**:

    ```bash
    ./run_tests.sh
    ```

    Note: Ensure the script has execute permissions:
 
    ```bash
    chmod +x run_tests.sh
    ```

5. **Clean the build files (optional)**:

    ```bash
    make clean
    ```

---

### Running with Docker

You can run both the Python and C++ implementations inside Docker containers.

### Python Implementation

### Steps:
1. **Navigate to the `python` directory**:
    ```bash
    cd python
    ```
2. **Build the Docker image**:
    ```bash
    docker build -t atm-python .
    ```
3. **Run the Docker container**:
    ```bash
    docker run --rm atm-python
    ```

### C++ Implementation

### Steps:
1. **Navigate to the `cpp` directory**:
    ```bash
    cd cpp
    ```
2. **Build the Docker image**:
    ```bash
    docker build -t atm-cpp .
    ```
3. **Run the Docker container**:
    ```bash
    docker run --rm atm-cpp
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

---

## Scripts

### Python Test Script

**`run_tests.sh`**: Automates the test execution for the Python implementation.  

### Usage
```bash
cd python
chmod +x run_tests.sh
./run_tests.sh 
```

### C++ Test Script
**`run_tests.sh`**: Automates the build and test process for the C++ implementation.

### Usage
```bash
cd cpp
chmod +x run_tests.sh
./run_tests.sh
```
