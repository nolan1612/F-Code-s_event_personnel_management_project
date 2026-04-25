// Chứa thuật toán sắp xếp, lọc tìm kiếm, xuất file .txt
#include "report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data/event.dat"
#include "../includes/event.h"



int search_events(Event list[], int countEvent, char eId[])
{   
    int Index = -1;

    for (int i = 0; i < countEvent; i++)
    {
        if ((strcmp(eId[i], list[i].eventId) == 0) || (strcmp(eId[i], toupper(list[i].eventId)) == 0))
        {
            Index = i;

            printf("Ma su kien la: %s\n", list[i].eventId);
            printf("Ten su kien la: %s\n", list[i].name);
            printf("Trang thai su kien: %d\n", list[i].status);

            return Index;
        }
    }

    if (Index == -1)
    {
        printf("Ma su kien nay khong ton tai!\n");
        return Index;
    }   
}


void event_detail(Event list[], int countEvent, char eId[], StaffEntry staffList[], int countAccount)
{
    int Index = search_events(list, countEvent, eId);

    if (Index != -1)
    {
        printf("|===============================|\n");
        printf("|       THONG TIN SU KIEN       |\n");
        printf("|===============================|\n");

        printf("\n|===============================================================|\n");
        printf("Ma su kien                   :%s\n", list[Index].eventId);
        printf("Ten su kien                  :%s\n", list[Index].name);
        printf("Mo ta su kien                :%s\n", list[Index].description);
        printf("Dia diem su kien             :%s\n", list[Index].location);
        printf("Ngay bat dau su kien         :%s\n", list[Index].startDate);
        printf("Ngay ket thuc su kien        :%s\n", list[Index].endDate);
        printf("Trang thai su kien           :%d\n", list[Index].status);
        printf("|=================================================================|\n");

        printf("|=======================================|\n");
        printf("|     DANH SACH NHAN SU CUA SU KIEN     |\n");
        printf("|=======================================|\n");

        for (int i = 0; i < countAccount; i++)
        {
            printf(" Ho va Ten: %s\n", staffList[i].studentName);
            printf(" Ma so sinh vien: %s\n", staffList[i].studentId);

            printf(" Vai tro: ");
                if (staffList[i].role == 0)
                {
                    printf("BCN\n");
                } 
                if (staffList[i].role == 1)
                {
                    printf("Member\n");
                } 
                if (staffList[i].role == 2)
                {
                    printf("Support\n");
                } else 
                    {
                        printf("Chua co vai tro\n");
                    }
            
            printf(" Nhiem vu: ");
            if (staffList[i].description == NULL)
            {
                printf("Chua co nhiem vu\n");
            }
            printf("%s\n", staffList[i].description);
        } 
    }
}