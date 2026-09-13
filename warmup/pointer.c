#include<stdio.h>

// |A|B|C|D|E|F|G|H|I|J| < Addresses
// -----------------------
// |J| | |2| |3| | |D|D| < Location
// -----------------------
//  ^p    ^x  ^y    ^p1 ^p2
//        p1 = &x
//        p2 = &y
//        p = &p2
int main() {
	int x, y; 
	int *p1, *p2; // Address of integers
	x = 2, y = 3;
	printf("x: %d, y: %d\n", x, y);

	p1 = &x, p2 = &y;
	*p1 = 5; 	// x = 5
	*p2 = 8;	// y = 8
	printf("x: %d, y: %d\n", x, y); // 5, 8

	int **p = &p2;	// Address of pointer variable
	*p = p1;	// p1 = &x; p2 = p1; p2 = &x; changed p2 to point to x.
	*p2 = 10;	// only one value is assigned to 10
	printf("x: %d, y: %d\n", x, y);	// 5, 10 or 10, 10 or 10, 8

	// printf("%lu, %lu, %lu, %lu\n", sizeof(x), sizeof(y), sizeof(p1), sizeof(p2));
}
