//  Định nghĩa struct StaffEntry (MSSV, Công việc, Đánh giá...)
#ifndef STAFF_H
#define STAFF_H

#include "event.h"

void toUpperCaseStr(char str[]);
void addStaffToEvent(Event events[], int count);
void editStaffRole(Event events[], int count);
void removeStaffFromEvent(Event events[], int count);
void viewMemberHistory(Event events[], int count);

#endif
