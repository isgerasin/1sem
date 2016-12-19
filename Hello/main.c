#include <stdio.h>

int x = 10;

void foo(int* y )
{
	*y = *y - 7;
}

int main()
{
	foo();
	foo();
	printf("x=%d\n", x);
	return 0;
}