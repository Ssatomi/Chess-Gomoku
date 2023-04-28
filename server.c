#include"gomoku.h"

#define IP "127.0.0.1"
#define PORT 6666

int main() {
    char gomoku[N][N];
    int message[2];
    struct sockaddr_in server_addr;
    int fd_socket, fd_connected;
    int x, y;
    int is_over = 0;
    //创建socket，使用tcp
    ASSERT((fd_socket = socket(AF_INET, SOCK_STREAM, 0)) != -1, "socket init fail\n");
    //bind绑定
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=inet_addr(IP);
    ASSERT(bind(fd_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) != -1, "bind fail\n");
    //listen监听
    ASSERT(listen(fd_socket, 10) != -1, "listen fail\n");
    //accept接受连接
    printf("wait for connect...\n");
    ASSERT((fd_connected = accept(fd_socket, NULL, NULL)) != -1, "accept fail\n");
    //初始化并渲染棋盘
    gomokuInit(gomoku);
    gomokuShow(gomoku);
    printf("gomoku game start\n");
    //下棋
    while(!is_over) {
        //client下棋
        printf("wait for client to play\n");
        recv(fd_connected, message, sizeof(message), 0);
        gomoku[message[0]][message[1]] = '0';//client棋子为0
        gomokuShow(gomoku);
        if (checkWin(message[0], message[1], gomoku, '0')) {
            printf("client win\n");
            break;
        }
        //server下棋
        while(1) {
            printf("server to play:\n");
            scanf("%d %d", &x, &y);
            if (x < 1 || x > N - 1 || y < 1 || y > N - 1) {
                printf("invaild position\n");
                continue;
            }
            if (gomoku[x][y] != '_') {
                printf("position occupied\n");
                continue;
            }
            gomoku[x][y] = '*';//server棋子为*
            gomokuShow(gomoku);
            if (checkWin(x, y, gomoku, '*')) {
                printf("server win\n");
                is_over = 1;
            }
            break;
        }
        //传送下棋位置
        message[0] = x;
        message[1] = y;
        send(fd_connected, message, sizeof(message), 0);
    }
    //关闭socket
    close(fd_socket);
    close(fd_connected);
    return 0;
}