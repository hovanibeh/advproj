/* nework.c */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>  


#define MAX_LEN 50
#define PASSWORD_LEN 6
#define FLEET_FILE "fleet.txt"
#define LOGIN_FILE "login.txt"

typedef enum { TRACTOR = 1, EXCAVATOR, ROLLER, CRANE, MIXER } MachineType;
typedef enum { NEVER = 1, LESS_THAN_THREE, LESS_THAN_FIVE, MORE_THAN_FIVE } BreakdownFreq;

// typedef struct for the machines 
typedef struct Machine {
    char Number[MAX_LEN];      // Machine number
    char make[MAX_LEN];        
    char mode[MAX_LEN];        // Model
    int year;                 
    float cost;                // Purchase cost
    float currentV;            
    int  Mileage;              // Current mileage
    int nextMileage;           // Next service mileage
    char Name[MAX_LEN];        // your name
    char Email[MAX_LEN];       // your email
    char Phone[MAX_LEN];       // your phone number
    MachineType type;          // Machine type
    BreakdownFreq breakdowns; 
    struct Machine* next;      
} Machine;

// Structure for login credentials
typedef struct {
    char username[MAX_LEN];
    char password[PASSWORD_LEN + 1];  // +1 for null terminator
} Login;

// Function declarations
void loadLoginData(Login logins[], int* count);
bool loginSystem(Login logins[], int count);
void Pass(char* password);

void loadFleet(Machine** head) {}
void saveFleet(Machine* head) {}
void addMachine(Machine** head) {}
void displayAllMachines(Machine* head) {}
Machine* findMachine(Machine* head, const char* chassis) { return NULL; }
void displayMachine(Machine* head) {}
void updateMachine(Machine* head) {}
void deleteMachine(Machine** head) {}
void generate(Machine* head) {}
void writeReport(Machine* head) {}
void sortByValuation(Machine** head) {}

bool validateEmail(const char* email);

// Main program
int main() {
    Login logins[3];       
    int Count = 0;        
    Machine* fleet = NULL; 

    loadLoginData(logins, &Count);  // Load names from file
    if (!loginSystem(logins, Count)) {  // Validate login
        printf("Access Denied.\n");
        return 0;
    }

    loadFleet(&fleet);  // Load fleet.txt  from file

    int choice;
    do {
        // Display main 
        printf("\n..... Fleet Menu ...................\n");
        printf("1. Add Machine\n");
        printf("2. Display All Machines\n");
        printf("3. Display Details\n");
        printf("4. Update Machine\n");
        printf("5. Delete Machine\n");
        printf("6. Generate all the details for thw machine \n");
        printf("7. Print File\n");
        printf("8. List Machines\n");
        printf("0. Exit\n> ");

        // Input choice
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');  // Clear invalid input
            printf("Invalid....\n");
            continue;
        }
        getchar();  // Clear newline

        // using case for he main menu
        switch (choice) {
        case 1: addMachine(&fleet); break;
        case 2: displayAllMachines(fleet); break;
        case 3: displayMachine(fleet); break;
        case 4: updateMachine(fleet); break;
        case 5: deleteMachine(&fleet); break;
        case 6: generate(fleet); break;
        case 7: writeReport(fleet); break;
        case 8: sortByValuation(&fleet); displayAllMachines(fleet); break;
        case 0: saveFleet(fleet); break;
        default: printf("Invalid choice, please try again.\n");
        }
    } while (choice != 0);  // Loop until exit

    return 0;
}

// pass using '*' characters
void Pass(char* password) {
    int i = 0;
    char ch;
    while (i < PASSWORD_LEN) {
        ch = _getch();  // Read character without echo
        if (ch == '\b' && i > 0) {  
            printf("\b \b");
            i--;
        }
        else if (isalnum(ch)) {  // Accept only letters and digits
            password[i++] = ch;
            printf("*");
        }
        else if (ch == '\r') { 
            break;
        }
    }
    password[i] = '\0';  
    printf("\n");
}

// Read login details from file
void loadLoginData(Login logins[], int* count) {
    FILE* file = fopen(LOGIN_FILE, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open %s\n", LOGIN_FILE);
        exit(1);
    }

    // Read username and password together
    while (!feof(file) && *count < 3) {
        if (fscanf(file, "%s %s", logins[*count].username, logins[*count].password) == 2) {
            (*count)++;
        }
    }
    fclose(file);

}

// basically to confirm the users identity 
bool loginSystem(Login logins[], int count) {
    char user[MAX_LEN], pass[PASSWORD_LEN + 1];
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    Pass(pass); 

    //.................
    for (int i = 0; i < count; i++) {
        if (strcmp(user, logins[i].username) == 0 && strcmp(pass, logins[i].password) == 0)
            return true;
    }
    return false;
}

// Check if email contains '@', '.' and ends in ".com"
bool validateEmail(const char* email) {
    return strstr(email, "@") && strstr(email, ".") && strstr(email, ".com");
}
