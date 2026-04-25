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
    printf("[He thong] Da tai thanh cong %d tai khoan va %d su kien tu file.\n", accountCount, eventCount);

	while (1) {
        printf("\n=========================================\n");
        printf("    CHAO MUNG DEN VOI F-CODE STAFF   \n");
        printf("=========================================\n");
        printf("1. Dang nhap\n");
        printf("0. Thoat chuong trinh\n");
        printf("-----------------------------------------\n");
        printf("Lua chon cua ban: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice == 0) {
            printf("Tam biet! Hen gap lai.\n");
            break;
        } else if (choice == 1) {
            printf("\n--- DANG NHAP ---\n");
            printf("Nhap MSSV: ");
            scanf(" %[^\n]", mssv); 
            printf("Nhap mat khau: ");
            scanf(" %[^\n]", ps);
            int status = Login(mssv, ps, list, accountCount);
            if (status >= 0) {
                printf("\n>>> Dang nhap thanh cong! <<<\n");
                if (list[status].role == 1) {
                    runAdminMenu(&list[status], list, accountCount,eventList, &eventCount);
                } else {
                    runMemberMenu(&list[status], list, accountCount,eventList, eventCount);
                }
                saveAccounts(list, accountCount); 
            } else if (status == -1) {
                saveAccounts(list, accountCount);
                exit(1); 
            }
        } else {
            printf(">> Loi: Lua chon khong hop le!\n");
        }
    }
    
    return 0;
}