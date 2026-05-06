#include <stdio.h>
#include <string.h>
#include "../includes/request.h"
#include "../includes/auth.h"
#include "../includes/utils.h"


int loadRequests(Request list[]) {
    FILE *f = fopen("data/request.dat", "rb");
    if (f == NULL) return 0;
    int count = 0;
    while (fread(&list[count], sizeof(Request), 1, f)) count++;
    fclose(f);
    return count;
}

void saveRequests(Request list[], int count) {
    FILE *f = fopen("data/request.dat", "wb");
    if (f == NULL) return;
    fwrite(list, sizeof(Request), count, f);
    fclose(f);
}

// ===================== MEMBER =====================
void sendUnlockRequest(Account *currentAcc) {
    if (currentAcc->isLocked == 0) {
        printf(">> Tai khoan cua ban khong bi khoa!\n");
        return;
    }

    // Kiểm tra đã gửi yêu cầu chưa
    Request list[MAX_REQUESTS];
    int count = loadRequests(list);
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].studentid, currentAcc->studentid) == 0 && list[i].status == 0) {
            printf(">> Ban da gui yeu cau truoc do, vui long cho BCN duyet!\n");
            return;
        }
    }

    char reason[200];
    printf("Nhap ly do yeu cau mo khoa: ");
    scanf(" %[^\n]", reason);
    clearBuffer();

    if (!confirmAction("Xac nhan gui yeu cau mo khoa?")) {
        printf(">> Da huy gui yeu cau.\n");
        return;
    }

    Request req;
    strcpy(req.studentid, currentAcc->studentid);
    strcpy(req.reason, reason);
    req.status = 0;

    list[count++] = req;
    saveRequests(list, count);
    printf(">> Da gui yeu cau mo khoa den BCN. Vui long cho duyet!\n");
}

// ===================== ADMIN =====================
void viewUnlockRequests(Account list[], int accountCount) {
    Request reqList[MAX_REQUESTS];
    int count = loadRequests(reqList);

    // Lọc và hiển thị danh sách chờ duyệt
    int pendingIndex[MAX_REQUESTS];
    int pendingCount = 0;

    printf("\n--- DANH SACH YEU CAU MO KHOA ---\n");
    for (int i = 0; i < count; i++) {
        if (reqList[i].status == 0) {
            printf("[%d] MSSV: %10s | Ly do: %s\n",
                pendingCount + 1,
                reqList[i].studentid,
                reqList[i].reason);
            pendingIndex[pendingCount++] = i;
        }
    }

    if (pendingCount == 0) {
        printf(">> Khong co yeu cau nao dang cho duyet.\n");
        return;
    }

    printf("\nNhap STT yeu cau muon xu ly (1 - %d): ", pendingCount);
    int choice = validInput(1, pendingCount);
    int idx = pendingIndex[choice - 1];

    printf("\nYeu cau cua MSSV: %s\n", reqList[idx].studentid);
    printf("Ly do: %s\n", reqList[idx].reason);

    if (confirmAction("Duyet yeu cau nay?")) {
        reqList[idx].status = 1;
        for (int i = 0; i < accountCount; i++) {
            if (strcmp(list[i].studentid, reqList[idx].studentid) == 0) {
                list[i].isLocked = 0;
                list[i].failCount = 0;
                printf(">> Da duyet va mo khoa tai khoan %s!\n", list[i].studentid);
                break;
            }
        }
    } else {
        reqList[idx].status = 2;
        printf(">> Da tu choi yeu cau cua %s!\n", reqList[idx].studentid);
    }

    saveRequests(reqList, count);
}