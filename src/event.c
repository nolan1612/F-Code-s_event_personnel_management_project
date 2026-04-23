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

void createEvent(Event events[], int count) {
    if (count >= MAX_EVENTS) {
        printf("He thong day, khong the tao them su kien!\n");
        return;
    }

    Event newEv;
    generateEventId(newEv.eventId, count); 
    
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
    
    events[count] = newEv;
    count++;
    // them ham save io
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
	//Them ham save io
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
	// them ham luu
}