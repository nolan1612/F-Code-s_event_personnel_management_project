// Khai báo các hàm dùng chung
#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
#endif