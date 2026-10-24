#include "day3_lib.h"

#if 1
struct myFunc_t {
    int (*fp) (int*, int);
    char * name;
};

int main(void) {

    int score[5] = {0};

    inputData(score, SIZE(score));
    // printData(score, SIZE(score));

    // printf("total = %d\n", sumData(score, SIZE(score)));
    // printf("average = %.2f\n", avgData(score, SIZE(score)));
    // printf("max = %d\n", findMaxData(score, SIZE(score)));
    // printf("min = %d\n", findMinData(score, SIZE(score)));

    // selectionSortData(score, SIZE(score));
    // printData(score, SIZE(score));
    bubbleSortData(score, SIZE(score));
    printData(score, SIZE(score));
    // insertionSortData(score, SIZE(score));
    // printData(score, SIZE(score));

    //Array of Pointer to Function returning a int
    // struct myFunc_t myFuncArr[] = {
    //     {sumData, "sum"},
    //     {findMaxData, "max"},
    //     {findMinData, "min"},
    // };

    // for(int i = 0; i < 3; i ++ ) {
    //     printf("%s = %d\n", myFuncArr[i].name, myFuncArr[i].fp(score, SIZE(score)));
    // }

    return 0;
}
#endif

#if 0

int main(void) {

    char str1[80] = "cat";
    char str2[80];

    strcpy(str1, "tiger");
    strcpy(str2, str1);

    printf("%s, %s\n", str1, str2);

    char str[80] = {0};

    scanf("%s", str);
    printf("%s\n", str);

    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';   // 끝에 붙은 '\n' 제거
    printf("%s\n", str);

    char c;
    scanf("%c", &c);
    printf("%c\n", c);

    scanf("%c", &c); // scanf에서 c를 하나 가져가면 공백
    printf("%c\n", c);

    return 0;
}

#endif

#if 0

int main(void) {

    char str1[10] = "apple";
    char * p1 = str1;
    p1[0] = 'a'; // 가능

    char * p2 = "banana";
    // p2[0] = 'a'; // 불가능 .rodata

    printf("%s\n", "apple" + 2); // "apple"도 포인터 상수 => "ple"
    printf("%c\n", "banana"[3]); // "banana"도 포인터 상수 => "a"

    str = "banana"; // 포인터 상수 (complie error)
    p2[0] = 'K'; // read only (run time error)

    return 0;
}

#endif

#if 0

extern int a;

int main(void) {

    int a = 10, b = 20;

    swap(&a, &b);

    printf("a = %d, b = %d\n", a, b);

    return 0;
}

#endif 

#if 0

int main(void) {

    int arr[10] = {0};

    int input;
    
    while(1) {
        scanf("%d", &input);
        if(!input) break;
        arr[input % 10]++;
    }

    for(int i = 0; i < 10; i++) {
        if(!arr[i]) continue;

        printf("%d : %d times\n", i, arr[i]);
    }

    return 0;
}

#endif