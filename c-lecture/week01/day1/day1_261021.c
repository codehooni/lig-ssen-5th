#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#if 0

int main(void) {
	float a = 1.234567890123456789f;
	double b = 1.234567890123456789;

	printf("%.20f\n", a);
	printf("%.20f\n", b);

	float c = 3.99999f;
	printf("%d", (int) c);

	return 0;
}

#endif


#if 0

int main(void) {
	const double a = 1.4;

	double* p = &a;
	*p = 1.2;
	printf("%f", a);


	const char* cp = "rabbit";
	cp = "cat";
	//cp[0] = 'd';
	printf("%s", cp);

	char* const cp2 = "rabbit";
	//cp2 = "cat";
	cp2[0] = 'd';
	printf("%s", cp2);

	const char* const cp3 = "rabbit";
	//cp3 = "cat";
	//cp3[0] = 'd';
	

	return 0;
}

#endif


#if 0

int myStrlen(const char* str)
{
	const char* s;

	if (str == 0)
		return 0;
	for (s = str; *s; ++s);
	return s - str;
}

int main(void) {
	
	int len = myStrlen("Hello");
	printf("%d\n", len);

	return 0;
}


#endif


#if 0

int main(void) {

	int a;

	scanf_s("%d", &a);
	printf("%d", a);


	return 0;
}


#endif


#if 0

int main(void) {

	int a = 10, b = 20;


	int res;

	res = (a > b) ? a : b;

	if (a > b) {
		res = a;
	}
	else {
		res = b;
	}

	printf("%d", res);


	return 0;
}


#endif

#if 0

unsigned int setBit(unsigned int num, int n) {
	return num | (1u << n);
}

unsigned int setBits(unsigned int num, int n, int count) {

}

unsigned int clearBit(unsigned int num, int n) {
	return num & ~(1u << n);
}

unsigned int toggleBit(unsigned int num, int n) {
	return num ^ (1u << n);
}

unsigned int getBit(unsigned int num, int n) {
	return (num >> n) & 1;
}

void printBits8(unsigned int num) {
	for (int i = 7; i >= 0; i--) {
		printf("%u", getBit(num, i));
	}
	printf("\n");
}

int main(void) {

	unsigned int a = 0b11001010;

	printBits8(a);
	printBits8(setBit(a, 0));
	printBits8(clearBit(a, 7));   
	printBits8(toggleBit(a, 3));  
	printf("%u\n", getBit(a, 1)); 

	return 0;
}


#endif


#if 0

int main(void) {

	int num = 7329;
	int a1, a2, a3, a4;

	a1 = num / 1000;
	a2 = num / 100 % 10;
	a3 = num / 10 % 10;
	a4 = num % 10;

	printf("%d %d %d %d\n", a1, a2, a3, a4);

	return 0;
}


#endif

#if 0

int main(void) {

	int a = 25, b = 5;

	a %= b -= 1; // 대입(=)은 식  (not 문)
	printf("%d %d", a, b);

	return 0;
}


#endif


#if 0

int main(void) {

	unsigned int a = 0xf0;
	int b = 0xf0;
	unsigned int c = 0x0f;
	int d = 0x0f;

	if (a == ~c) printf("1\n");
	if (a == ~d) printf("2\n");
	if (b == ~c) printf("3\n");
	if (b == ~d) printf("4\n");
	printf("hello, world");

	return 0;
}


#endif


#if 1

int main(void) {

	unsigned int a = 0xf0;
	int b = 0xf0;
	unsigned int c = 0x0f;
	int d = 0x0f;

	if (a == ~c) printf("1\n");
	if (a == ~d) printf("2\n");
	if (b == ~c) printf("3\n");
	if (b == ~d) printf("4\n");
	printf("hello, world");

	return 0;
}


#endif


#if 0



#endif