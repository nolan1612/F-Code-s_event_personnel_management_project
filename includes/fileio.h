//  Khai báo các hàm đọc/ghi file
#ifndef FILEIO_H
#define FILEIO_H
#include "event.h"
#include "auth.h"
#include <stdio.h>

void saveAccounts(Account list[], int count);
int loadAccounts(Account list[]);

void saveEvents(Event list[], int count);
int loadEvents(Event list[]);

#endif