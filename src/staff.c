// Code for assigning tasks to staff members and viewing staff lists
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

void toUpperCaseStr(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
}

void addStaffToEvent(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;
    int attempts = 0;

    printf("\n--- ADD STAFF TO EVENT ---\n");

    while (attempts < 3) {
        printf("Enter event ID (Ex: EV000001): ");
        scanf(" %[^\n]", searchId);

        for (int i = 0; i < count; i++) {
            if (strcmp(events[i].eventId, searchId) == 0) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            break;
        }

        printf(">> Error: Cannot find event with ID %s!\n", searchId);
        attempts++;
    }

    if (foundIndex == -1) {
        return;
    }

    if (events[foundIndex].status == 2) {
        printf(">> Error: Event has ENDED, cannot add staff!\n");
        return;
    }

    if (events[foundIndex].staffCount >= 30) {
        printf(">> Error: Event has reached the maximum of 30 staff members!\n");
        return;
    }

    char mssvInput[50];
    attempts = 0;

    while (attempts < 3) {
        int existed = 0;

        printf("Enter staff student ID: ");
        scanf(" %[^\n]", mssvInput);

        toUpperCaseStr(mssvInput);

        for (int i = 0; i < events[foundIndex].staffCount; i++) {
            if (strcmp(events[foundIndex].staffList[i].studentId, mssvInput) == 0) {
                existed = 1;
                break;
            }
        }

        if (!existed) {
            break;
        }

        printf(">> Error: Staff member %s already exists in the event!\n", mssvInput);
        attempts++;
    }

    if (attempts == 3) {
        return;
    }

    int role;
    printf("Enter role (0 = Leader, 1 = Member, 2 = Support): ");
    scanf("%d", &role);

    char desc[100];
    printf("Enter task description: ");
    scanf(" %[^\n]", desc);

    int sCount = events[foundIndex].staffCount;

    strcpy(events[foundIndex].staffList[sCount].studentId, mssvInput);
    events[foundIndex].staffList[sCount].role = role;
    strcpy(events[foundIndex].staffList[sCount].description, desc);

    events[foundIndex].staffCount++;

    printf(">> Success: Added staff member %s to event %s.\n", mssvInput, searchId);

    saveEvents(events, count);
}

void editStaffRole(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;
    int attempts = 0;

    printf("\n--- EDIT STAFF INFORMATION IN EVENT ---\n");

    while (attempts < 3) {
        printf("Enter event ID (Ex: EV000001): ");
        scanf(" %[^\n]", searchId);

        for (int i = 0; i < count; i++) {
            if (strcmp(events[i].eventId, searchId) == 0) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            break;
        }

        printf(">> Error: Cannot find event with ID %s!\n", searchId);
        attempts++;
    }

    if (foundIndex == -1) {
        return;
    }

    if (events[foundIndex].status == 1) {
        printf(">> Error: Cannot edit staff while the event is ongoing!\n");
        return;
    }

    if (events[foundIndex].staffCount == 0) {
        printf(">> Error: The event has no staff members yet!\n");
        return;
    }

    char mssvInput[50];
    int staffIndex = -1;

    attempts = 0;

    while (attempts < 3) {
        printf("Enter student ID of the staff member to edit: ");
        scanf(" %[^\n]", mssvInput);

        toUpperCaseStr(mssvInput);

        for (int i = 0; i < events[foundIndex].staffCount; i++) {
            if (strcmp(events[foundIndex].staffList[i].studentId, mssvInput) == 0) {
                staffIndex = i;
                break;
            }
        }

        if (staffIndex != -1) {
            break;
        }

        printf(">> Error: Cannot find staff member %s in the event!\n", mssvInput);
        attempts++;
    }

    if (staffIndex == -1) {
        return;
    }

    printf("Enter new role (0 = Leader, 1 = Member, 2 = Support): ");
    scanf("%d", &events[foundIndex].staffList[staffIndex].role);

    printf("Enter new task description: ");
    scanf(" %[^\n]", events[foundIndex].staffList[staffIndex].description);

    printf(">> Success: Updated staff member %s in event %s.\n", mssvInput, searchId);

    saveEvents(events, count);
}

void removeStaffFromEvent(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;
    int attempts = 0;

    printf("\n--- REMOVE STAFF FROM EVENT ---\n");

    while (attempts < 3) {
        printf("Enter event ID (Ex: EV000001): ");
        scanf(" %[^\n]", searchId);

        for (int i = 0; i < count; i++) {
            if (strcmp(events[i].eventId, searchId) == 0) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex != -1) {
            break;
        }

        printf(">> Error: Cannot find event with ID %s!\n", searchId);
        attempts++;
    }

    if (foundIndex == -1) {
        return;
    }

    if (events[foundIndex].status == 1) {
        printf(">> Error: Cannot remove staff while the event is ongoing!\n");
        return;
    }

    if (events[foundIndex].staffCount == 0) {
        printf(">> Error: The event has no staff members yet!\n");
        return;
    }

    printf("Current staff list:\n");

    for (int i = 0; i < events[foundIndex].staffCount; i++) {
        printf("- Student ID: %s | Role: %d | Task: %s\n",
               events[foundIndex].staffList[i].studentId,
               events[foundIndex].staffList[i].role,
               events[foundIndex].staffList[i].description);
    }

    char mssvInput[50];
    int staffIndex = -1;

    attempts = 0;

    while (attempts < 3) {
        printf("Enter student ID of the staff member to remove: ");
        scanf(" %[^\n]", mssvInput);

        toUpperCaseStr(mssvInput);

        for (int i = 0; i < events[foundIndex].staffCount; i++) {
            if (strcmp(events[foundIndex].staffList[i].studentId, mssvInput) == 0) {
                staffIndex = i;
                break;
            }
        }

        if (staffIndex != -1) {
            break;
        }

        printf(">> Error: Cannot find staff member %s in the event!\n", mssvInput);
        attempts++;
    }

    if (staffIndex == -1) {
        return;
    }

    char confirm;

    printf("Are you sure you want to remove staff member %s from this event? (y/n): ", mssvInput);
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = staffIndex; i < events[foundIndex].staffCount - 1; i++) {
            events[foundIndex].staffList[i] = events[foundIndex].staffList[i + 1];
        }

        events[foundIndex].staffCount--;

        printf(">> Success: Removed staff member %s from event %s.\n", mssvInput, searchId);
    } else {
        printf(">> Delete operation cancelled.\n");
    }

    saveEvents(events, count);
}