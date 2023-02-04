#include <iostream>
#include <cstring>
#include <cstdlib>
#include <WinSock2.h>
#include <WS2tcpip.h>

char* SERVERIP = (char *)"127.0.0.1";
#define SERVERPORT 9000
#define BUFSIZE 1024


int main(int argc, char* argv[])
{
    WSAData wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
        return -1;

    int retval;

    //socket 생성
    SOCKET client_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (client_sock < 0)
    {
        fprintf(stderr, "socket 생성 error\n");
        return 1;
    }

    //connect
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    inet_pton(AF_INET, SERVERIP, &server.sin_addr);
    server.sin_port = htons(SERVERPORT);
    retval = connect(client_sock, (struct sockaddr*)&server, sizeof(server));

    if (retval < 0)
    {
        fprintf(stderr, "connect failed.\nIs the server running?\n");
        return 2;
    }

    char buf[BUFSIZE + 1];
    int len;

    while (true)
    {
        std::cout << "[Text input] ";
        if (fgets(buf, BUFSIZE + 1, stdin) == NULL)
        {
            break;
        }
        std::cout << std::endl;

        // delete '\n'
        len = (int)strlen(buf);
        if (buf[len - 1] == '\n')
        {
            buf[len - 1] = '\0';
        }
        if (strlen(buf) == 0)
        {
            break;
        }

        //send the data
        retval = send(client_sock, buf, (int)strlen(buf), 0);
        if (retval < 0)
        {
            fprintf(stderr, "send failed\nI think that text length is problem\n");
            break;
        }
        std::cout << "send the " << retval << " byte" << std::endl;

        //receive the data
        retval = recv(client_sock, buf, retval, MSG_WAITALL);
        if (retval < 0)
        {
            fprintf(stderr, "receive failed\n");
            break;
        }

        buf[retval] = '\0';
        std::cout << "receive " << retval << " byte from server" << std::endl;
        std::cout << "receive data from server " << buf << std::endl;

    }

    closesocket(client_sock);
    
    WSACleanup();
    return 0;


}
