#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/event.h"
#include "../includes/report.h"


int eventSearch(Event list[], int countEvent, char eIdorName[])
{   
    int Index = -1;

    for (int i = 0; i < countEvent; i++)
    {
        if (strcmp(list[i].eventId, eIdorName) == 0 || strcasecmp(list[i].name, eIdorName) == 0)
        {
            Index = i;

            printf("The event code is: %s\n", list[i].eventId);
            printf("The event name is: %s\n", list[i].name);

        if (list[i].status == 0)
        {
            printf("Event Status: Not Started\n");
        } else if (list[i].status == 1)
            {
                printf("Event Status: Ongoing\n");
            } else if (list[i].status == 2)
                {
                    printf("Event Status: Completed\n");
                } else 
                    {
                        printf("Event Status: Unknown\n");
                    }
            return Index;
        }
    }

    if (Index == -1)
    {
        printf("The event you are looking for does not exist!\n");
    }   
    
    return Index;
}


void eventDetail(Event list[], int countEvent)
{
    char eId[20];
    printf("Enter the event code you want to view details for (e.g., EV000001) or the event name: ");
    scanf(" %[^\n]", eId);



    int Index = eventSearch(list, countEvent, eId);

    if (Index != -1)
    {
        printf("|===============================|\n");
        printf("|       EVENT DETAILS       |\n");
        printf("|===============================|\n");

        printf("\n|===============================================================|\n");
        printf("Event Code                   :%s\n", list[Index].eventId);
        printf("Event Name                   :%s\n", list[Index].name);
        printf("Event Description            :%s\n", list[Index].description);
        printf("Event Location               :%s\n", list[Index].location);
        printf("Event Start Date             :%s\n", list[Index].startDate);
        printf("Event End Date               :%s\n", list[Index].endDate);

        if (list[Index].status == 0)
        {
            printf("Event Status                 :Not Started\n");
        } else if (list[Index].status == 1)
            {
                printf("Event Status                 :Ongoing\n");
            } else if (list[Index].status == 2)
                {
                    printf("Event Status                 :Completed\n");
                } else 
                    {
                        printf("Event Status                 :Unknown\n");
                    }

        printf("|=================================================================|\n");
    }

    printf("|=======================================|\n");
    printf("|     EVENT PARTICIPANTS LIST           |\n");
    printf("|=======================================|\n");
        
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
  