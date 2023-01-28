#include <iostream>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h> //IPv6 구조체 (sockaddr_in6), inet_pton(), inet_ntop()

#else // linux

// build command → g++ -o IpAddr IpAddr.cpp
#include <sys/socket.h> //sockaddr 구조체
#include <netinet/in.h> //sockaddr_in, sockaddr_in6, sockaddr_bth 구조체, hton, ntoh
#include <arpa/inet.h> //Convert Internet host address, inet_pton(), inet_ntop()

#endif

int main(int argc, char *argv[])
{
    /*IPv4 test*/
    const char *ip4 = "172.0.2.32";
    fprintf(stdout, "IPv4 주소(string) = %s\n", ip4);

    //inet_pton() test
    struct in_addr ipv4num;
    inet_pton(AF_INET, ip4, &ipv4num); //string to network numberic (presentation to network)
    fprintf(stdout, "IPv4 주소(numberic) = %#x\n", ipv4num.s_addr);

    //inet_ntop() test
    char ip4_2[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &ipv4num, ip4_2, sizeof(ip4_2)); //network to presentation
    fprintf(stdout, "IPv4 주소(원상복귀) = %s\n\n", ip4_2);

    /*IPv6 test*/
    const char *ip6 = "2001:2030:abcd:efaa:0023:eb00:ffff:1111";
    fprintf(stdout, "IPv6 주소(string) = %s\n", ip6);

    //inet_pton() test
    struct in6_addr ipv6num;
    inet_pton(AF_INET6, ip6, &ipv6num);
    fprintf(stdout,"IPv6 주소(numberic) = 0x");
    for (int i = 0; i < 16; i++)
    {
        fprintf(stdout, "%02x", ipv6num.s6_addr[i]);
    }
    std::cout << std::endl;
    
    //inet_ntop() test
    char ip6_2[INET6_ADDRSTRLEN];
    inet_ntop(AF_INET6, &ipv6num, ip6_2, sizeof(ip6_2)); //network to presentation
    fprintf(stdout, "IPv6 주소(원상복귀) = %s\n", ip6_2);

    return 0;
}