// Code hàm gán việc cho thành viên, hàm xem danh sách của thành viên
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

void toUpperCaseStr(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32;
        }
    }
}

void addStaffToEvent(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;

    printf("\n--- THEM NHAN SU VAO SU KIEN ---\n");
    printf("Nhap ma su kien (VD: EV000001): ");
    scanf(" %[^\n]", searchId);

    for (int i = 0; i < count; i++) {
        if (strcmp(events[i].eventId, searchId) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf(">> Loi: Khong tim thay su kien co ma %s!\n", searchId);
        return;
    }

    if (events[foundIndex].status == 2) {
        printf(">> Loi: Su kien da KET THUC, khong the them nhan su!\n");
        return;
    }

    if (events[foundIndex].staffCount >= 30) {
        printf(">> Loi: Su kien da dat toi da 30 nhan su!\n");
        return;
    }

    char mssvInput[50];
    printf("Nhap MSSV nhan su can them: ");
    scanf(" %[^\n]", mssvInput);
    
    toUpperCaseStr(mssvInput);

    for (int i = 0; i < events[foundIndex].staffCount; i++) {
        if (strcmp(events[foundIndex].staffList[i].studentId, mssvInput) == 0) {
            printf(">> Loi: Nhan su %s da ton tai trong su kien!\n", mssvInput);
            return;
        }
    }

    int role;
    printf("Nhap vai tro (0 = Leader, 1 = Member, 2 = Support): ");
    scanf("%d", &role);

    char desc[100];
    printf("Nhap mo ta nhiem vu: ");
    scanf(" %[^\n]", desc);

    int sCount = events[foundIndex].staffCount;
    strcpy(events[foundIndex].staffList[sCount].studentId, mssvInput);
    events[foundIndex].staffList[sCount].role = role;
    strcpy(events[foundIndex].staffList[sCount].description, desc);

    events[foundIndex].staffCount++;
    printf(">> Thanh cong: Da them nhan su %s vao su kien %s.\n", mssvInput, searchId);
    saveEvents(events, count);
}

void editStaffRole(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;

    printf("\n--- SUA THONG TIN NHAN SU TRONG SU KIEN ---\n");
    printf("Nhap ma su kien (VD: EV000001): ");
    scanf(" %[^\n]", searchId);

    for (int i = 0; i < count; i++) {
        if (strcmp(events[i].eventId, searchId) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf(">> Loi: Khong tim thay su kien co ma %s!\n", searchId);
        return;
    }

    if (events[foundIndex].status == 1) {
        printf(">> Loi: Khong the sua nhan su khi su kien dang dien ra!\n");
        return;
    }

    if (events[foundIndex].staffCount == 0) {
        printf(">> Loi: Su kien chua co nhan su nao!\n");
        return;
    }

    char mssvInput[50];
    int staffIndex = -1;

    printf("Nhap MSSV nhan su can sua: ");
    scanf(" %[^\n]", mssvInput);
    toUpperCaseStr(mssvInput);

    for (int i = 0; i < events[foundIndex].staffCount; i++) {
        if (strcmp(events[foundIndex].staffList[i].studentId, mssvInput) == 0) {
            staffIndex = i;
            break;
        }
    }

    if (staffIndex == -1) {
        printf(">> Loi: Khong tim thay nhan su %s trong su kien!\n", mssvInput);
        return;
    }

    printf("Nhap vai tro moi (0 = Leader, 1 = Member, 2 = Support): ");
    scanf("%d", &events[foundIndex].staffList[staffIndex].role);

    printf("Nhap mo ta nhiem vu moi: ");
    scanf(" %[^\n]", events[foundIndex].staffList[staffIndex].description);

    printf(">> Thanh cong: Da cap nhat nhan su %s trong su kien %s.\n", mssvInput, searchId);
    saveEvents(events, count);
}

void removeStaffFromEvent(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;

    printf("\n--- XOA NHAN SU KHOI SU KIEN ---\n");
    printf("Nhap ma su kien (VD: EV000001): ");
    scanf(" %[^\n]", searchId);

    for (int i = 0; i < count; i++) {
        if (strcmp(events[i].eventId, searchId) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf(">> Loi: Khong tim thay su kien co ma %s!\n", searchId);
        return;
    }

    if (events[foundIndex].status == 1) {
        printf(">> Loi: Khong the xoa nhan su khi su kien dang dien ra!\n");
        return;
    }

    if (events[foundIndex].staffCount == 0) {
        printf(">> Loi: Su kien chua co nhan su nao!\n");
        return;
    }

    printf("Danh sach nhan su hien tai:\n");
    for (int i = 0; i < events[foundIndex].staffCount; i++) {
        printf("- MSSV: %s | Vai tro: %d | Nhiem vu: %s\n", 
               events[foundIndex].staffList[i].studentId, 
               events[foundIndex].staffList[i].role,
               events[foundIndex].staffList[i].description);
    }

    char mssvInput[50];
    int staffIndex = -1;

    printf("Nhap MSSV nhan su can xoa: ");
    scanf(" %[^\n]", mssvInput);
    toUpperCaseStr(mssvInput);

    for (int i = 0; i < events[foundIndex].staffCount; i++) {
        if (strcmp(events[foundIndex].staffList[i].studentId, mssvInput) == 0) {
            staffIndex = i;
            break;
        }
    }

    if (staffIndex == -1) {
        printf(">> Loi: Khong tim thay nhan su %s trong su kien!\n", mssvInput);
        return;
    }

    char confirm;
    printf("Ban co chac chan muon xoa nhan su %s khoi su kien nay? (y/n): ", mssvInput);
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        for (int i = staffIndex; i < events[foundIndex].staffCount - 1; i++) {
            events[foundIndex].staffList[i] = events[foundIndex].staffList[i + 1];
        }
        events[foundIndex].staffCount--;
        printf(">> Thanh cong: Da xoa nhan su %s khoi su kien %s.\n", mssvInput, searchId);
    } else {
        printf(">> Da huy thao tac xoa.\n");
    }
    saveEvents(events, count);
}

