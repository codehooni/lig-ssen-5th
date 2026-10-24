#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#if 0

unsigned int setBits(unsigned int num, int s, int n) {
	return num | (((1 << n) -1) << s);
}

unsigned int clearBits(unsigned int num, int s, int n) {
	return num & ~(((1 << n) -1) << s);
}

unsigned int toggleBits(unsigned int num, int s, int n) {
	return num ^ (((1 << n) -1) << s);
}

unsigned int isBitSet(unsigned int num, int n) {
    return (num >> n) & 1;
}

unsigned int isBitSets(unsigned int num, int s, int n) {
    return (num >> s) & ((1 << n) - 1);
}

void printBits8(unsigned int num) {
	for (int i = 7; i >= 0; i--) {
		printf("%u", isBitSet(num, i));
	}
	printf("\n");
}

int main(void) {

	unsigned int a = 0b11001010;

	printBits8(a);
	// printBits8(setBits(a, 2, 3));
	// printBits8(clearBits(a, 6, 2));   
	// printBits8(toggleBits(a, 3, 3));
    printf("%u\n", isBitSets(a, 1, 2));

	return 0;
}


#endif


#if 0

int main(void) {

	int n;
	scanf("%d", &n);

	if (n % 2 == 0) {
		printf("Even\n");
	} else {
		printf("Odd\n");
	}

	printf((n & 1) ? "odd" : "even");
	
	return 0;
}

#endif




#if 0

int func(int n) {

	if (n % 2 == 0) return 2;
	if (n % 3 == 0) return 3;
	if (n % 5 == 0) return 5;

	return 0;
}

int main(void) {

	int n;
	scanf("%d", &n);

	printf("result: %d", func(n));

	return 0;
}

#endif



#if 0

void solution(int score) {
	
	if(score >= 70){
		printf("pass");
	} 
	else if (score >= 60) {
		printf("try again");
	}
	else {
		printf("faild");
	}


}

int main(void) {

	int score = 50;

	if(score >= 70){
		printf("pass\n");
	} 
	else if (score >= 60) {
		printf("try again\n");
	}
	else {
		printf("fail\n");
	}

	printf(
		(score >= 70) ? "pass\n" :
	 	(score >= 60) ? "try again\n" : "fail\n"
	);

	printf("Thank you :)");

	return 0;
}


#endif


#if 0

int main(void) {

	int score = 89;
	char result;

	switch (score / 10) {
		case 10:
		case 9:
			result = 'A';
			break;
		case 8:
			result = 'B';
			break;
		case 7:
			result = 'C';
			break;
		case 6:
			result = 'D';
			break;
		default:
			result = 'F';
	}

	printf("%c", result);

	return 0;
}


#endif


#if 0

int main(void) {

	int s = 99;
	char* grade = "FFFFFFDCBAA";

	printf("%c\n", *(grade + (s / 10)));

	return 0;
}

#endif

#if 0

int main(void) {

	int n1 = 11;

	while(n1 > 10) {
		printf("number1: ");
		scanf("%d", &n1);
	} 

	int n2;

	do {
		printf("number2: ");
		scanf("%d", &n2);
	} while(n2 > 10);

	return 0;
}

#endif


#if 0

int main(void) {

	printf("Hello, World!");

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
		if(input[i] != '0')
        	printf("%c", input[i]);
    }

    return 0;
}

#endif


#if 1

int main(void) {

	int num = 1300;

	do {
		printf("%d", num % 10);
		num /= 10;
	}while(num > 0);

	return 0;
}

#endif