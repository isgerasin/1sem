#include <stdio.h>


#define MACROS pritnf("Hello World!"); // макрос( этот код тупо подставляется туда, где будет написано MACROS )

void funcprintHello() // функция( она отдельно вызывается)
{
	pritnf("Hello World!");
}




int main(int argc, char **argv)
{
	int a[] = { 0, 10, 20, 30, 40, 50, 60, 70 };
	int* p = &a[3];
	*( p + 4 ) = 100;
}
