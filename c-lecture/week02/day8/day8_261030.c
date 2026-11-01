#include "day8_lib.h"
#include "../day7/day7_lib.h"

#if 0

int main(void) {

    int * arr, n = 10;

    arr = (int *)malloc(10 * sizeof(int));

    if (arr == NULL) {
        printf("There's no memory.");
        exit(1);
    }

    for(int i = 0; i < 10; i++) {
        arr[i] = 10 * i;
    }

    printData(arr, n);

    int * temp = (int *) realloc(arr, n * sizeof(int));

    if(temp == NULL) return 12;
    if(temp != arr) arr = temp;
    arr[3] = 1000;

    printData(arr, n);

    free(arr);
    arr = NULL;

    return 0;
}

#endif

#if 0

int main(void) {

    int * arr, * temp;
    int num;
    int size = 10, index;

    arr = (int *) malloc(size * sizeof(int));

    if(arr == NULL) {
        printf("There's no memory.");
        exit(1);
    }

    for(index = 0; (num = getInt()) > 0; index++) {

        if(index == size) {
            size += 5;

            temp = (int *) realloc(arr, size * sizeof(int));

            if(temp == NULL) {
                printf("There's no memory.");
                free(arr);
                exit(1);
            }

            arr = temp;
        }

        arr[index] = num;
    }

    printData(arr, index);

    free(arr);
    arr = NULL;

    return 0;
}

#endif

#if 0

typedef char (*p21c)[21];
typedef char c21[21];

int main(void) {

    freopen("data.txt", "r", stdin);

    int n;
    p21c arr;

    scanf("%d", &n);
    getchar();

    arr = (p21c) calloc(n, sizeof(c21));

    for(int i = 0; i < n; i++) {
        gets(arr[i]);
    }

    for(int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }

    return 0;
}

#endif

#if 0

typedef char ** s_arr_t;
typedef char * str_t;

int main(void) {

    freopen("data.txt", "r", stdin);

    int n, len = 21;
    str_t str;
    s_arr_t arr;

    scanf("%d", &n);
    getchar();

    arr = (s_arr_t) calloc(n, sizeof(str));

    if(arr == NULL) exit(1);

    for(int i = 0; i < n; i++) {
        str = (str_t) calloc(len, sizeof(char));

        if(arr == NULL) exit(1);

        gets(str);
        arr[i] = str;
    }

    for(int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }

    return 0;
}

#endif

#if 0

typedef char ** s_arr_t;
typedef char str_t[21];

int main(void) {

    freopen("data.txt", "r", stdin);

    int n, len = 21;
    str_t str;
    s_arr_t arr;

    scanf("%d", &n);
    getchar();

    arr = (s_arr_t) calloc(n, sizeof(char *));

    if(arr == NULL) exit(1);

    for(int i = 0; i < n; i++) {
        gets(str);

        arr[i] = (char *) malloc((strlen(str) + 1) * sizeof(char));

        if(arr[i] == NULL) exit(1);

        strcpy(arr[i], str);
    }

    for(int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }

    freeDoubleMem((void ***) &arr, n);

    return 0;
}

#endif

#if 0

typedef char ** s_arr_t;
typedef char str_t[21];

char ** getData(int n) {
    str_t str;
    s_arr_t arr;

    arr = (s_arr_t) calloc(n, sizeof(char *));

    if(arr == NULL) exit(1);

    for(int i = 0; i < n; i++) {
        gets(str);

        arr[i] = (char *) malloc((strlen(str) + 1) * sizeof(char));

        if(arr[i] == NULL) exit(1);

        strcpy(arr[i], str);
    }

    return arr;
}

int main(void) {

    freopen("data.txt", "r", stdin);

    int n, len = 21;
    s_arr_t arr;

    scanf("%d", &n);
    getchar();

    arr = getData(n);

    for(int i = 0; i < n; i++) {
        printf("%s\n", arr[i]);
    }

    freeDoubleMem((void ***) &arr, n);

    return 0;
}

#endif

#if 0

int main(void) {

    char ** arr;
    char * str;
    int n;

    arr = (char**) malloc(1000);

    scanf("%d", &n);
    getchar();

    arr[0] = arr + n;

    for(int i = 0; i < n; i++) {
        gets(arr[0]);
        arr[1] = (char) arr + strlen(arr[0]);

        gets(arr[1]);

        arr[1] = (char) arr + strlen(arr[0]);
    }

    return 0;
}

#endif

#if 01

// assignment 
// 큰 메모리를 한 번 할당 받아 그 메모리에 주소 및 문자를 모두 저장
// 모두 저장후 realloc을 사용해 불필요한 메모리 반환하여 보기.

int main(void) {

    freopen("data.txt", "r", stdin);

    char **arr, **tmp, *str, *last;
    int n, size;

    arr = malloc(1000);

    scanf("%d", &n);

    arr[0] = (char *) arr + (n * sizeof(char *));
    scanf("%s", arr[0]);

    for(int i = 1; i < n; i++) {
        arr[i] = arr[i - 1] + (strlen(arr[i - 1]) + 1);
        scanf("%s", arr[i]);
    }

    last = arr[n - 1] + (strlen(arr[n - 1]) + 1);

    size = last - (char *) arr;

    tmp = realloc(arr, size);
    if(tmp == NULL) {
        free(arr);
        return EXIT_FAILURE;
    }

    if(arr != tmp) {
        tmp[0] = (char *) tmp + (n * sizeof(char *));

        for(int i = 1; i < n; i++) {
            tmp[i] = tmp[i - 1] + (strlen(tmp[i - 1]) + 1);
        }

        arr = tmp;       
    }

    for(int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }

    free(arr);
    arr = NULL;

    return 0;
}

#endif

#if 0

struct student {
    int num;
    double grade;
    char name[20];
    char * phone;
};

typedef struct student student_t;

void printStudent(student_t a) {
    printf("%d %.1lf %s\n", a.num, a.grade, a.name);
}

void printStudent_p(student_t * p) {
    printf("%d %.1lf %s\n", p -> num, p -> grade, p -> name);
    printf("%d %.1lf %s\n", (*p).num, (*p).grade, (*p).name);
}

int main(void) {

    student_t a = { 1, 4.3, "Jihoon Lee", "010-1234-1234" };
    student_t b;

    b = a;
    strcpy(b.name, "SOS");

    printStudent(a);
    printStudent_p(&b);

    a.phone = "010-7980-7093";
 
    return 0;
}

#endif

#if 0

typedef struct student {
    int num;
    double grade;
    char name[20];
}student_t;

void initStudent(student_t * arr, size_t n) {

    student_t * p;

    for(int i = 0; i < n; i++) {
        p = arr + i;
        scanf("%d %lf %s", &p -> num, &p -> grade, p -> name);
    }

}

void printStudent(student_t * arr, size_t n) {

    student_t * p;

    for(int i = 0; i < n; i++) {
        p = arr + i;
        printf("%d %.1lf %7s\n", p -> num, p -> grade, p -> name);
    }

}

int main(void) {

    freopen("student.txt", "r", stdin);

    const int N = 4;
    student_t arr[N];

    initStudent(arr, N);

    printStudent(arr, N);

    return 0;
}

#endif

#if 0

typedef struct profile {
    int age;
    char * favorateColor[3];
    char name[20];
}profile_t;

typedef struct student {
    int num;
    double grade;
    profile_t profile;
}student_t;

typedef char str_t[20];

void initStudent(student_t * arr, size_t n) {

    str_t buf;

    for(int i = 0; i < n; i++) {
        student_t * sp = arr + i;
        profile_t * pp = &sp -> profile;

        scanf("%d %lf %d", &sp -> num, &sp -> grade,&pp -> age);
        for(int i = 0; i < 3; i++) {
            scanf("%s", buf);
            pp->favorateColor[i] = (char *) malloc(strlen(buf) + 1);
            if(pp == NULL) exit(1);
            strcpy(pp->favorateColor[i], buf);
        }
        scanf("%s", pp -> name);
    }

}

void printStudent(student_t * arr, size_t n) {

    student_t * sp;
    profile_t * pp;

    for(int i = 0; i < n; i++) {
        sp = arr + i;
        pp = &sp -> profile;
        printf("%d %.1lf %d %s %s %s %s\n", 
            sp->num, sp->grade, pp->age, 
            pp->favorateColor[0], pp->favorateColor[1], pp->favorateColor[2],
            pp->name
        );
    }
}

void freeMem3(void * p, size_t n) {

    student_t * s = (student_t *) p;

    student_t * sp;
    profile_t * pp;

    for(int i = 0; i < n; i++) {
        sp = s + i;
        pp = &(s + i) -> profile;
        for(int j = 0; j < 3; j++) {
            freeMem((void**) &pp->favorateColor[j]);
        }
    }
}

int main(void) {

    freopen("student2.txt", "r", stdin);

    const int N = 3;
    student_t arr[N];
    
    initStudent(arr, N);
    printStudent(arr, N);

    freeMem3(arr, N);


    // 해제된 메모리 확인
    student_t * sp;
    profile_t * pp;

    for(int i = 0; i < N; i++) {
        sp = arr + i;
        pp = &(arr + i) -> profile;
        for(int j = 0; j < 3; j++) {
            printf("p = %p\n", pp->favorateColor[j]);
        }
    }

    return 0;
}

#endif