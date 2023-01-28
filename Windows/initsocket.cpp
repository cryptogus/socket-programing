#include <stdio.h>

#ifdef _WIN32

#include <winsock2.h> //SOCKET 구조체

int main(int argc, char *argv[])
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0)
    {
        fprintf(stderr, "윈속 초기화 실패\n");
        return 1;
    }

    //소켓 생성
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        fprintf(stderr, "소켓 생성 실패\n");
        return 2;
    }

    //소켓 닫기
    closesocket(sock);

    //윈속 종료
    WSACleanup();
    
    fprintf(stdout, "SUCCESS\n");
    return 0;

}
#endif
//#else 대신 환경 명시
#ifdef linux || unix || __APPLE__ || __FreeBSD__

int main()
{
    printf("windows 환경에서 사용해주세요.\n");
    return -1;
}
#endif