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
        if (stricmp(list[i].eventId, eIdorName) == 0 || strcasecmp(list[i].name, eIdorName) == 0)
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
    printf("Enter the event code you want to view details for (e.g., EV000001) or the event name:");
    scanf(" %[^\n]", eId);



    int Index = search_events(list, countEvent, eId);

    if (Index != -1)
    {
        printf("|===============================|\n");
        printf("|       EVENT INFORMATION       |\n");
        printf("|===============================|\n");

        printf("\n|=====================|===========================================|\n");
        printf("|\tEvent Code       \t|%s\n", list[Index].eventId);
        printf("|=======================|===========================================|\n");
        printf("|\tEvent Name       \t|%s\n", list[Index].name);
        printf("|=======================|===========================================|\n");
        printf("|\tEvent Description\t|%s\n", list[Index].description);
        printf("|=======================|===========================================|\n");
        printf("|\tEvent Location   \t|%s\n", list[Index].location);
        printf("|=======================|===========================================|\n");
        printf("|\tEvent Start Date \t|%s\n", list[Index].startDate);
        printf("|=======================|===========================================|\n");
        printf("|\tEvent End Date   \t|%s\n", list[Index].endDate);
        printf("|=======================|===========================================|\n");
        printf("|\tEvent Status     \t|%d\n", list[Index].status);
        printf("|=======================|===========================================|\n");
    }


    if (list[Index].staffCount == 0)
        {
            printf(">> Announcement: No staff have been assigned to this event yet!\n");
            return;
        } else
            {      

                printf("|=========================================|\n");
                printf("|       LIST OF STAFF FOR THE EVENT       |\n");
                printf("|=========================================|\n");

                for (int i = 0; i < list[Index].staffCount; i++)
                {   
        
                    printf("|\t\t%s\t\t", list[Index].staffList[i].studentName);

                    printf("|\t\t%s\n", list[Index].staffList[i].studentId);

                    printf("| Role: ");
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
                                        printf("Unassigned\n");
                                    }

                    printf("| Responsibilities: ");
                    if (strlen(list[Index].staffList[i].description) == 0)
                        {
                            printf("No responsibilities assigned\n");
                        } else
                            {
                                printf("%s\n", list[Index].staffList[i].description);
                            }
                }
            }  
}


void create_file(Event list[], int countEvent)
{
    FILE *fptr;
    fptr = fopen("report.txt", "w");
    if (fptr == NULL)
    {
        printf("Error creating report file!\n");
        return;
    }
    printf("search name of event you want to create report for: ");
    char eId[20];
    scanf(" %[^\n]", eId);

    int Index = search_events(list, countEvent, eId);

    if (Index != -1)
    {
        fprintf(fptr, "Event Code: %s\n", list[Index].eventId);
        fprintf(fptr, "Event Name: %s\n", list[Index].name);
        fprintf(fptr, "Event Description: %s\n", list[Index].description);
        fprintf(fptr, "Event Location: %s\n", list[Index].location);
        fprintf(fptr, "Event Start Date: %s\n", list[Index].startDate);
        fprintf(fptr, "Event End Date: %s\n", list[Index].endDate);
        fprintf(fptr, "Event Status: %d\n", list[Index].status);

        if (list[Index].staffCount == 0)
        {
            fprintf(fptr, "No staff have been assigned to this event yet!\n");
        } else
            {   
                printf("|=========================================|\n");
                printf("|       LIST OF STAFF FOR THE EVENT       |\n");
                printf("|=========================================|\n");
                for (int i = 0; i < list[Index].staffCount; i++)
                {   
                    fprintf(fptr, "Name: %s | Student ID: %s | Role: ", list[Index].staffList[i].studentName, list[Index].staffList[i].studentId);
                    if (list[Index].staffList[i].role == 0)
                        {
                            fprintf(fptr, "BCN\n");
                        } else if (list[Index].staffList[i].role == 1)
                            {
                                fprintf(fptr, "Member\n");
                            } else if (list[Index].staffList[i].role == 2)
                                {
                                    fprintf(fptr, "Support\n");
                                } else 
                                    {
                                        fprintf(fptr, "Unassigned\n");
                                    }

                    fprintf(fptr, "Responsibilities: ");
                    if (strlen(list[Index].staffList[i].description) == 0)
                        {
                            fprintf(fptr, "No responsibilities assigned\n");
                        } else
                            {
                                fprintf(fptr, "%s\n", list[Index].staffList[i].description);
                            }
                }
            }  
    } else
        {
            fprintf(fptr, "Event with the given ID or name does not exist!\n");
        }
    fclose(fptr);
}
