#include <stdio.h>
//#include <iostream>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h> //inet_pton(), INET_ADDRSTRLEN
/*https://andrew0409.tistory.com/119*/
//#define _WINSOCK_DEPRECATED_NO_WARNINGS
//#define _CRT_SECURE_NO_WARNINGS
/*visual studio 2022에서는 인자 주는 거 설정하기 귀찮으니 macro로 사용한다.*/
#define DNS "www.google.com"
#define IP "8.8.8.8"
#else
// build command → g++ -o DNS_iff_IP DNS_iff_IP.cpp
#include <netdb.h>
#include <arpa/inet.h>

void usage()
{
    printf("syntax: DNS_iff_IP <DNS>\n");
    printf("sample: DNS_iff_IP www.google.com\n\n");
    printf("If you want to convert IP to DNS\n\n");
    printf("syntax: DNS_iff_IP IPver <IP>\n");
    printf("sample: DNS_iff_IP IPver 127.0.0.1\n");
    printf("sample: DNS_iff_IP IPver 8.8.8.8\n");
}
#endif

int main(int argc,/*const*/ char *argv[])
{
    
    struct in_addr addr;
    #ifdef _WIN32
    /******************************
     * Differences from Linux code*/

    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa))
    {
        fprintf(stderr, "winsock initialization failed\n");
        return false;
    }
    /******************************/
    struct hostent *dns = gethostbyname(DNS);

    if (dns == NULL)
    {
        fprintf(stderr, "DNS is not correct.\n");
        return false;
    }
    if (dns->h_addrtype != AF_INET)
    {
        fprintf(stderr, "Address type is not AF_INET\n");
        return false;
    }
    
    memcpy(&addr, dns->h_addr/*dns->h_addr_list[0]*/, dns->h_length);
    
    char ipv4[INET_ADDRSTRLEN];
    
    inet_ntop(AF_INET, &addr, ipv4, sizeof(ipv4));
    fprintf(stdout, "DNS macro: %s\n", DNS);
    fprintf(stdout, "IP address: %s\n\n", ipv4);
    
    /*IPv4 address to DNS*/
    inet_pton(AF_INET, IP, &addr); //Differences from Linux code
    struct hostent *ip = gethostbyaddr((char *)&addr, sizeof(addr), AF_INET);
    
    if (ip == NULL)
    {
        fprintf(stderr, "IPv4 is not correct.\n");
        return false;
    }
    
    if (ip->h_addrtype != AF_INET)
    {
        fprintf(stderr, "Address type is not AF_INET\n");
        return false;
    }
    fprintf(stdout, "IP macro: %s\n", IP);
    fprintf(stdout, "DNS: %s\n", ip->h_name);
    WSACleanup(); // Differences from Linux code
    #else
    if ((argc == 2) && strcmp(argv[1], "IPver"))
    {   
        /*DNS to IPv4 address*/
        struct hostent *dns = gethostbyname(argv[1]);

        if (dns == NULL)
        {
            fprintf(stderr, "DNS is not correct.\n");
            return false;
        }
        if (dns->h_addrtype != AF_INET)
        {
            fprintf(stderr, "Address type is not AF_INET\n");
            return false;
        }
        
        memcpy(&addr, dns->h_addr/*dns->h_addr_list[0]*/, dns->h_length);
        
        char ipv4[INET_ADDRSTRLEN];
        
        inet_ntop(AF_INET, &addr, ipv4, sizeof(ipv4));
        fprintf(stdout, "IP address: %s\n", ipv4);
        
    }
    else if ((argc == 3) && !strcmp(argv[1], "IPver"))
    {   
        /*IPv4 address to DNS*/
        inet_pton(AF_INET, argv[2], &addr);
        struct hostent *ip = gethostbyaddr(&addr, sizeof(addr), AF_INET);
        
        if (ip == NULL)
        {
            fprintf(stderr, "IPv4 is not correct.\n");
            return false;
        }
        
        if (ip->h_addrtype != AF_INET)
        {
            fprintf(stderr, "Address type is not AF_INET\n");
            return false;
        }
        
        fprintf(stdout, "DNS: %s\n", ip->h_name);
    }
    else
    {
        usage();
        return -1;
    }
    #endif

    return 0;
}