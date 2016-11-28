#include <stdio.h>
#include <stdlib.h> // чтобы работал qsort
#define N 100
// 0 if x==y
// <0 if x<y
// >0 if x>y
// определение функции сравнения для массива int'ов
int cmp_int( const void * p1, const void * p2 ) {
	int x = *( int* )p1; // добываем из указателя значение по этому указателю
	int y = *( int* )p2; // добываем из указателя значение по этому указателю
	return x-y;
}
void print(int a[], int n) {
	int i;
	for (i = 0; i<n; i++)
	printf("%d ", a[i]);
	printf("\n");
}
int main()
{

	int n;
	scanf ("%d", &n);
	int i;
	int a[N];
	for (i=0; i<n; i++)
	{
		scanf("%d", &a[i]);
	}
	print(a, n);
	qsort(a, n, sizeof(int), cmp_int); // сортировка массива a
	print(a, n);
	return 0;
}