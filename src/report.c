#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/event.h"
#include "../includes/report.h"


int search_events(Event list[], int countEvent, char eIdorName[])
{
    int Index = -1;

    for (int i = 0; i < countEvent; i++)
    {
        // ĐÃ SỬA: Chỉ so sánh eId (cả chuỗi) chứ không dùng eId[i]
        if (strcmp(eIdorName, list[i].eventId) == 0 
            || strcmp(eIdorName, list[i].name) == 0 
            || strcmp(eIdorName, toupper(list[i].name)) == 0 
            || strcmp(eIdorName, toupper(list[i].eventId)) == 0)
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
    }   
    
    return Index;
}


void event_detail(Event list[], int countEvent)
{
    char eId[20];
    printf("Nhap ma su kien can xem chi tiet (VD: EV000001) hoac ten su kien: ");
    scanf(" %[^\n]", eId);

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
    }

    printf("|=======================================|\n");
    printf("|     DANH SACH NHAN SU CUA SU KIEN     |\n");
    printf("|=======================================|\n");
        
    if (list[Index].staffCount == 0)
        {
            printf(">> Thong bao: Su kien chua co nhan su nao!\n");
            return;
        } else
            {
                for (int i = 0; i < list[Index].staffCount; i++)
                {
                    printf(" Ho va Ten: %s\n", list[Index].staffList[i].studentName);

                    printf(" Ma so sinh vien: %s\n", list[Index].staffList[i].studentId);

                    printf(" Vai tro: ");
                    // ĐÃ SỬA BUG LOGIC: Dùng chuỗi else if liên hoàn
                    if (list[Index].staffList[i].role == 0)
                        {
                            printf("BCN\n");
                        } else if (list[Index].staffList[i].role == 1)
                            {
                                printf("Member\n");
                            } else if (list[Index].staffList[i].role == 2)
                                {
                                    printf("Support\n");
                                } else 
                                    {
                                        printf("Chua co vai tro\n");
                                    }

                    printf(" Nhiem vu: ");
                    if (strlen(list[Index].staffList[i].description) == 0)
                        {
                            printf("Chua co nhiem vu\n");
                        } else
                            {
                                printf("%s\n", list[Index].staffList[i].description);
                            }
                }
            }  
} 