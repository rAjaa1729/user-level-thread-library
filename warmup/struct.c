#include<stdio.h>
#include<math.h>

struct Point {
	int x, y;
};

typedef struct Point Point;

// float distance(int p1x, int p1y, int p2x, int p2y) {
// 	return sqrt(pow(p1x - p2x, 2) + pow(p1y - p2y, 2));
// }

float distance(Point p1, Point p2) {
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int main() {
	Point p1 = {.x = 0, .y = 0};
	Point p2 = {.x = 3, .y = 4};

	printf("%.2f\n", distance(p1, p2));
}
