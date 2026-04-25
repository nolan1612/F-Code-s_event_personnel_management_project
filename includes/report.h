// Khai báo các tính năng nâng cao
#ifndef REPORT_H
#define REPORT_H


#include "event.h"

typedef struct {
    char studentId[15]; 
    int role;             
    char description[100]; 
    char studentName[100];
} StaffEntry;

int search_events(Event list[], int countEvent, char eId[]);

#endif