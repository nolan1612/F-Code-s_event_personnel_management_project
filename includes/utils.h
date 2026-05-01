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
int isLeapYear(int year);
int isValidDate(int year, int month, int day);
void inputValidFormatDate(char str[]);
int confirmAction( char message[]);
#endif