#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/auth.h"
#include "../includes/event.h"
#include "../includes/menu.h"
#include "../includes/fileio.h"
#include "../includes/report.h"
#include "../includes/staff.h"
#include "../includes/utils.h"
int checkPassword(char ps[], Account *account);
int Login(char mssv[], char ps[], Account list[], int accountCount) ;
void changePassword(Account *currentAcc);
int Logout(Account *currentAcc, Account list[], int accountCount);

int checkPassword(char ps[], Account *account) {
    if (strcmp(ps, account->password) == 0) {
        account->failCount = 0; 
        return 1; 
    }

    account->failCount++;
    if (account->failCount >= 3) {
        account->isLocked = 1;
        printf("Incorrect password 3 times. This account has been locked!\n");
        return -3;
    } 
    printf("Incorrect password! You have %d attempts left.\n", 3 - account->failCount);
    return -1;  
}

int Login(char mssv[], char ps[], Account list[], int accountCount) {    
    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(mssv, list[i].studentid) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Student ID does not exist!\n");
        return -2;
    }
    if (list[index].isLocked == 1) {
        printf("This account has been locked!\n");
        return -3; 
    }

    int result = checkPassword(ps, &list[index]);
    if (result == 1) return index;
    if (result == -1) return -1;   
    if (result == -3) return -3;
    return -1; 
}

    void changePassword(Account *currentAcc) {
        char oldPass[20], newPass[20], confirmPass[20];
        int failCount = 0; 
        
        printf("\n--- CHANGE PASSWORD ---\n");

    while(1) {
        printf("Enter old password (Type '0' to cancel): ");
        scanf(" %s", oldPass);

        if (strcmp(oldPass, "0") == 0) {
            printf(">> Change password canceled. Returning to menu...\n");
            return; 
        }

        if (strcmp(oldPass, currentAcc->password) != 0) {
            failCount++; 
            printf(">> Error: Incorrect old password!\n");
            
            
            if (failCount >= 3) {
                printf("\033[1;33m[Tip]\033[0m If you forgot your password, type '0' to exit and ask the Admin to reset it!\n");
            } else {
                printf(">> Please try again.\n");
            }
        } else {
            break; 
        }
    }

        while(1) {
            printf("Enter new password (Type '0' to cancel): "); 
            scanf(" %[^\n]", newPass);
            
            if (strcmp(newPass, "0") == 0) {
                printf(">> Change password canceled. Returning to menu...\n");
                return; 
            }

            if (strcmp(newPass, currentAcc->password) == 0) {
                printf(">> Error: New password cannot be the same as the current password!\n");
                continue; 
            }

            printf("Confirm new password: ");
            scanf(" %[^\n]", confirmPass);

            if (strcmp(confirmPass, "0") == 0) {
                printf(">> Change password canceled. Returning to menu...\n");
                return; 
            }

            if (strcmp(newPass, confirmPass) != 0) {
                printf(">> Error: New password and confirmation do not match!\n");
            } 
            else{
                strcpy(currentAcc->password, newPass);
                printf("\033[1;32m>> Success: Password has been changed!\033[0m\n");
                break; 
            }
        }
    }

int Logout(Account *currentAcc, Account list[], int accountCount) {
    printf("Confirm logout? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        saveAccounts(list, accountCount);
        printf(">> Logged out successfully. See you again %s!\n", currentAcc->studentid);
        return 1;
    } else {
        printf(">> Logout canceled.\n");
        return 0;
    }
}