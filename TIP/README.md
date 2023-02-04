# struct size packing option in c/c++
기본적으로 c/c++ 컴파일러는 구조체 멤버에 대한 접근 속도를 빠르게 하기 위해 메모리를 약간 낭비하는 방식을 취한다.
```c
struct Memory
{
    int first; // 4byte
    char second; //1byte
    int third; //4byte
}
```
총 합쳐서 구조체에 9byte가 할당 될 것 같지만 실제로는 12byte가 할당된다.   
만약 비어 있는 메모리를 없애고 9byte를 할당하고싶다면 구조체 패킹 옵션을 주면 된다.   
```c
//In Windows
#pragma pack(1) // 구조체 메모리를 1byte 기준으로 변경

struct Memory
{
    int first; // 4byte
    char second; //1byte
    int third; //4byte
}
#pragma pack() // 원상 복귀 -> 구조체 12byte 할당
```
```c
//In Linux
struct __attribute__((packed)) Memory
{
    int first; // 4byte
    char second; //1byte
    int third; //4byte
}
```