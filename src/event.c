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
void generateEventId(char *dest, int currentCount) {
    sprintf(dest, "EV%06d", currentCount + 1);
}

void createEvent(Event events[], int *count) {
    if (*count >= MAX_EVENTS) {
        printf("He thong day, khong the tao them su kien!\n");
        return;
    }

    Event newEv;
    generateEventId(newEv.eventId, *count); 
    
    printf("Nhap ten su kien: ");
    scanf(" %[^\n]", newEv.name);
    
    printf("Nhap mo ta su kien: ");
    scanf(" %[^\n]", newEv.description);
    
    printf("Nhap dia diem su kien: ");
    scanf(" %[^\n]", newEv.location);
    
    while (1) {
        printf("Nhap ngay bat dau (YYYY-MM-DD): ");
        scanf(" %[^\n]", newEv.startDate);
        printf("Nhap ngay ket thuc (YYYY-MM-DD): ");
        scanf(" %[^\n]", newEv.endDate);

        if (strcmp(newEv.endDate, newEv.startDate) >= 0) {
            break;
        } else {
            printf(">> Loi: Ngay ket thuc phai sau hoac bang ngay bat dau! Vui long nhap lai.\n");
        }
    }
    
    newEv.status = 0;
    newEv.staffCount = 0;
    
    events[*count] = newEv;
    (*count)++;
    saveEvents(events, *count);
    printf(">> Thanh cong: Da tao su kien %s\n", newEv.eventId);
}

void editEvent(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;

    printf("\n--- SUA THONG TIN SU KIEN ---\n");
    printf("Nhap ma su kien can sua (VD: EV000001): ");
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
        printf(">> Loi: Khong the sua su kien da ket thuc!\n");
        return;
    }

    if (events[foundIndex].status == 1) {
        char confirm;
        printf("!!! CANH BAO: Su kien nay dang DIEN RA. Ban co chac chan muon sua? (y/n): ");
        scanf(" %c", &confirm);
        if (confirm != 'y' && confirm != 'Y') {
            printf(">> Da huy thao tac sua.\n");
            return;
        }
    }

    printf("\nThong tin hien tai cua %s:\n", events[foundIndex].eventId);
    printf("1. Ten: %s\n", events[foundIndex].name);
    printf("2. Mo ta: %s\n", events[foundIndex].description);
    printf("3. Dia diem: %s\n", events[foundIndex].location);
    printf("4. Ngay bat dau: %s\n", events[foundIndex].startDate);
    printf("5. Ngay ket thuc: %s\n", events[foundIndex].endDate);

    
    printf("\nNhap ten moi: ");
    scanf(" %[^\n]", events[foundIndex].name);
    printf("Nhap mo ta moi: ");
    scanf(" %[^\n]", events[foundIndex].description);
    printf("Nhap dia diem moi: ");
    scanf(" %[^\n]", events[foundIndex].location);
    
    while (1) {
        printf("Nhap ngay bat dau moi (YYYY-MM-DD): ");
        scanf(" %[^\n]", events[foundIndex].startDate);
        printf("Nhap ngay ket thuc moi (YYYY-MM-DD): ");
        scanf(" %[^\n]", events[foundIndex].endDate);

        if (strcmp(events[foundIndex].endDate, events[foundIndex].startDate) >= 0) {
            break;
        } else {
            printf(">> Loi: Ngay ket thuc phai sau ngay bat dau!\n");
        }
    }

    printf(">> Thanh cong: Da cap nhat thong tin su kien %s.\n", searchId);
	saveEvents(events, count);
}

void updateEventStatus(Event events[], int count) {
    char searchId[10];
    int foundIndex = -1;

    printf("\n--- CAP NHAT TRANG THAI SU KIEN ---\n");
    printf("Nhap ma su kien (VD: EV000001): ");
    scanf(" %[^\n]", searchId);

    for (int i = 0; i < count; i++) {
        if (strcmp(events[i].eventId, searchId) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        printf(">> Loi: Khong tim thay su kien %s!\n", searchId);
        return;
    }

    int currentStatus = events[foundIndex].status;
    printf("Trang thai hien tai: ");
    if (currentStatus == 0) printf("Chua bat dau\n");
    else if (currentStatus == 1) printf("Dang dien ra\n");
    else printf("Ket thuc\n");

    if (currentStatus == 2) {
        printf(">> Loi: Su kien da KET THUC, khong the thay doi trang thai nua!\n");
        return;
    }

    if (currentStatus == 0) {
        char confirm;
        printf("Ban muon chuyen sang [Dang dien ra]? (y/n): ");
        scanf(" %c", &confirm);
        
        if (confirm == 'y' || confirm == 'Y') {
            if (events[foundIndex].staffCount == 0) {
                char force;
                printf("!!! CANH BAO: Su kien chua co nhan su nao. Van tiep tuc? (y/n): "); 
                scanf(" %c", &force);
                if (force != 'y' && force != 'Y') return;
            }
            events[foundIndex].status = 1;
            printf(">> Thanh cong: Su kien dang trong trang thai DIEN RA.\n");
        }
    } 
    else if (currentStatus == 1) {
        char confirm;
        printf("Ban muon chuyen sang [Ket thuc]? (y/n): ");
        scanf(" %c", &confirm);
        
        if (confirm == 'y' || confirm == 'Y') {
            events[foundIndex].status = 2;
            printf(">> Thanh cong: Su kien da KET THUC.\n");
        }
    }
	saveEvents(events, count);
}

void deleteEvent(Event events[], int *count) {
    char searchId[10];
    int foundIndex = -1;
    printf("\n--- XOA SU KIEN ---\n");
    printf("Nhap ma su kien can xoa (VD: EV000001): ");
    scanf(" %[^\n]", searchId);
    for (int i = 0; i < *count; i++) {
        if (strcmp(events[i].eventId, searchId) == 0) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1) {
        printf(">> Loi: Khong tim thay su kien co ma %s!\n", searchId);
        return;
    }
    printf("Ten su kien: %s\n", events[foundIndex].name);
    printf("So nhan su dang co trong su kien: %d\n", events[foundIndex].staffCount);
    if (events[foundIndex].status == 1) {
        printf(">> Loi: Khong the xoa su kien dang dien ra!\n"); 
        return;
    }
    char confirm1;
    printf("!!! CANH BAO: Ban co chac chan muon xoa su kien nay khong? (y/n): ");
    scanf(" %c", &confirm1);
    if (confirm1 != 'y' && confirm1 != 'Y') {
        printf(">> Da huy thao tac xoa.\n");
        return;
    }
    char confirm2;
    printf("!!! XAC NHAN LAN 2: Hanh dong nay se xoa vinh vien su kien va toan bo nhan su. Tiep tuc? (y/n): ");
    scanf(" %c", &confirm2);
    if (confirm2 != 'y' && confirm2 != 'Y') {
        printf(">> Da huy thao tac xoa.\n");
        return;
    }

    for (int i = foundIndex; i < *count - 1; i++) {
        events[i] = events[i + 1];
    }
    (*count)--;
    printf(">> Thanh cong: Da xoa su kien %s.\n", searchId);
    saveEvents(events, *count);
}

void displayAllEvents(Event events[], int count) {
    if (count == 0) {
        printf(">> Thong bao: Danh sach su kien dang trong.\n");
        return;
    }
    int filter;
    printf("\n--- LOC DANH SACH SU KIEN ---\n");
    printf("1. Tat ca\n");
    printf("2. Chua bat dau\n");
    printf("3. Dang dien ra\n");
    printf("4. Ket thuc\n");
    printf("Chon kieu loc: ");
    scanf("%d", &filter);
    int targetStatus = filter - 2; 

    printf("\n%-10s | %-20s | %-12s | %-12s | %-15s | %-5s | %-15s\n", 
           "Ma ID", "Ten Su Kien", "Bat dau", "Ket thuc", "Dia diem", "NS", "Trang thai");
    printf("------------------------------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (filter == 1 || events[i].status == targetStatus) {
            char statusStr[20];
            if (events[i].status == 0) {
            	strcpy(statusStr, "Chua bat dau");
			}else if (events[i].status == 1) {
				strcpy(statusStr, "Dang dien ra");
			}
            else {
            	strcpy(statusStr, "Ket thuc");
			}
            printf("%-10s | %-20s | %-12s | %-12s | %-15s | %-5d | %-15s\n", 
                   events[i].eventId, 
                   events[i].name, 
                   events[i].startDate, 
                   events[i].endDate, 
                   events[i].location, 
                   events[i].staffCount, 
                   statusStr);
            found = 1;
        }
    }

    if (!found) {
        printf(">> Khong co su kien nao phu hop voi bo loc.\n");
    }
    printf("------------------------------------------------------------------------------------------------------------\n");
}

void viewMemberProfile(Account *currentAcc) {
    printf("\n=========================================\n");
    printf("           THONG TIN CA NHAN             \n");
    printf("=========================================\n");
    //printf("%-12s: %s\n", "Ho ten", currentAcc->username);
    printf("%-12s: %s\n", "MSSV", currentAcc->studentid);
    // printf("%-12s: %s\n", "Email", currentAcc->email);
    // printf("%-12s: %s\n", "SDT", currentAcc->phone);
    // printf("%-12s: %s\n", "Ban", currentAcc->dept);
    printf("%-12s: %s\n", "Chuc vu", (currentAcc->role >= 1) ? "Ban Chu Nhiem (BCN)" : "Thanh vien");
    printf("=========================================\n");
    while (getchar() != '\n'); 
    getchar();
}

