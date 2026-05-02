#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../includes/auth.h"
#include "../includes/event.h"
#include "../includes/menu.h"
#include "../includes/fileio.h"
#include "../includes/report.h"
#include "../includes/staff.h"
#include "../includes/utils.h"


int isValidDate(const char* date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) return 0;
    
    if (year < 1900 || year > 2100) return 0; 
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
        daysInMonth[2] = 29;
    }
    
    if (day > daysInMonth[month]) return 0;
    return 1;
}

int getDaysDifference(const char* start, const char* end) {
    struct tm tm_start = {0};
    struct tm tm_end = {0};

    sscanf(start, "%d-%d-%d", &tm_start.tm_year, &tm_start.tm_mon, &tm_start.tm_mday);
    sscanf(end, "%d-%d-%d", &tm_end.tm_year, &tm_end.tm_mon, &tm_end.tm_mday);

    tm_start.tm_year -= 1900;
    tm_start.tm_mon -= 1;
    tm_end.tm_year -= 1900;
    tm_end.tm_mon -= 1;

    time_t time_start = mktime(&tm_start);
    time_t time_end = mktime(&tm_end);

    double seconds = difftime(time_end, time_start);
    return (int)(seconds / (60 * 60 * 24)); 
}

int checkOverlap(Event events[], int count, const char* newStart, const char* newEnd, const char* ignoreEventId) {
    for (int i = 0; i < count; i++) {
        if (ignoreEventId != NULL && strcmp(events[i].eventId, ignoreEventId) == 0) {
            continue;
        }
        if (strcmp(newStart, events[i].endDate) <= 0 && strcmp(events[i].startDate, newEnd) <= 0) {
            return 1;
        }
    }
    return 0;
}

void generateEventId(char *dest, Event events[], int count) {
    int maxId = 0;
    for (int i = 0; i < count; i++) {
        int currentId;
        if (sscanf(events[i].eventId, "EV%d", &currentId) == 1) {
            if (currentId > maxId) {
                maxId = currentId;
            }
        }
    }
    sprintf(dest, "EV%06d", maxId + 1);
}

void createEvent(Event events[], int *count) {
    if (*count >= MAX_EVENTS) {
        printf("System is full, cannot create more events!\n");
        return;
    }

    Event newEv;
    generateEventId(newEv.eventId, events, *count); 
    
    printf("Enter event name: ");
    scanf(" %[^\n]", newEv.name);
    
    printf("Enter event description: ");
    scanf(" %[^\n]", newEv.description);
    
    printf("Enter event location: ");
    scanf(" %[^\n]", newEv.location);
    
    while (1) {
        printf("Enter start date (YYYY-MM-DD): ");
        scanf(" %[^\n]", newEv.startDate);
        if (!isValidDate(newEv.startDate)) {
            printf("\033[1;31m>> Error: Start date is invalid or does not exist!\033[0m\n");
            continue;
        }

        printf("Enter end date (YYYY-MM-DD): ");
        scanf(" %[^\n]", newEv.endDate);
        if (!isValidDate(newEv.endDate)) {
            printf("\033[1;31m>> Error: End date is invalid or does not exist!\033[0m\n");
            continue;
        }

        if (strcmp(newEv.endDate, newEv.startDate) < 0) {
            printf("\033[1;31m>> Error: End date must be after or equal to start date!\033[0m\n");
            continue;
        }

        int days = getDaysDifference(newEv.startDate, newEv.endDate);
        if (days < 4) {
            printf("\033[1;31m>> Error: Event must last at least 4 days (Currently %d days)!\033[0m\n", days);
            continue;
        }

        if (checkOverlap(events, *count, newEv.startDate, newEv.endDate, NULL)) {
            printf("\033[1;33m>> Error: This time overlaps with another existing event!\033[0m\n");
            continue;
        }

        break; 
    }
    
    newEv.status = 0;
    newEv.staffCount = 0;
    
    events[*count] = newEv;
    (*count)++;
    saveEvents(events, *count);
    printf(">> Success: Created event %s\n", newEv.eventId);
}

void editEvent(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;
    int attempts = 3;

    printf("\n--- EDIT EVENT INFORMATION ---\n");
    while (attempts > 0) {
        printf("Enter event ID to edit (e.g., EV000001): ");
        scanf(" %[^\n]", searchId);
        foundIndex = -1;
        for (int i = 0; i < count; i++) {
            if (strcmp(events[i].eventId, searchId) == 0) {
                foundIndex = i;
                break;
            }
        }
        if (foundIndex != -1) {
            break;
        }
        attempts--;
        if (attempts > 0) {
            printf(">> Error: Cannot find event with ID %s! You have %d attempt(s) left.\n", searchId, attempts);
        } else {
            printf(">> Error: Cannot find event with ID %s! Maximum attempts reached. Exiting...\n", searchId);
            return;
        }
    }
    if (events[foundIndex].status == 2) {
        printf(">> Error: Cannot edit a finished event!\n");
        return;
    }

    if (events[foundIndex].status == 1) {
        char confirm;
        printf("!!! WARNING: This event is ONGOING. Are you sure you want to edit? (y/n): ");
        scanf(" %c", &confirm);
        if (confirm != 'y' && confirm != 'Y') {
            printf(">> Edit operation cancelled.\n");
            return;
        }
    }

    printf("\nCurrent information of %s:\n", events[foundIndex].eventId);
    printf("1. Name: %s\n", events[foundIndex].name);
    printf("2. Description: %s\n", events[foundIndex].description);
    printf("3. Location: %s\n", events[foundIndex].location);
    printf("4. Start date: %s\n", events[foundIndex].startDate);
    printf("5. End date: %s\n", events[foundIndex].endDate);

    printf("\nEnter new name: ");
    scanf(" %[^\n]", events[foundIndex].name);
    printf("Enter new description: ");
    scanf(" %[^\n]", events[foundIndex].description);
    printf("Enter new location: ");
    scanf(" %[^\n]", events[foundIndex].location);
    
    while (1) {
        printf("Enter new start date (YYYY-MM-DD): ");
        scanf(" %[^\n]", events[foundIndex].startDate);
        if (!isValidDate(events[foundIndex].startDate)) {
            printf("\033[1;31m>> Error: Start date is invalid or does not exist!\033[0m\n");
            continue;
        }

        printf("Enter new end date (YYYY-MM-DD): ");
        scanf(" %[^\n]", events[foundIndex].endDate);
        if (!isValidDate(events[foundIndex].endDate)) {
            printf("\033[1;31m>> Error: End date is invalid or does not exist!\033[0m\n");
            continue;
        }

        if (strcmp(events[foundIndex].endDate, events[foundIndex].startDate) < 0) {
            printf("\033[1;31m>> Error: End date must be after or equal to start date!\033[0m\n");
            continue;
        }

        int days = getDaysDifference(events[foundIndex].startDate, events[foundIndex].endDate);
        if (days < 4) {
            printf("\033[1;31m>> Error: Event must last at least 4 days (Currently %d days)!\033[0m\n", days);
            continue;
        }

        if (checkOverlap(events, count, events[foundIndex].startDate, events[foundIndex].endDate, events[foundIndex].eventId)) {
            printf("\033[1;33m>> Error: New time overlaps with another event in the system!\033[0m\n");
            continue;
        }

        break;
    }

    printf(">> Success: Updated information for event %s.\n", searchId);
    saveEvents(events, count);
}

void updateEventStatus(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;
    int attempts = 3;

    printf("\n--- UPDATE EVENT STATUS ---\n");
    while (attempts > 0) {
        printf("Enter event ID (e.g., EV000001): ");
        scanf(" %[^\n]", searchId);
        foundIndex = -1;
        for (int i = 0; i < count; i++) {
            if (strcmp(events[i].eventId, searchId) == 0) {
                foundIndex = i;
                break;
            }
        }
        if (foundIndex != -1) {
            break;
        }
        attempts--;
        if (attempts > 0) {
            printf(">> Error: Cannot find event with ID %s! You have %d attempt(s) left.\n", searchId, attempts);
        } else {
            printf(">> Error: Cannot find event with ID %s! Maximum attempts reached. Exiting...\n", searchId);
            return;
        }
    }

    int currentStatus = events[foundIndex].status;
    printf("Current status: ");
    if (currentStatus == 0) printf("Not started\n");
    else if (currentStatus == 1) printf("Ongoing\n");
    else printf("Finished\n");

    if (currentStatus == 2) {
        printf(">> Error: Event is FINISHED, status cannot be changed anymore!\n");
        return;
    }

    if (currentStatus == 0) {
        char confirm;
        printf("Do you want to change to [Ongoing]? (y/n): ");
        scanf(" %c", &confirm);
        
        if (confirm == 'y' || confirm == 'Y') {
            if (events[foundIndex].staffCount == 0) {
                char force;
                printf("!!! WARNING: Event has no staff. Continue anyway? (y/n): "); 
                scanf(" %c", &force);
                if (force != 'y' && force != 'Y') return;
            }
            events[foundIndex].status = 1;
            printf(">> Success: Event is now ONGOING.\n");
        }
    } 
    else if (currentStatus == 1) {
        char confirm;
        printf("Do you want to change to [Finished]? (y/n): ");
        scanf(" %c", &confirm);
        
        if (confirm == 'y' || confirm == 'Y') {
            events[foundIndex].status = 2;
            printf(">> Success: Event is now FINISHED.\n");
        }
    }
	saveEvents(events, count);
}

void deleteEvent(Event events[], int *count) {
    char searchId[10];
    int foundIndex = -1;
    int attempts = 3;
    printf("\n--- DELETE EVENT ---\n");
    while (attempts > 0) {
        printf("Enter event ID to delete (e.g., EV000001): ");
        scanf(" %[^\n]", searchId);
        foundIndex = -1;
        for (int i = 0; i < *count; i++) {
            if (strcmp(events[i].eventId, searchId) == 0) {
                foundIndex = i;
                break;
            }
        }
        if (foundIndex != -1) {
            break;
        }
        attempts--;
        if (attempts > 0) {
            printf(">> Error: Cannot find event with ID %s! You have %d attempt(s) left.\n", searchId, attempts);
        } else {
            printf(">> Error: Cannot find event with ID %s! Maximum attempts reached. Exiting...\n", searchId);
            return;
        }
    }
    printf("Event name: %s\n", events[foundIndex].name);
    printf("Number of staff currently in the event: %d\n", events[foundIndex].staffCount);
    if (events[foundIndex].status == 1) {
        printf(">> Error: Cannot delete an ongoing event!\n"); 
        return;
    }
    char confirm1;
    printf("!!! WARNING: Are you sure you want to delete this event? (y/n): ");
    scanf(" %c", &confirm1);
    if (confirm1 != 'y' && confirm1 != 'Y') {
        printf(">> Delete operation cancelled.\n");
        return;
    }
    char confirm2;
    printf("!!! 2ND CONFIRMATION: This action will permanently delete the event and all its staff. Continue? (y/n): ");
    scanf(" %c", &confirm2);
    if (confirm2 != 'y' && confirm2 != 'Y') {
        printf(">> Delete operation cancelled.\n");
        return;
    }

    for (int i = foundIndex; i < *count - 1; i++) {
        events[i] = events[i + 1];
    }
    (*count)--;
    printf(">> Success: Deleted event %s.\n", searchId);
    saveEvents(events, *count);
}

void displayAllEvents(Event events[], int count) {
    if (count == 0) {
        printf(">> Notice: Event list is empty.\n");
        return;
    }
    int filter;
    int attempts = 0;
    int max_attempts = 3;
    int valid_input = 0;
    while (attempts < max_attempts) {
        printf("\n--- FILTER EVENT LIST ---\n");
        printf("1. All\n");
        printf("2. Not started\n");
        printf("3. Ongoing\n");
        printf("4. Finished\n");
        printf("Select filter type (1-4): ");
        if (scanf("%d", &filter) != 1) {
            while (getchar() != '\n');
            printf(">> Error: Invalid input. Please enter a number.\n");
        } 
        else if (filter >= 1 && filter <= 4) {
            valid_input = 1;
            break;
        } 
        else {
            printf(">> Error: Choice out of range. Please select between 1 and 4.\n");
        }

        attempts++;
        if (attempts < max_attempts) {
            printf(">> You have %d attempt(s) left.\n", max_attempts - attempts);
        }
    }
    if (!valid_input) {
        printf(">> Notice: Too many invalid attempts. Returning to previous menu.\n");
        return;
    }

    int targetStatus = filter - 2;

    printf("\n%-10s | %-20s | %-12s | %-12s | %-15s | %-5s | %-15s\n", 
           "ID", "Event Name", "Start Date", "End Date", "Location", "Staff", "Status");
    printf("------------------------------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (filter == 1 || events[i].status == targetStatus) {
            char statusStr[20];
            if (events[i].status == 0) {
            	strcpy(statusStr, "Not started");
			}else if (events[i].status == 1) {
				strcpy(statusStr, "Ongoing");
			}
            else {
            	strcpy(statusStr, "Finished");
			}
            printf("%-10s | %-20s | %-12s | %-12s | %-15s | %-5d | %-15s\n", 
                   events[i].eventId, 
                   events[i].name, 
                   events[i].startDate, 
                   events[i].endDate, 
                   events[i].location, 
                   events[i].staffCount, 
                   statusStr);
            found = 1;
        }
    }

    if (!found) {
        printf(">> No events match the filter.\n");
    }
    printf("------------------------------------------------------------------------------------------------------------\n");
}

void viewMemberProfile(Account *currentAcc) {
    printf("\n=========================================\n");
    printf("           PERSONAL INFORMATION             \n");
    printf("=========================================\n");
    //printf("%-12s: %s\n", "Full Name", currentAcc->username);
    printf("%-12s: %s\n", "Student ID", currentAcc->studentid);
    // printf("%-12s: %s\n", "Email", currentAcc->email);
    // printf("%-12s: %s\n", "Phone", currentAcc->phone);
    // printf("%-12s: %s\n", "Dept", currentAcc->dept);
    printf("%-12s: %s\n", "Role", (currentAcc->role >= 1) ? "Board of Directors (BOD)" : "Member");
    printf("=========================================\n");
    while (getchar() != '\n'); 
    getchar();
}

void viewMemberHistory(Event events[], int count) {
    char searchId[15];
    int found = 0;
    int attempts = 3;
    printf("\n--- VIEW MEMBER PARTICIPATION HISTORY ---\n");
    while (attempts > 0) {
        printf("Enter Student ID to search: ");
        scanf(" %[^\n]", searchId);
        found = 0;
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < events[i].staffCount; j++) {
                if (strcmp(events[i].staffList[j].studentId, searchId) == 0) {
                    found = 1;
                    break;
                }
            }
            if (found) {
                break;
            }
        }

        if (found) {
            break;
        }

        attempts--;
        if (attempts > 0) {
            printf(">> Error: Cannot find any participation history for Student ID %s! You have %d attempt(s) left.\n", searchId, attempts);
        } else {
            printf(">> Error: Cannot find Student ID %s! Maximum attempts reached. Exiting...\n", searchId);
            return;
        }
    }
    printf("\n%-25s | %-10s | %-15s\n", "Event Name", "Role", "Status");
    printf("----------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < events[i].staffCount; j++) {
            if (strcmp(events[i].staffList[j].studentId, searchId) == 0) {
                char roleStr[20];
                if (events[i].staffList[j].role == 0) {
                    strcpy(roleStr, "Leader");
                } else if (events[i].staffList[j].role == 1) {
                    strcpy(roleStr, "Member");
                } else if (events[i].staffList[j].role == 2) {
                    strcpy(roleStr, "Support");
                } else {
                    strcpy(roleStr, "Unknown");
                }
                char statusStr[20];
                if (events[i].status == 0) {
                    strcpy(statusStr, "Not started");
                } else if (events[i].status == 1) {
                    strcpy(statusStr, "Ongoing");
                } else if (events[i].status == 2) {
                    strcpy(statusStr, "Finished");
                } else {
                    strcpy(statusStr, "Unknown");
                }
                printf("%-25s | %-10s | %-15s\n", 
                       events[i].name, 
                       roleStr, 
                       statusStr);
                       
                break;
            }
        }
    }
    printf("----------------------------------------------------------\n");
}
