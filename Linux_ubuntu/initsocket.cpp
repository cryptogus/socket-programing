//build command -> gcc -o initsocket initsocket.cpp
#include <stdio.h>

#ifdef linux

 //SOCKET 구조체, 타입(사용할 프로토콜 특성)
#include <sys/socket.h>
#include <sys/types.h>

#include <unistd.h>

int main(int argc, char *argv[])
{

    //소켓 생성
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    if (sock < 0)
    {
        fprintf(stderr, "소켓 생성 실패\n");
        return 1;
    }

    //소켓 닫기
    close(sock);

    fprintf(stdout, "SUCCESS\n");
    return 0;

}
#else
int main()
{
    printf("리눅스 환경에서 실행해주세요~\n");
}
#endif
//#ifdef linux || unix || __APPLE__ || __FreeBSD__