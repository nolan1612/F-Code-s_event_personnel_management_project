#ifndef REQUEST_H
#define REQUEST_H

#include "auth.h"

#define MAX_REQUESTS 500

typedef struct {
    char studentid[10];
    char reason[200];
    int status; // 0: chờ | 1: duyệt | 2: từ chối
} Request;

int loadRequests(Request list[]);
void saveRequests(Request list[], int count);
void sendUnlockRequest(Account *currentAcc);
void viewUnlockRequests(Account list[], int accountCount);

#endif