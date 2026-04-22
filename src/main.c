//  Điểm vào của chương trình, chứa hàm main() và menu tổng.
//  File này chỉ dùng để gọi hàm, KHÔNG chứa logic xử lý dài.
#include <stdio.h>

int main(){
    int choice;
    printf("=== He Thong Quan Ly Su Kien ===\n");
    printf("1. Dang Nhap\n");
    printf("2. Thoát\n");
    scanf("%d", &choice);

    switch(choice){
        case 1:
            // Gọi hàm đăng nhập
            printf("Dang Nhap chua duoc ho tro.\n");
            break;
        case 2:
            printf("Thoat chuong trinh.\n");
            break;
        default:
            printf("Lua chon khong hop le. Vui long thu lai.\n");
    }


    /*
        vào menu đăng nhập, nếu đăng nhập thành công thì sẽ vào menu chính của hệ thống, nếu không sẽ quay lại menu đăng nhập.
    */
}