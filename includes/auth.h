//  Định nghĩa struct Account (MSSV, Mật khẩu, Quyền)
#ifndef AUTH_H
#define AUTH_H

#define MAX_ACCOUNTS 100

typedef struct {
    char studentid[10];
    char password[20];
    int role;
    int isLocked;
    int failCount;
} Account;

int checkPassword(char ps[], Account list[], int index);
int Login(char mssv[], char ps[], Account list[], int accountCount);
void changePassword(Account *currentAcc);

#endif