//  Định nghĩa struct Event (ID, Tên, Trạng thái, Số lượng...)
#ifndef EVENT_H
#define EVENT_H
#include "auth.h"
#define MAX_STAFF_PER_EVENT 30
#define MAX_EVENTS 1000000

typedef struct {
    char studentId[15]; 
    char studentName[50];
    int role;             
    char description[100]; 
} StaffEntry;

typedef struct {
    char eventId[10];      
    char name[100];        
    char description[500];  
    char location[100];     
    char startDate[11];  
    char endDate[11];      
    int status;             
    int staffCount;         
    StaffEntry staffList[MAX_STAFF_PER_EVENT];
} Event;

void generateEventId(char *dest, Event events[], int count);
int getDaysDifference(const char* start, const char* end);
int isValidDate(const char* date);
int checkOverlap(Event events[], int count, const char* newStart, const char* newEnd, const char* ignoreEventId);
void createEvent(Event events[], int *count);
void editEvent(Event events[], int count);
void updateEventStatus(Event events[], int count);
void deleteEvent(Event events[], int *count);
void displayAllEvents(Event events[], int count);
void viewMemberProfile(Account *currentAcc);
void viewMemberHistory(Event events[], int count);
#endif