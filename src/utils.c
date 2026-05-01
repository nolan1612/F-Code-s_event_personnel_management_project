#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../includes/auth.h"
#include "../includes/event.h"
#include "../includes/menu.h"
#include "../includes/fileio.h"
#include "../includes/report.h"
#include "../includes/staff.h"
#include "../includes/utils.h"
void clearBuffer();
void trimNewLine(char str[]);
int validInput(int min, int max);
int containsIgnoreCase(char str[], char strSub[]);
int isLeapYear(int year);
int isValidDate(int year, int month, int day);
void inputValidFormatDate(char str[]);
int confirmAction( char message[]);
void clearBuffer() {
    while (getchar() != '\n');
}
void trimNewLine(char str[]){
    int range = strlen(str);
    if (range > 0 && str[range - 1] == '\n') {
        str[range - 1] = '\0';
    }
}
int validInput(int min, int max){
    int number;
    while(1){
        int check = scanf("%d", &number);
        if(check == 1){
            if(number >= min && number <= max){
                return number;
            }else{
                printf(">>Error: The number must be in %d to %d. Pls, try again: ", min, max);
            }
        }
        else{
            printf(">>Error: You just entered text! Please only enter numbers: ");
            clearBuffer();
        }
    }
}
int containsIgnoreCase(char str[], char strSub[]){
    int check = 0;
    int size1 = strlen(str);
    int size2 = strlen(strSub);
    for(int i = 0; i <= size1 - 1; i++){
       if(tolower(str[i]) == tolower(strSub[check])){
            if(check == size2 - 1){
                return 1;
            } 
            check++;
        }else{
            i -= check;
            check = 0;
        }
    }
    return 0;
}
int isLeapYear(int year){
    if(year % 400 == 0) return 1;
    else if(year % 4 == 0 && year % 100 != 0) return 1;
    return 0;
}

int isValidDate(int year, int month, int day){
    if(year < 2000 || year > 2100) return 0;
    if(month < 1 || month > 13) return 0;
    if(day < 1) return 0;

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year) == 1) {
        daysInMonth[2] = 29;
    }
    if (day > daysInMonth[month]) {
        return 0; 
    }
    return 1;
}
void inputValidFormatDate(char str[]){
    char buffer[100];
    char tempBuffer[100];
    int year, month, day;
    while(1){
        scanf(" %[^\n]", buffer);
        clearBuffer();
        strcpy(buffer, tempBuffer);
        char *token;
        int part[3];
        int cnt = 0;
        token = strtok(tempBuffer, "/");
        while(token != NULL && cnt < 3){
            part[cnt] = atoi(token);
            cnt++;
            token = strtok(NULL, "/");
        }
        if(cnt == 3){
            year = part[0];
            month = part[1];
            day = part[2];
            if(isValidDate(year, month, day)){
                strcpy(str,buffer);
                return;
            }else{
                printf(">> Error: It doesn't exist in reality today! Please re-enter (YYYY/MM/DD):");
            }
        } else {
          printf(">> Error: Invalid format! Please use YYYY/MM/DD (Ex: 2026/05/02): ");
        }
    }
}

int confirmAction( char message[]) {
    char choice;
    while (1) {
        printf("%s (Y/N): ", message);
        scanf(" %c", &choice);
        clearBuffer(); 
        choice = toupper(choice); 
        if (choice == 'Y') return 1;
        if (choice == 'N') return 0;
        printf(">> Error: Invalid input! Please enter Y or N.\n");
    }
}
