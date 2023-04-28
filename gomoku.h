#ifndef _GOMOKU_
#define _GOMOKU_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
//五子棋棋盘边长
#define N 10
//断言函数宏定义，flag为假时返回错误信息，为真时不操作
#define ASSERT(flag,msg) ((flag)?NULL:(fprintf(stdout,(msg)),exit(EXIT_FAILURE)))
//棋盘初始化函数
void gomokuInit(char gomoku[N][N]);
//棋盘渲染函数
void gomokuShow(char gomoku[N][N]);
//下了一步棋后判断是否胜利
int checkWin(int x, int y, char gomoku[N][N], char piece_type);
#endif