#ifndef MENU_H
#define MENU_H

void AdminMenu();
void MemberMenu();
void runAdminMenu(Account *currentAcc, Account list[], int accountCount, Event eventList[], int *eventCount);
void runMemberMenu(Account *currentAcc, Account list[], int accountCount, Event eventList[], int eventCount);

#endif