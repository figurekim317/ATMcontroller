# Configuration settings for the ATM system

# General settings
ATM_LIMIT = 1000  # Maximum withdrawal limit per transaction
BANK_NAME = "Global Bank"  # Bank name displayed in the system

# Logging settings
LOGGING_ENABLED = True  # Enable or disable logging
LOG_FILE = "atm_logs.txt"  # File to store logs (if enabled)

# Security settings
MAX_PIN_ATTEMPTS = 3  # Maximum number of incorrect PIN attempts before card lock
PIN_LENGTH = 4  # Required length of the PIN

# UI settings
WELCOME_MESSAGE = f"Welcome to {BANK_NAME}!"  # Message displayed when ATM starts
