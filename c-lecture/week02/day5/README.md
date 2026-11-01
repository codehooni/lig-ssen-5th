## int arr[5]

### int (*p)
- 구분
    -  p: a pointer to int
    - *p: int
- sizeof
    - sizeof ( p): 4 // a pointer (to int)
    - sizeof (*p): 4 // int

### int (*p) [5] // 함수에서 전체를 받을 때
- 구분
    -   p: a pointer to an array of 5 int
    -  *p: an array of 5 int
    - **p: int


## char str[5][10]

### char (*p) [10]
- 구분
    -  p: a pointer to an array of 10 char
    - *p: an array of 10 char
- sizeof
    - sizeof (p): 4 // a pointer (to an array of 10 char)
    - sizeof (*p) = sizeof(char[10]): 10 // an array of 10 (char)
- &
    - &p: 포인터 주소
    - &(*p) = &(p[0]) = &(str0): 첫 번째 요소의 주소

### char (*p)[5][10]
- 구분
    -    p: a pointer to an array of 5 arrays of 10 char
    -   *p: an array of 5 arrays of 10 char 
    -  **p: an array of 10 char
    - ***p: char
- sizeof
    - sizeof (   p): 4 // a pointer (to an array of 5 arrays of 10 char)
    - sizeof (  *p): 50 // an array (of 5 arrays of 10 char)
    - sizeof ( **p): 10 // an array of 10 char
    - sizeof (***p): 1 // char
    
### char **p
- 구분
    -   p: a pointer to a pointer to char
    -  *p: a pointer to char
    - **p: char
- sizeof
    - sizeof (p)  : 4 // a pointer (to a pointer to char)
    - sizeof (*p) : 4 // a pointer (to char)
    - sizeof (**p): 1 // char




### P.186
1. 0d1000, int (*) [4]
2. 0d1000. int *
3. 0d1000, int *
4. 0d1000, int // 1
5. 0d1000, int // 1
6. 0d1016, int // 5
7. 0d1016, int // 5
8. 0d1008, int // 3
9. 0d1008, int // 3
10. 0d1000, int // 2
11. 0d1048, int * [4] // 범위 초과 
12. 0d1004, int * // 2
13. 0d1048, int * // 범위 초과
14. 0d1000, int * // 0d1000
15. 0d1024, int * // 0d1024
16. 0d1032, int * // 0d1032