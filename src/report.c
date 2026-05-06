#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/event.h"
#include "../includes/report.h"


int eventSearch(Event list[], int countEvent, char eIdorName[])
{   
    int Index = -1;

    for (int i = 0; i < countEvent; i++)
    {
        if (stricmp(list[i].eventId, eIdorName) == 0 || strcasecmp(list[i].name, eIdorName) == 0)
        {
            Index = i;

            printf("The event code: %s\n", list[i].eventId);
            printf("The event name: %s\n", list[i].name);

            if (list[i].status == 0)
            {
                printf("the event status: Not Start\n");
            } else if (list[i].status == 1)
                    {
                        printf("the event status: Ongoing\n");
                    } else if (list[i].status == 2)
                            {
                                printf("the event status: Complete\n");
                            } else 
                                {
                                    printf("the event status: Unknown\n");
                                }

            return Index;
        }
    }

    if (Index == -1)
    {
        printf("The event code or name you entered does not exist!\n");
    }   
    
    return Index;
}


void eventDetail(Event list[], int countEvent)
{
    char eId[20];
    printf("Enter the event code you want to view details for (e.g., EV000001) or the event name:");
    scanf(" %[^\n]", eId);

    int Index = eventSearch(list, countEvent, eId);

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
        
        if (list[Index].status == 0)
            {
                printf("|\tEvent Status     \t|Not Started\n");
            } else if (list[Index].status == 1)
                {
                    printf("|\tEvent Status     \t|Ongoing\n");
                } else if (list[Index].status == 2)
                    {
                        printf("|\tEvent Status     \t|Completed\n");
                    } else 
                        {
                            printf("|\tEvent Status     \t|Unknown\n");
                        }

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
                printf("|Name                   |ID                     |Role                      |Responsibilities\n");  

                for (int i = 0; i < list[Index].staffCount; i++)
                {   
                    printf("|%s\t\t\t\t", list[Index].staffList[i].studentName);

                    printf("|%s\t\t\t\t", list[Index].staffList[i].studentId);

                    if (list[Index].staffList[i].role == 0)
                        {
                            printf("|BCN\t\t\t\t");
                        } else if (list[Index].staffList[i].role == 1)
                            {
                                printf("|Member\t\t\t\t");
                            } else if (list[Index].staffList[i].role == 2)
                                {
                                    printf("|Support\t\t\t\t");
                                } else 
                                    {
                                        printf("|Unassigned\t\t\t\t");
                                    }

                    if (strlen(list[Index].staffList[i].description) == 0)
                        {
                            printf("|No responsibilities assigned\n");
                        } else
                            {
                                printf("|%s\n", list[Index].staffList[i].description);
                            }
                }
            }  
}


void createFile(Event list[], int countEvent)
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

        if (list[Index].status == 0)
            {
                fprintf(fptr, "the event status: Not Start\n");
            } else if (list[Index].status == 1)
                    {
                        fprintf(fptr, "the event status: Ongoing\n");
                    } else if (list[Index].status == 2)
                            {
                                fprintf(fptr, "the event status: Complete\n");
                            } else 
                                {
                                    fprintf(fptr, "the event status: Unknown\n");
                                }

        if (list[Index].staffCount == 0)
        {
            fprintf(fptr, "No staff have been assigned to this event yet!\n");
        } else
            {   
                fprintf(fptr, "|=========================================|\n");
                fprintf(fptr, "|       LIST OF STAFF FOR THE EVENT       |\n");
                fprintf(fptr, "|=========================================|\n");
                fprintf(fptr, "|Name                   |ID                     |Role                      |Responsibilities\n");

                for (int i = 0; i < list[Index].staffCount; i++)
                {   

                    fprintf(fptr, "|%s\t\t\t\t", list[Index].staffList[i].studentName);

                    fprintf(fptr, "|%s\t\t\t\t", list[Index].staffList[i].studentId);

                    if (list[Index].staffList[i].role == 0)
                        {
                            fprintf(fptr, "|BCN\t\t\t\t");
                        } else if (list[Index].staffList[i].role == 1)
                            {
                                fprintf(fptr, "|Member\t\t\t\t");
                            } else if (list[Index].staffList[i].role == 2)
                                {
                                    fprintf(fptr, "|Support\t\t\t\t");
                                } else 
                                    {
                                        fprintf(fptr, "|Unassigned\t\t\t\t");
                                    }

                    if (strlen(list[Index].staffList[i].description) == 0)
                        {
                            fprintf(fptr, "|No responsibilities assigned\n");
                        } else
                            {
                                fprintf(fptr, "|%s\n", list[Index].staffList[i].description);
                            }
                }
            }  
    } else
        {
            fprintf(fptr, "Event with the given ID or name does not exist!\n");
        }
    fclose(fptr);
}
