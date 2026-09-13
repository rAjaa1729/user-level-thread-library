#include<stdio.h>

// ---------------
// |A|B|C|D|E|F|G|
// ---------------
// |3| | |3| | |A|
// ---------------
//  ^x    ^y    ^p

// Call by value
void foo_val(int y) {
	y = 3;
}

// call by reference 
int foo_ref(const int *p) {
	// *p = 3;
	return (*p)*(*p);
}

// const
int main() {
	int x = 2;

	foo_val(x);
	printf("x: %d\n", x);	// Garbage value, or 2

	foo_ref(&x);
	printf("x: %d\n", x); // 3
}
