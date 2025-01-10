#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store transaction details
typedef struct Transaction {
    char type[10];  // "Deposit" or "Withdrawal"
    float amount;
    struct Transaction *next;
} Transaction;

// Structure to store bank account details
typedef struct Account {
    int accountNumber;
    char accountHolderName[100];
    float balance;
    Transaction *transactionHistory; // Linked list of transactions
    struct Account *next;
} Account;

// Function to create a new account
Account* createAccount(int accountNumber, const char *accountHolderName) {
    Account *newAccount = (Account *)malloc(sizeof(Account));
    if (newAccount == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newAccount->accountNumber = accountNumber;
    strcpy(newAccount->accountHolderName, accountHolderName);
    newAccount->balance = 0.0;
    newAccount->transactionHistory = NULL;
    newAccount->next = NULL;
    return newAccount;
}

// Function to add a transaction
void addTransaction(Account *account, const char *type, float amount) {
    Transaction *newTransaction = (Transaction *)malloc(sizeof(Transaction));
    if (newTransaction == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strcpy(newTransaction->type, type);
    newTransaction->amount = amount;
    newTransaction->next = account->transactionHistory;
    account->transactionHistory = newTransaction;
}

// Function to deposit money
void deposit(Account *account, float amount) {
    account->balance += amount;
    addTransaction(account, "Deposit", amount);
    printf("Deposited %.2f. New balance: %.2f\n", amount, account->balance);
}

// Function to withdraw money
void withdraw(Account *account, float amount) {
    if (account->balance >= amount) {
        account->balance -= amount;
        addTransaction(account, "Withdrawal", amount);
        printf("Withdrew %.2f. New balance: %.2f\n", amount, account->balance);
    } else {
        printf("Insufficient balance. Withdrawal denied.\n");
    }
}

// Function to print the transaction history
void printTransactionHistory(Account *account) {
    if (account->transactionHistory == NULL) {
        printf("No transaction history.\n");
        return;
    }
    
    printf("Transaction history for account %d:\n", account->accountNumber);
    Transaction *current = account->transactionHistory;
    while (current != NULL) {
        printf("%s: %.2f\n", current->type, current->amount);
        current = current->next;
    }
}

// Function to check balance
void checkBalance(Account *account) {
    printf("Current balance: %.2f\n", account->balance);
}

// Function to find an account by account number
Account* findAccount(Account *head, int accountNumber) {
    Account *current = head;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL;  // Account not found
}

// Function to create a new account and add to the list
void addAccount(Account **head, int accountNumber, const char *accountHolderName) {
    Account *newAccount = createAccount(accountNumber, accountHolderName);
    newAccount->next = *head;
    *head = newAccount;
}

int main() {
    Account *head = NULL;
    int choice, accountNumber;
    float amount;
    char name[100];

    while (1) {
        printf("\nBanking System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transaction History\n");
        printf("5. Check Balance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Create a new account
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter account holder name: ");
                getchar();  // To consume newline character left by scanf
                fgets(name, 100, stdin);
                name[strcspn(name, "\n")] = '\0';  // Remove newline character
                addAccount(&head, accountNumber, name);
                printf("Account created successfully!\n");
                break;

            case 2:
                // Deposit money
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter deposit amount: ");
                scanf("%f", &amount);
                {
                    Account *account = findAccount(head, accountNumber);
                    if (account) {
                        deposit(account, amount);
                    } else {
                        printf("Account not found.\n");
                    }
                }
                break;

            case 3:
                // Withdraw money
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter withdrawal amount: ");
                scanf("%f", &amount);
                {
                    Account *account = findAccount(head, accountNumber);
                    if (account) {
                        withdraw(account, amount);
                    } else {
                        printf("Account not found.\n");
                    }
                }
                break;

            case 4:
                // Print transaction history
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                {
                    Account *account = findAccount(head, accountNumber);
                    if (account) {
                        printTransactionHistory(account);
                    } else {
                        printf("Account not found.\n");
                    }
                }
                break;

            case 5:
                // Check balance
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                {
                    Account *account = findAccount(head, accountNumber);
                    if (account) {
                        checkBalance(account);
                    } else {
                        printf("Account not found.\n");
                    }
                }
                break;

            case 6:
                // Exit
                printf("Exiting the banking system.\n");
                exit(0);

            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

