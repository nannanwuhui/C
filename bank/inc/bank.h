#ifndef _BANK_H
#define _BANK_H
#include <sys/types.h>
#define KEY_REQUEST 0x12345678
#define KEY_RESPOND 0x87654321
#define TYPE_OPEN     8001
#define TYPE_CLOSE    8002
#define TYPE_SAVE     8003
#define TYPE_WITHDRAW 8004//取现
#define TYPE_QUERY    8005
#define TYPE_TRANSFER 8006
typedef struct tag_Account{
    int id;
    char name[256];
    char passwd[9];
    double balance;//余额
}ACCOUNT;
typedef struct tag_OpenRequest{
    long type;
    pid_t pid;
    char name[256];
    char passwd[9];
    double balance;
}OPEN_REQUEST;
typedef struct tag_OpenRespond{
    long type;
    char error[512];
    int  id;
}OPEN_RESPOND;
typedef struct tag_QueryRequest{
    long type;
    pid_t pid;
    int id;
    char name[256];
    char passwd[9];
}QUERY_REQUEST;
typedef struct tag_QueryRespond{
    long type;
    char error[512];
    double balance;
}QUERY_RESPOND;

#endif//_BANK_h
