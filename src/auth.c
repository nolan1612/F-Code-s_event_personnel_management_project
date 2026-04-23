#include <stdio.h>
#include <string.h>
#include "auth.h"

int checkPassword(char ps[], Account list[], int index) {
    if (strcmp(ps, list[index].password) == 0) {
        list[index].failCount = 0; 
        return 1;
    } else {
        list[index].failCount++;
        
        if (list[index].failCount >= 3) {
            printf("Nhap sai mat khau 3 lan. Khoa tai khoan va thoat chuong trinh!\n");
            list[index].isLocked = 1;
            return -1;
        } else {
            printf("Sai mat khau! Ban con %d lan thu.\n", 3 - list[index].failCount);
            return 0;
        }
    }
}

int Login(char mssv[], char ps[], Account list[], int accountCount) {    
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(mssv, list[i].studentid) == 0) {
            
            if (list[i].isLocked == 1) {
                printf("Tai khoan nay da bi khoa tu truoc! Thoat chuong trinh.\n");
                return -1; 
            }
            
            int passCheck = checkPassword(ps, list, i);
            
            if (passCheck == 1) return i; 
            if (passCheck == -1) return -1; 
            return -2; 
        } 
    }
    printf("MSSV khong ton tai!\n");
    return -2; 
}

void changePassword(Account *currentAcc) {
    char oldPass[20], newPass[20], confirmPass[20];

    /*printf("\n--- DOI MAT KHAU ---\n");
    printf("Nhap mat khau cu: ");
    scanf(" %[^\n]", oldPass);

    if (strcmp(oldPass, currentAcc->password) != 0) {
        printf(">> Loi: Mat khau cu khong chinh xac!\n");
        return;
    } */

    printf("Nhap mat khau moi: ");
    scanf(" %[^\n]", newPass);
    printf("Xac nhan mat khau moi: ");
    scanf(" %[^\n]", confirmPass);

    if (strcmp(newPass, confirmPass) == 0) {
        strcpy(currentAcc->password, newPass);
      
        printf(">> Thanh cong: Da thay doi mat khau!\n");
    } else {
        printf(">> Loi: Mat khau xac nhan khong khop!\n");
    }
}