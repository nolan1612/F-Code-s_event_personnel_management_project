#include "../includes/auth.h"
#include "../includes/event.h"
#include "../includes/menu.h"
#include "../includes/fileio.h"
#include "../includes/report.h"
#include "../includes/staff.h"
#include "../includes/utils.h"
void AdminMenu() {
    printf("\n=========================================\n");
    printf("        BAN CHU NHIEM (ADMIN) MENU       \n");
    printf("=========================================\n");
    printf("1. Tao su kien moi\n");
    printf("2. Sua thong tin su kien\n");
    printf("3. Xoa su kien\n");
    printf("4. Cap nhat trang thai su kien\n");
    printf("5. Quan ly nhan su (Them/Sua/Xoa)\n");
    printf("6. Xem danh sach tat ca su kien\n");
    printf("7. Xem chi tiet mot su kien\n");
    printf("8. Tim kiem su kien\n");
    printf("9. Xem lich su tham gia cua thanh vien\n");
    printf("10. Doi mat khau\n");
    printf("0. Dang xuat\n");
    printf("=========================================\n");
}

void MemberMenu() {
    printf("\n=========================================\n");
    printf("             THANH VIEN MENU             \n");
    printf("=========================================\n");
    printf("1. Xem profile ca nhan\n");
    printf("2. Xem danh sach su kien dang tham gia\n");
    printf("3. Xem chi tiet su kien minh tham gia\n");
    printf("4. Xem lich su su kien da tham gia\n");
    printf("5. Doi mat khau\n");
    printf("0. Dang xuat\n");
    printf("=========================================\n");
}
void runAdminMenu(Account *currentAcc, Account list[], int accountCount, Event eventList[], int *eventCount) {
    int choice;
    do {
        AdminMenu();
        printf("Nhap lua chon cua ban (0-10): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            choice = -1;
        }

        switch(choice) {
            case 1: 
                createEvent(eventList, eventCount);
                break;
            case 2: 
                // 2. Sua thong tin su kien
                break;
            case 3: 
                // 3. Xoa su kien
                break;
            case 4: 
                // 4. Cap nhat trang thai su kien
                break;
            case 5: 
                // 5. Quan ly nhan su (Them/Sua/Xoa)
                break;
            case 6: 
                displayAllEvents(eventList, *eventCount);
                break;
            case 7: 
                // 7. Xem chi tiet mot su kien
                break;
            case 8: 
                // 8. Tim kiem su kien
                break;
            case 9: 
                // 9. Xem lich su tham gia cua thanh vien
                break;
            case 10: 
                changePassword(currentAcc);
                saveAccounts(list, accountCount);
                break;
            case 0: 
                printf("\n>> Da dang xuat khoi tai khoan\n"); 
                break;
            default: 
                printf(">> Loi: Lua chon khong hop le. Vui long nhap lai!\n");
        }
    } while (choice != 0); 
}
void runMemberMenu(Account *currentAcc, Account list[], int accountCount, Event eventList[], int eventCount) {
    int choice;
    do {
        MemberMenu();
        printf("Nhap lua chon cua ban (0-5): ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); 
            choice = -1;
        }

        switch(choice) {
            case 1: 
                viewMemberProfile(currentAcc);
                break;
            case 2: 
                // 2. Xem danh sach su kien dang tham gia
                break;
            case 3: 
                // 3. Xem chi tiet su kien minh tham gia
                break;
            case 4: 
                // 4. Xem lich su su kien da tham gia
                break;
            case 5: 
                changePassword(currentAcc);
                saveAccounts(list, accountCount);
                break;
            case 0: 
                printf("\n>> Da dang xuat khoi tai khoan\n"); 
                break;
            default: 
                printf(">> Loi: Lua chon khong hop le. Vui long nhap lai!\n");
        }
    } while (choice != 0); 
}