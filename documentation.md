# Documentation — Subway Card Access Gate System

## 1. Functionality

The application supports the following features:

- Create Card: Registers a new card with a unique ID and zero balance
- Check Balance: Displays the current balance of a card by ID
- Top Up: Adds a specified amount of money to a card
- Enter Gate: Checks balance and deducts fare (150 Standard / 100 Student)
- View History: Shows all transactions belonging to a specific card
- Sort Cards: Sorts all cards from lowest to highest balance
- Display Cards: Shows all registered cards with their balances
- Save and Exit: Saves all cards and transactions to text files

## 2. Code Organization

The source code is organized into 6 sections:

### Structs
- Card: stores card ID and balance
- Transaction: stores card ID, type (TOPUP/ENTRY), and amount
- SmartArray: a dynamic resizable array that holds all cards

### Smart Array
- initArray(): initializes the dynamic array with capacity 2
- resizeArray(): doubles the capacity when the array is full
- addCard(): adds a new card, resizes if needed

### Core Functions
- findCard(): linear search to find a card by ID
- createCard(): creates a new card with auto-assigned ID
- addLog(): records a transaction into the logs array
- checkBalance(): displays balance of a card
- topUp(): adds money to a card and logs the transaction
- enterGate(): deducts fare and grants or denies access
- viewHistory(): displays transaction history of a card

### File Handling
- saveData(): writes all cards and logs to cards.txt and logs.txt
- loadData(): reads and rebuilds data from those files on startup

### Sorting
- sortCards(): sorts cards by balance using bubble sort
- displayCards(): prints all cards and their balances

### Main Function
- Initializes the array and loads saved data
- Runs an infinite menu loop until user selects Save and Exit

## 3. Testing

The application was tested manually by going through each menu option:

- Created multiple cards and verified auto-assigned IDs
- Topped up cards and checked updated balances
- Entered gate with sufficient balance - Access Granted confirmed
- Entered gate with insufficient balance - Access Denied confirmed
- Verified student fare (100) and standard fare (150) are correctly deducted
- Viewed transaction history and confirmed all logs appear correctly
- Sorted cards and confirmed order from lowest to highest balance
- Saved data, closed the program, reopened and confirmed data was loaded back correctly
