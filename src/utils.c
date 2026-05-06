#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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
int confirmAction( char message[]);
int isLeapYear(int year);
int isValidDateNum(int year, int month, int day);
int isValidDateStr(const char* date);
int getDaysDifference(const char* start, const char* end);
void inputValidFormatDate(char str[]);
void isValidEmail(char email[]);
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

int isValidDateNum(int year, int month, int day){
    if(year < 1900 || year > 2100) return 0; 
    if(month < 1 || month > 12) return 0; 
    if(day < 1 || day > 31) return 0;

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (isLeapYear(year)) {
        daysInMonth[2] = 29;
    }
    if (day > daysInMonth[month]) {
        return 0; 
    }
    return 1;
}
int isValidDateStr(const char* date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) return 0;
    
    return isValidDateNum(year, month, day);
}
int getDaysDifference(const char* start, const char* end) {
    struct tm tm_start = {0};
    struct tm tm_end = {0};

    sscanf(start, "%d-%d-%d", &tm_start.tm_year, &tm_start.tm_mon, &tm_start.tm_mday);
    sscanf(end, "%d-%d-%d", &tm_end.tm_year, &tm_end.tm_mon, &tm_end.tm_mday);

    tm_start.tm_year -= 1900;
    tm_start.tm_mon -= 1;
    tm_end.tm_year -= 1900;
    tm_end.tm_mon -= 1;

    time_t time_start = mktime(&tm_start);
    time_t time_end = mktime(&tm_end);

    long long seconds = (long long)difftime(time_end, time_start);
    return (int)(seconds / (60 * 60 * 24)); 
}
void inputValidFormatDate(char str[]){
    char buffer[100];
    char tempBuffer[100];
    int year, month, day;
    while(1){
        scanf(" %[^\n]", buffer);
        clearBuffer();
        strcpy(tempBuffer, buffer); 

        char *token;
        int part[3];
        int cnt = 0;
        
        token = strtok(tempBuffer, "/-");
        while(token != NULL && cnt < 3){
            part[cnt] = atoi(token);
            cnt++;
            token = strtok(NULL, "/-");
        }
        
        if(cnt == 3){
            year = part[0];
            month = part[1];
            day = part[2];
            
            if(isValidDateNum(year, month, day)){
                sprintf(str, "%04d-%02d-%02d", year, month, day);
                return;
            } else {
                printf(">> Error: It doesn't exist in reality today! Please re-enter: ");
            }
        } else {
            printf(">> Error: Invalid format! Please use YYYY-MM-DD or YYYY/MM/DD: ");
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
int isValidEmail(char email[]){
    if(email == NULL || strlen(email) == 0) return 0;
    //kiem tra dau cach 
    for(int i = 0; i <= strlen(email) - 1; i++){
        if(isspace(email[i])) return 0;
    }
    if(email[0] == '@') return 0;

    char copy[101];
    strncpy(copy, email, sizeof(copy) - 1);
    copy[sizeof(copy) - 1] = '\0';

    char *part1 = strtok(copy, "@");
    char *part2 = strtok(NULL, "@");
    char *extra = strtok(NULL, "@");

    if(part1 == NULL || part2 == NULL) return 0;
    if(extra != NULL) return 0;

    char part2cpy[101];
    strncpy(part2cpy, part2, sizeof(part2cpy) - 1);
    part2cpy[sizeof(part2cpy) - 1] = '\0';

    char *token = strtok(part2cpy, ".");
    char *last = NULL;
    while (token != NULL) {
        last  = token;
        token = strtok(NULL, ".");
    }
  
    if (last == NULL || strlen(last) == 0) return 0;
    return 1;
}

