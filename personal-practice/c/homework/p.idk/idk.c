#include "idk_lib.h"

// 포인터 배열도 동적할당, 배열의 멤버도 동적할당

int main(void) {

    freopen("student3.txt", "r", stdin);

    class_t myClass;

    initClass(&myClass);

    printClass(myClass);

    freeMem(&myClass); // realloc사용해서 한 번에 받기

    return 0;
}