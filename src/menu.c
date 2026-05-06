#include <stdio.h>
#include "../includes/auth.h"
#include "../includes/event.h"
#include "../includes/menu.h"
#include "../includes/fileio.h"
#include "../includes/report.h"
#include "../includes/staff.h"
#include "../includes/utils.h"

void AdminMenu() {
    printf("\n=========================================\n");
    printf("            ADMIN MENU                   \n");
    printf("=========================================\n");
    printf("1. Create new event\n");
    printf("2. Edit event information\n");
    printf("3. Delete event\n");
    printf("4. Update event status\n");
    printf("5. Manage staff (Add/Edit/Delete)\n");
    printf("6. View all events list\n");
    printf("7. View event details\n");
    printf("8. Search events\n");
    printf("9. View member participation history\n");
    printf("10. Change password\n");
    printf("11. Setup/Update Email\n"); 
    printf("0. Logout\n");
    printf("=========================================\n");
}

void MemberMenu() {
    printf("\n=========================================\n");
    printf("             MEMBER MENU                 \n");
    printf("=========================================\n");
    printf("1. View personal profile\n");
    printf("2. View joined events list\n");
    printf("3. View joined event details\n");
    printf("4. View participation history\n");
    printf("5. Change password\n");
    printf("6. Setup/Update Email\n"); 
    printf("0. Logout\n");
    printf("=========================================\n");
}

void runAdminMenu(Account *currentAcc, Account list[], int accountCount, Event eventList[], int *eventCount) {
    int choice;
    do {
        AdminMenu();
        printf("Enter your choice (0-11): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch(choice) {
            case 1: 
                createEvent(eventList, eventCount);
                break;
            case 2: 
                editEvent(eventList, *eventCount);
                break;
            case 3: 
                deleteEvent(eventList, eventCount);
                break;
            case 4: 
                updateEventStatus(eventList, *eventCount);
                break;
            case 5: {
                int subChoice;
                do {
                    printf("\n--- STAFF MANAGEMENT ---\n");
                    printf("1. Add staff to event\n");
                    printf("2. Edit staff role in event\n");
                    printf("3. Remove staff from event\n");
                    printf("0. Back to main menu\n");
                    printf("Enter your choice: ");
                    if (scanf("%d", &subChoice) != 1) {
                        while(getchar() != '\n');
                        subChoice = -1;
                    }

                    switch(subChoice) {
                        case 1: 
                            addStaffToEvent(eventList, *eventCount); 
                            break;
                        case 2: 
                            editStaffRole(eventList, *eventCount); 
                            break;
                        case 3: 
                            removeStaffFromEvent(eventList, *eventCount); 
                            break;
                        case 0: 
                            printf(">> Returning to Admin menu...\n");
                            break;
                        default: 
                            printf(">> Error: Invalid choice. Please try again!\n");
                    }
                } while (subChoice != 0);
                break;
            }
            case 6: 
                displayAllEvents(eventList, *eventCount);
                break;
            case 7: 
                eventDetail(eventList, *eventCount);
                break;
            case 8: 
                // 8. Search events
                break;
            case 9: 
                viewMemberHistory(eventList, *eventCount);
                break;
            case 10: 
                changePassword(currentAcc);
                saveAccounts(list, accountCount);
                break;
            case 11: 
                setupEmail(currentAcc, list, accountCount);
                break;
            case 0: 
                if (Logout(currentAcc, list, accountCount) == 1) {
                    return; 
                }
                choice = -1; 
                break;
            default: 
                printf(">> Error: Invalid choice. Please try again!\n");
        }
    } while (choice != 0); 
}

void runMemberMenu(Account *currentAcc, Account list[], int accountCount, Event eventList[], int eventCount) {
    int choice;
    do {
        MemberMenu();
        printf("Enter your choice (0-6): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch(choice) {
            case 1:
                viewMemberProfile(currentAcc);
                break;
            case 2:
                viewJoinedEventsList(eventList, eventCount, currentAcc);
                break;
            case 3:
                viewJoinedEventDetails(eventList, eventCount, currentAcc);
                break;
            case 4:
                viewMyParticipationHistory(eventList, eventCount, currentAcc);
                break;
            case 5:
                changePassword(currentAcc);
                saveAccounts(list, accountCount);
                break;
            case 6:
                setupEmail(currentAcc, list, accountCount);
                break;
            case 0:
                if (Logout(currentAcc, list, accountCount) == 1) {
                    return; 
                }
                choice = -1;
                break;
            default:
                printf(">> Error: Invalid choice. Please try again!\n");
        }
    } while (choice != 0);
}