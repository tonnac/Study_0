#include <stdio.h>

int length, width;
long area;
struct coord {
	int x;
	int y;
};

struct rectangle {
	struct coord top;
	struct coord bottom;
}box;

int main(void)
{
	printf("Top x: ");
	scanf("%d", &box.top.x);
	printf("Top y: ");
	scanf("%d", &box.top.y);
	printf("Bottom x: ");
	scanf("%d", &box.bottom.x);
	printf("Bottom y: ");
	scanf("%d", &box.bottom.y);

	width = box.bottom.x - box.top.x;
	length = box.bottom.y - box.top.y;
	area = width * length;
	printf("The area is %ld units.", area);

	return 0;
}