// #define _CRT_SECURE_NO_WARNINGS
// #include <stdio.h>

#if 0

#include <stdio.h>

int main(void) {

    unsigned int a = 0x12345678;
    unsigned char * p = (unsigned char *) &a;
s
    for(int i = 0; i < 4; i++) {
        printf("%p: %02X\n", (void*) (p + i), p[i]);
    }

    printf(p[0] == 0x78 ? "little-endian" : "big-endian");

    return 0;
}
#endif


#if 0

// 양수 덧셈 프로그램
int main(void) {
    int total = 0;

    int num;
    do {
        scanf("%d", &num);
        total += num;
    } while(num != 0);
    printf("num: %d\n", total);
    return 0;
}

#endif

#if 0

int main(void) {

    int currectPW = 1357;

    int enteredPW;

    for(int attempts = 3; attempts > 0; attempts--) {
        scanf("%d", &enteredPW);
        if (enteredPW == currectPW) {
            printf("Logged in successfully.");
            break;
        }
    }

    if (enteredPW != currectPW)
        printf("Please Contact the administrator.");

    return 0;
}

#endif

#if 0

int getLen(int n) {
    if(n < 1 || n > 10000000) return 0;

    int len = 1;
    while(n /= 10) len++;

    return len;
}

int main(void) {

    int num;
    scanf("%d", &num);
    printf("%d", getLen(num));
    
    return 0;
}


#endif


#if 0

int myLen(const char * c) {
    int len = 0;
    while(*(c++)) len++;
    return len; 
}

int main(void) {
    char input[9];
    scanf("%8s", input);
    
    int len = myLen(input);
    
    for(int i = len-1; i >= 0; i--) {
        printf("%c", input[i]);
    }

    return 0;
}

#endif

#if 0

int main(void) {

	int num = 1300;

	do {
        if ((num % 10) != 0)
		    printf("%d", num % 10);
		num /= 10;
	}while(num > 0);

	return 0;
}

#endif



#if 1

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

void inputData(int * arr, int n) {

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

}

void printData(int * arr, int n) {
    
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(void) {

    int score[5] = {0};

    inputData(score, SIZE(score));
    printData(score, SIZE(score));

    return 0;
}
#endif