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