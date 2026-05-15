#include <stdio.h>    // provides printf, scanf for input/output
#include <stdlib.h>   // provides malloc, realloc for dynamic memory
#include <string.h>   // provides strcpy for copying strings

// ---------------- STRUCT DEFINITIONS ----------------

// Card represents one subway card
typedef struct {
    int id;         // unique identifier of the card
    float balance;  // money stored in the card
} Card;

// Transaction represents one action (top-up or entry)
typedef struct {
    int cardID;        // which card performed the action
    char type[10];     // "TOPUP" or "ENTRY"
    float amount;      // amount added or deducted
} Transaction;

// SmartArray is a dynamic array (resizable array)
typedef struct {
    Card *data;    // pointer to dynamically allocated array of cards
    int size;      // current number of cards stored
    int capacity;  // maximum number before resizing is needed
} SmartArray;

// ---------------- SMART ARRAY FUNCTIONS ----------------

// Initialize the dynamic array
void initArray(SmartArray *arr) {
    arr->size = 0;                           // initially no cards
    arr->capacity = 2;                       // start with small capacity
    arr->data = (Card*)malloc(arr->capacity * sizeof(Card)); 
    // allocate memory for 'capacity' number of Card elements
}

// Resize the array when it's full
void resizeArray(SmartArray *arr) {
    arr->capacity *= 2;  // double the capacity 
    arr->data = (Card*)realloc(arr->data, arr->capacity * sizeof(Card));
    // realloc expands memory while keeping existing data
}

// Add a new card to the dynamic array
void addCard(SmartArray *arr, Card c) {
    if (arr->size == arr->capacity) {  // check if array is full
        resizeArray(arr);              // expand memory
    }
    arr->data[arr->size] = c;  // place new card at next position
    arr->size++;               // increase number of stored cards
}

// ---------------- GLOBAL VARIABLES ----------------

SmartArray cards;           // dynamic list of cards
Transaction logs[1000];     // fixed-size array for transactions
int logCount = 0;           // number of stored transactions

// ---------------- CORE FUNCTIONS ----------------

// Linear search to find card index by ID
int findCard(int id) {
    for (int i = 0; i < cards.size; i++) {     // loop through all cards
        if (cards.data[i].id == id) {          // compare IDs
            return i;                          // return index if found
        }
    }
    return -1;  // return -1 if card does not exist
}

// Create a new card
void createCard() {
    Card c;                      // temporary card object
    c.id = cards.size + 1;       // assign ID sequentially
    c.balance = 0;               // initial balance is zero

    addCard(&cards, c);          // add card using smart array

    printf("Card created with ID: %d\n", c.id);
}

// Add a transaction to log
void addLog(int id, char type[], float amount) {
    logs[logCount].cardID = id;        // store card ID
    strcpy(logs[logCount].type, type); // copy type string
    logs[logCount].amount = amount;    // store amount
    logCount++;                        // increase log count
}

// Display balance of a card
void checkBalance() {
    int id;
    printf("Enter card ID: ");
    scanf("%d", &id);                 // read user input

    int i = findCard(id);             // search for card

    if (i == -1) {                    // if card not found
        printf("Card not found\n");
        return;                       // exit function early
    }

    printf("Balance: %.2f\n", cards.data[i].balance);
}

// Add money to card
void topUp() {
    int id;
    float amount;

    printf("Enter ID and amount: ");
    scanf("%d %f", &id, &amount);     // read both values

    int i = findCard(id);

    if (i == -1) {
        printf("Card not found\n");
        return;
    }

    cards.data[i].balance += amount;  // increase balance

    addLog(id, "TOPUP", amount);      // record transaction

    printf("Top-up successful\n");
}

// Attempt to enter gate
void enterGate() {
    int id, type;
    float fare;

    printf("Enter ID and fare type (1=Standard, 2=Student): ");
    scanf("%d %d", &id, &type);

    int i = findCard(id);

    if (i == -1) {
        printf("Card not found\n");
        return;
    }

    // Select fare based on type (branching)
    if (type == 1)
        fare = 150.0;
    else
        fare = 100.0;

    // Check if sufficient balance
    if (cards.data[i].balance >= fare) {
        cards.data[i].balance -= fare;   // deduct fare

        addLog(id, "ENTRY", fare);       // log transaction

        printf("Access Granted\n");
    } else {
        printf("Access Denied\n");
    }
}

// Show transaction history for a card
void viewHistory() {
    int id;

    printf("Enter card ID: ");
    scanf("%d", &id);

    printf("\n--- Transaction History ---\n");

    for (int i = 0; i < logCount; i++) {       // loop through all logs
        if (logs[i].cardID == id) {            // match card ID
            printf("%s %.2f\n", logs[i].type, logs[i].amount);
        }
    }
}

// ---------------- FILE HANDLING ----------------

// Save cards and logs to files
void saveData() {
    FILE *f = fopen("cards.txt", "w");   // open file for writing

    fprintf(f, "%d\n", cards.size);      // write number of cards

    for (int i = 0; i < cards.size; i++) {
        fprintf(f, "%d %.2f\n",
                cards.data[i].id,
                cards.data[i].balance); // write each card
    }
    fclose(f); // close file

    FILE *l = fopen("logs.txt", "w");   // open log file

    fprintf(l, "%d\n", logCount);       // write log count

    for (int i = 0; i < logCount; i++) {
        fprintf(l, "%d %s %.2f\n",
                logs[i].cardID,
                logs[i].type,
                logs[i].amount);       // write each log
    }
    fclose(l);

    printf("Data saved\n");
}

// Load data from files
void loadData() {
    FILE *f = fopen("cards.txt", "r");

    if (f != NULL) {                    // check if file exists
        int n;
        fscanf(f, "%d", &n);            // read number of cards

        for (int i = 0; i < n; i++) {
            Card c;
            fscanf(f, "%d %f", &c.id, &c.balance);
            addCard(&cards, c);         // rebuild array
        }
        fclose(f);
    }

    FILE *l = fopen("logs.txt", "r");

    if (l != NULL) {
        fscanf(l, "%d", &logCount);     // read number of logs

        for (int i = 0; i < logCount; i++) {
            fscanf(l, "%d %s %f",
                   &logs[i].cardID,
                   logs[i].type,
                   &logs[i].amount);
        }
        fclose(l);
    }
}

// ---------------- SORTING ----------------

// Bubble sort cards by balance
void sortCards() {
    for (int i = 0; i < cards.size - 1; i++) {
        for (int j = 0; j < cards.size - i - 1; j++) {

            if (cards.data[j].balance > cards.data[j + 1].balance) {

                Card temp = cards.data[j];              // temporary storage
                cards.data[j] = cards.data[j + 1];      // swap
                cards.data[j + 1] = temp;
            }
        }
    }

    printf("Cards sorted by balance\n");
}

// Display all cards
void displayCards() {
    printf("\n--- Cards ---\n");

    for (int i = 0; i < cards.size; i++) {
        printf("ID: %d | Balance: %.2f\n",
               cards.data[i].id,
               cards.data[i].balance);
    }
}

// ---------------- MAIN FUNCTION ----------------

int main() {
    int choice;

    initArray(&cards);   // initialize dynamic array

    loadData();          // load saved data at program start

    while (1) {          // infinite loop for menu
        printf("\n1.Create 2.Check 3.TopUp 4.Enter 5.History 6.Sort 7.Show 8.Save&Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createCard(); break;
            case 2: checkBalance(); break;
            case 3: topUp(); break;
            case 4: enterGate(); break;
            case 5: viewHistory(); break;
            case 6: sortCards(); break;
            case 7: displayCards(); break;
            case 8: saveData(); return 0; // save before exiting
            default: printf("Invalid option\n");
        }
    }

    return 0;
}