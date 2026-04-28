#include <stdio.h>
#include <stdlib.h>
#include "../includes/auth.h"
#include "../includes/event.h"
#include "../includes/menu.h"
#include "../includes/fileio.h"
#include "../includes/report.h"
#include "../includes/staff.h"
#include "../includes/utils.h"

Account list[MAX_ACCOUNTS];
Event eventList[MAX_EVENTS];

int main() {
    char mssv[10];
    char ps[20];
    int choice;
    
    int accountCount = loadAccounts(list);
    int eventCount = loadEvents(eventList);
    printf("[System] Successfully loaded %d accounts and %d events from file.\n", accountCount, eventCount);

    while (1) {
        printf("\n=========================================\n");
        printf("         WELCOME TO F-CODE STAFF         \n");
        printf("=========================================\n");
        printf("1. Login\n");
        printf("0. Exit program\n");
        printf("-----------------------------------------\n");
        printf("Your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Clear buffer if input is not an integer
            continue;
        }

        if (choice == 0) {
            printf("Goodbye! See you again.\n");
            break;
        } else if (choice == 1) {
           
            printf("\n--- LOGIN ---\n");
            printf("Enter Student ID: ");
            scanf(" %[^\n]", mssv); 
            
            while(1) {  
                printf("Enter password: ");
                scanf(" %[^\n]", ps);
                
                int status = Login(mssv, ps, list, accountCount);
               
                if (status >= 0) {
                    printf("\n>>> Login successful! <<<\n");
                    if (list[status].role == 1) {
                        runAdminMenu(&list[status], list, accountCount, eventList, &eventCount);
                    } else {
                        runMemberMenu(&list[status], list, accountCount, eventList, eventCount);
                    }
                    saveAccounts(list, accountCount); 
                    break;
                } else if (status == -1) {
                    saveAccounts(list, accountCount);
                    
                } else if (status == -2 || status == -3){
                    saveAccounts(list, accountCount);
                    break;
                }
            }
        } else {
            printf(">> Error: Invalid choice!\n");
        }
    }
    return 0;
}