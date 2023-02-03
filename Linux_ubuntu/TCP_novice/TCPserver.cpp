/*g++ TCPserver.cpp -o TCPserver*/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUFSIZE 1024

void usage()
{
    std::cout << "Syntax: TCPserver <port>\nWarning: <port> is 1024 ~ 49151" << std::endl;
    
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        usage();
        return -1;
    }
    int retval;
    
    int listen_sock = socket(AF_INET, SOCK_STREAM, 0);

    if (listen_sock < 0)
    {
        fprintf(stderr,"socket 생성 error\n");
        return 1;

    }

    //bind
    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(atoi(argv[1]));
    retval = bind(listen_sock, (struct sockaddr *)&server, sizeof(server));
    if (retval < 0)
    {
        fprintf(stderr,"bind error\n\n");
        usage();
        return 2;
    }

    //listen
    retval = listen(listen_sock, SOMAXCONN);
    if (retval < 0)
    {
        fprintf(stderr,"listen error\n");
        return 3;
    }

    //socket for client connection
    int server_sock;
    struct sockaddr_in client_addr;
    socklen_t addrlen;
    char buf[BUFSIZE + 1] = {0,};
    char addr[INET_ADDRSTRLEN];
    char port[6];
    std::cout<<"TCP server start"<<std::endl;

    while (true)
    {
        addrlen = sizeof(client_addr);
        server_sock = accept(listen_sock, (struct sockaddr *)&client_addr, &addrlen);
        if (server_sock < 0)
        {
            fprintf(stderr,"accept error\n");
            return 4;
        }
        
        //data from client
        while (true)
        {
            retval = recv(server_sock, buf, BUFSIZE, 0);
            if (retval < 0)
            {
                fprintf(stderr,"recv error\n");
                return 5;
            }else if (retval == 0)
            {
                break;
            }
        

            //data print
            buf[retval] = '\0';
            inet_ntop(AF_INET, &client_addr.sin_addr, addr, sizeof(addr));
            
            fprintf(stdout,"From [%s:%d]: %s\n",addr, ntohs(client_addr.sin_port), buf);

            //send data
            retval = send(server_sock, buf, retval, 0);
        }
        close(server_sock);
        fprintf(stdout, "[TCP server terminated]\n");

    }
    close(listen_sock);

    return 0;
    
    

}