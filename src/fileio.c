#include "../includes/auth.h"
#include "../includes/event.h"
#include "../includes/menu.h"
#include "../includes/fileio.h"
#include "../includes/report.h"
#include "../includes/staff.h"
#include "../includes/utils.h"
void saveAccounts(Account list[], int count);
void saveAccounts(Account list[], int count);
void saveEvents(Event list[], int count);
int loadEvents(Event list[]);
void saveAccounts(Account list[], int count) {
    FILE *file = fopen("data/account.dat", "w"); 
    
    if (file == NULL) {
        printf("Loi .dat!\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
       
        fprintf(file, "%s %s %s %d %d %d\n", 
                list[i].studentid, 
                list[i].username,
                list[i].password, 
                list[i].role, 
                list[i].isLocked, 
                list[i].failCount);
    }
    
    fclose(file);
}


int loadAccounts(Account list[]) {
   
    FILE *file = fopen("data/account.dat", "r"); 
    
    if (file == NULL) {
        printf("[He thong] File data/account.dat chua ton tai!\n");
        return 0; 
    }
    
    int count = 0;

    while (fscanf(file, "%s %s %s %d %d %d", 
                  list[count].studentid, 
                  list[count].username,   
                  list[count].password, 
                  &list[count].role, 
                  &list[count].isLocked, 
                  &list[count].failCount) == 6) { 
        count++;
    }
    
    fclose(file);
    return count;
}

void saveEvents(Event list[], int count) {
    FILE *file = fopen("data/events.dat", "wb"); 
    if (file == NULL) {
        printf("\033[1;31m[Loi]\033[0m Khong the mo file events.dat de ghi!\n");
        return;
    }
    size_t written = fwrite(list, sizeof(Event), count, file);
    
    if (written != (size_t)count) {
        printf("\033[1;31m[Loi]\033[0m Ghi du lieu su kien bi loi!\n");
    }
    
    fclose(file);
}

int loadEvents(Event list[]) {
    FILE *file = fopen("data/events.dat", "rb"); 
    if (file == NULL) {
        return 0; 
    }
    
    int count = 0;
    while (fread(&list[count], sizeof(Event), 1, file) == 1) {
        count++;
        if (count >= MAX_EVENTS) break;
    }
    
    fclose(file);
    return count;
}