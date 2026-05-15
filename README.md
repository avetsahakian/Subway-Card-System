# Subway Card Access Gate System

A subway card management system built in C programming language.

## How to Compile

Open your terminal and run:

gcc subway_card.c -o subway_card

## How to Run

After compiling, run:

./subway_card

On Windows:

subway_card.exe

## Features

1. Create Card       - Register a new subway card
2. Check Balance     - View current balance of a card
3. Top Up            - Add money to a card
4. Enter Gate        - Deduct fare and grant/deny access
5. View History      - See all transactions of a card
6. Sort Cards        - Sort all cards by balance
7. Display Cards     - Show all registered cards
8. Save and Exit     - Save all data and close the program

## Fare Types

- Standard : 150
- Student  : 100

## Notes

- All data is automatically saved to cards.txt and logs.txt
- Data is loaded back automatically when the program starts again
