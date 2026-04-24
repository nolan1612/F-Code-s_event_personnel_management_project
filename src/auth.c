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


int checkPassword(char ps[], Account list[], int index) {
    do{
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
                printf("Nhap lai mat khau: ");
                scanf(" %[^\n]", ps);
            }
        }
    } while (list[index].failCount < 3);
}
// int checkPassword(char ps[], Account *account) {
//     if (strcmp(ps, account->password) == 0) {
//         account->failCount = 0; 
//         return 1; 
//     }

//     account->failCount++;
//     if (account->failCount >= 3) {
//         account->isLocked = 1;
//         printf("Nhap sai mat khau 3 lan. Tai khoan da bi khoa!\n");
//         return -3;
//     } 
//     printf("Sai mat khau! Ban con %d lan thu.\n", 3 - account->failCount);
//     return -1;  


    
//     if (strcmp(ps, account->password) == 0) {
//         account->failCount = 0; 
//         return 1; 
//     }

//     account->failCount++;
//     if (account->failCount >= 3) {
//         account->isLocked = 1;
//         printf("Nhap sai mat khau 3 lan. Tai khoan da bi khoa!\n");
//         return -3;
//     } 
//     printf("Sai mat khau! Ban con %d lan thu.\n", 3 - account->failCount);
//     return -1;  
// }

int Login(char mssv[], char ps[], Account list[], int accountCount) {    
    int index = -1;
    for (int i = 0; i < accountCount; i++) {
        if (strcmp(mssv, list[i].studentid) == 0) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("MSSV khong ton tai!\n");
        return -2;
    }
    if (list[index].isLocked == 1) {
        printf("Tai khoan nay da bi khoa!\n");
        return -3; 
    }

    list[index].failCount = 0;

    int result = checkPassword(ps, list, index);
    if (result == 1) return index;
    if (result == -1) return -1;   
    if (result == -3) return -3;
    return -1; 
}

void changePassword(Account *currentAcc) {
        char oldPass[20], newPass[20], confirmPass[20];
        printf("\n--- DOI MAT KHAU ---\n");
        while(1) {
            printf("Nhap mat khau cu: ");
            scanf(" %[^\n]", oldPass);

        if (strcmp(oldPass, currentAcc->password) != 0) {
            printf(">> Loi: Mat khau cu khong chinh xac!\n");
        } else {
        printf(">> Mat khau cu chinh xac!\n");
        break;
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
        while(1){
        printf("Nhap mat khau moi: ");
        scanf(" %[^\n]", newPass);
        printf("Xac nhan mat khau moi: ");
        scanf(" %[^\n]", confirmPass);

        if (strcmp(newPass, confirmPass) != 0) {
           printf(">> Loi: Mat khau moi va xac nhan khong khop!\n");
        } 
        else{
        printf(">> Mat khau moi va xac nhan khop!\n");
        break;
        }
    }
        if(strcmp(newPass, confirmPass) == 0) {
            strcpy(currentAcc->password, newPass);
            printf(">> Thanh cong: Da thay doi mat khau!\n");
        }
        else if(strlen(newPass) == 0  || strlen(confirmPass) == 0) {
        printf("ban co muon giu lai mat khau cu khong? (y/n): ");
        char choice;
            scanf(" %c", &choice);
            if(choice == 'y' || choice == 'Y') {
                printf(">> Mat khau van duoc giu nguyen!\n");
            }else if(choice == 'n' || choice == 'N') {
                printf(">> Mat khau van duoc giu nguyen!\n");
            }
        }
    }


    // hàm gửi yêu cầu mở tài khoản cho BCN