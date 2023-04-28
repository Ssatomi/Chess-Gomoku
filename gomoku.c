#include"gomoku.h"

void gomokuInit(char gomoku[N][N]){//棋盘初始化
    int i, j;
    char c_tmp = '_';
    for (i = 0; i < N; i++) {//全部位置初始化为'_'
        for (j = 0; j < N; j++) {
            gomoku[i][j] = c_tmp;
        }
    }
    gomoku[0][0] = 'G';
    for (i = 1; i < N; i++) {//棋盘第一行和第一列为数字
        c_tmp = i + '0';
        gomoku[0][i] = c_tmp;
        gomoku[i][0] = c_tmp;
    }
}

void gomokuShow(char gomoku[N][N]){//棋盘渲染
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%c ", gomoku[i][j]);
        }
        printf("\n");
    }
}

int checkWin(int x, int y, char gomoku[N][N], char piece_type){
    //x,y为当前下的棋子的位置
    //piece_type指示下的棋子是黑棋还是白棋
	int i, j, count = 0;
    //统计横向
	for(i = y + 1; i < N; i++)
		if(gomoku[x][i] == piece_type)
			count++;
		else break;
	for(i = y-1; i > 0; i--)
		if(gomoku[x][i] == piece_type)
			count++;
		else break;
	if(count >= 4) return 1;//胜利
	count=0;
    //统计纵向
	for(i = x + 1; i < N; i++)
		if(gomoku[i][y] == piece_type)
			count++;
		else break;
	for(i = x - 1; i > 0; i--)
		if(gomoku[i][y] == piece_type)
			count++;
		else break;
	if(count >= 4) return 1;//胜利
	count=0;
    //统计左斜向
	for(i = x + 1, j = y + 1; i < N, y < N; i++, j++)
		if(gomoku[i][j] == piece_type)
			count++;
		else break;
	for(i = x - 1, j = y - 1; i > 0, j > 0; i--, j--)
		if(gomoku[i][j] == piece_type)
			count++;
		else break;
	if(count >= 4) return 1;//胜利
	count=0;
    //统计右斜向
	for(i = x - 1, j = y + 1; i > 0, j < N; i--, j++)
		if(gomoku[i][j] == piece_type)
			count++;
		else break;
	for(i = x + 1, j = y - 1; i < N, j > 0; i++, j--)
		if(gomoku[i][j] == piece_type)
			count++;
		else break;
	if(count >= 4) return 1;//胜利
	return 0;//没有胜利
}