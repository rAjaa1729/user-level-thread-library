#include<stdio.h>
#include<stdlib.h>
#define SZ 1024*1024*1024
#define FOO_SZ 1024

//
char* foo_stack() {
	char A[FOO_SZ];
	for(int i = 0 ; i < FOO_SZ; i ++) {
		A[i] = 'A';
	}
	A[FOO_SZ - 1] = 0;
	// printf("%s", A);
	return A;
}

char* foo_heap() {
	char *A = (char*) malloc(FOO_SZ * sizeof(char));
	for(int i = 0 ; i < FOO_SZ; i ++) {
		A[i] = 'A';
	}
	A[FOO_SZ - 1] = 0;
	// printf("%s", A);
	return A;
}

int main() {
	// 1. Dynamic memory allocation
	// int sz;
	// scanf("%d", &sz);
	// char c[sz];
	// char *c = (char*) malloc(sz * sizeof(char));	// Heap allocation
	// scanf("%s", c);
	// printf("%s\n", c);
	
	// 2. Can do large allocations
	// char arr[SZ];
	// char* p = (char*)malloc(SZ*sizeof(char));
	// for(int i = 0; i  < SZ; i ++) {
	// 	*(p + i) = 'A';
	// }

	// 3. Allocation stays across function boundaries
	// char *c = foo_stack();
	// printf("stack: %s\n", c);

	// c = foo_heap();
	// printf("heap: %s\n", c);

	// 4. Must do free
	// void* p = malloc(SZ);
	// printf("Allocated GB memory\n");
	// if(p == NULL) {
	// 	return 0;
	// }
	// free(p);

	// 5. Large allocations without free
	int* p[100];
	int ctr = 0;
	while(1) {
		p[ctr] = (int*) malloc(SZ * sizeof(int));
		if(p[ctr]  == NULL) {
			return 0;
		}
		printf("Allocated %d GB memory\n", ctr);
		for(int i = 0; i  < SZ; i ++) {
			*(p[ctr] + i) = 3;
		}
		ctr++;
	}

	// while(ctr > 0) {
	// 	ctr --;
	// 	for(int i = 0; i  < SZ; i ++) {
	// 		printf("%d", *p[ctr]);
	// 	}
	// }
}
