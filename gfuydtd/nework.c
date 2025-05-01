/* howqe.c */
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

typedef struct Machine {
    char Number[MAX_LEN];
    char make[MAX_LEN];
    char mode[MAX_LEN];
    int year;
    float cost;
    float currentValuation;
    int  Mileage;
    int nextMileage;
    char Name[MAX_LEN];
    char Email[MAX_LEN];
    char Phone[MAX_LEN];
    MachineType type;
    BreakdownFreq breakdowns;
    struct Machine* next;
} Machine;

typedef struct {
    char username[MAX_LEN];
    char password[PASSWORD_LEN + 1];
} Login;

void loadLoginData(Login logins[], int* count);
bool loginSystem(Login logins[], int count);
void maskPassword(char* password);

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

int main() {
    Login logins[3];
    int Count = 0;
    Machine* fleet = NULL;

    loadLoginData(logins, & Count);
    if (!loginSystem(logins, Count)) {
        printf("Access Denied.\n");
        return 0;
    }

    loadFleet(&fleet);

    int choice;
    do {
        printf("\n--- Fleet Management Menu ---\n");
        printf("1. Add Machine\n");
        printf("2. Display All Machines\n");
        printf("3. Display Details\n");
        printf("4. Update Machine\n");
        printf("5. Delete Machine\n");
        printf("6. Generate \n");
        printf("7. Print File\n");
        printf("8. List Machines\n");
        printf("0. Exit\n> ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // clear invalid input
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        getchar();

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
    } while (choice != 0);

    return 0;
}

void maskPassword(char* password) {
    int i = 0;
    char ch;
    while (i < PASSWORD_LEN) {
        ch = _getch();
        if (ch == '\b' && i > 0) {
            printf("\b \b");
            i--;
        }
        else if (isalnum(ch)) {
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

void loadLoginData(Login logins[], int* count) {
    FILE* file = fopen(LOGIN_FILE, "r");
    if (!file) {
        perror("Login file not found");
        exit(1);
    }
    while (fscanf(file, "%s %s", logins[*count].username, logins[*count].password) == 2) {
        (*count)++;
    }
    fclose(file);
}

bool loginSystem(Login logins[], int count) {
    char user[MAX_LEN], pass[PASSWORD_LEN + 1];
    printf("Username: ");
    scanf("%s", user);
    printf("Password: ");
    maskPassword(pass);

    for (int i = 0; i < count; i++) {
        if (strcmp(user, logins[i].username) == 0 && strcmp(pass, logins[i].password) == 0)
            return true;
    }
    return false;
}

bool validateEmail(const char* email) {
    return strstr(email, "@") && strstr(email, ".") && strstr(email, ".com");
}
