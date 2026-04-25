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


// int checkPassword(char ps[], Account list[], int index) {
//     do{
//         if (strcmp(ps, list[index].password) == 0) {
//             list[index].failCount = 0; 
//             return 1;
//         } else {
//             list[index].failCount++;
            
//             if (list[index].failCount >= 3) {
//                 printf("Nhap sai mat khau 3 lan. Khoa tai khoan va thoat chuong trinh!\n");
//                 list[index].isLocked = 1;
//                 return -1;
//             } else {
//                 printf("Sai mat khau! Ban con %d lan thu.\n", 3 - list[index].failCount);
//                 printf("Nhap lai mat khau: ");
//                 scanf(" %[^\n]", ps);
//             }
//         }
//     } while (list[index].failCount < 3);
// }
int checkPassword(char ps[], Account *account) {
    if (strcmp(ps, account->password) == 0) {
        account->failCount = 0; 
        return 1; 
    }

    account->failCount++;
    if (account->failCount >= 3) {
        account->isLocked = 1;
        printf("Nhap sai mat khau 3 lan. Tai khoan da bi khoa!\n");
        return -3;
    } 
    printf("Sai mat khau! Ban con %d lan thu.\n", 3 - account->failCount);
    return -1;  

    if (strcmp(ps, account->password) == 0) {
        account->failCount = 0; 
        return 1; 
    }

    account->failCount++;
    if (account->failCount >= 3) {
        account->isLocked = 1;
        printf("Nhap sai mat khau 3 lan. Tai khoan da bi khoa!\n");
        return -3;
    } 
    printf("Sai mat khau! Ban con %d lan thu.\n", 3 - account->failCount);
    return -1;  
}

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

    int result = checkPassword(ps, &list[index]);
    if (result == 1) return index;
    if (result == -1) return -1;   
    if (result == -3) return -3;
    return -1; 
}

void changePassword(Account *currentAcc) {
    char oldPass[20], newPass[20], confirmPass[20];
    int failCount = 0; 
    
    printf("\n--- DOI MAT KHAU ---\n");

    
    while(1) {
        printf("Nhap mat khau cu: ");
        scanf(" %[^\n]", oldPass);

      
        if (strcmp(oldPass, "0") == 0) {
            printf(">> Da huy doi mat khau. Quay lai menu...\n");
            return; 
        }

        if (strcmp(oldPass, currentAcc->password) != 0) {
            failCount++; 
            printf(">> Loi: Mat khau cu khong chinh xac!\n");
            printf(">> Hay thu lai. Ban con %d lan thu.\n", 3 - failCount);
            
            // Nếu sai từ 3 lần trở lên, tung phao cứu sinh
            if (failCount >= 3) {
                printf("\033[1;33m[Meo]\033[0m Neu ban da quen mat khau, hay go '0' de thoat ra va nho Admin reset nhe!\n");
            }
        } else {
            break; 
        }
    }


    while(1) {
        printf("Nhap mat khau moi (Go '0' de huy): "); 
        scanf(" %[^\n]", newPass);
        
        if (strcmp(newPass, "0") == 0) {
            printf(">> Da huy doi mat khau. Quay lai menu...\n");
            return; 
        }

        if (strcmp(newPass, currentAcc->password) == 0) {
            printf(">> Loi: Mat khau moi khong duoc giong mat khau hien tai!\n");
            continue; 
        }

        printf("Xac nhan mat khau moi: ");
        scanf(" %[^\n]", confirmPass);

        if (strcmp(confirmPass, "0") == 0) {
            printf(">> Da huy doi mat khau. Quay lai menu...\n");
            return; 
        }

        if (strcmp(newPass, confirmPass) != 0) {
           printf(">> Loi: Mat khau moi va xac nhan khong khop! Hay nhap lai.\n");
        } else {
            strcpy(currentAcc->password, newPass);
            printf("\033[1;32m>> Thanh cong: Da thay doi mat khau!\033[0m\n");
            break; 
        }
    }
}


int Logout(Account *currentAcc, Account list[], int accountCount) {
    printf("Xac nhan dang xuat? (y/n): ");
    char choice;
    scanf(" %c", &choice);
    if (choice == 'y' || choice == 'Y') {
        saveAccounts(list, accountCount);
        printf(">> Da dang xuat thanh cong. Hen gap lai %s!\n", currentAcc->studentid);
        return 1;
    } else {
        printf(">> Huy dang xuat.\n");
        return 0;
    }

}
