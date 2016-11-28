#include <stdio.h>
#include <assert.h>
#define N 100

struct _Decimal {
	char a[N]; // number is a[0]*10^0 + a[1]*10^1 + ..+ a[n]*10^n
	unsigned int n; // наибольшая степень десяти
};
typedef struct _Decimal Decimal;

Decimal add (Decimal a, Decimal b)
{
	Decimal res = {};
	unsigned int z;
	if ( a.n > b.n )
		z = a.n;
	else
		z = b.n;
	//printf("%d", z);
	int i;
	res.a[0]=0;

	for ( i=0; i<z; i++)
	{
		res.a[i] = res.a[i]+a.a[i]+b.a[i];
		if (res.a[i]>9)
		{
			res.a[i]=res.a[i]-10;
			res.a[i+1]=1;
		}
	}
	res.n = z;
	return res;
}

void print (Decimal p){
	int i;
	
	for (i=0; i <= p.n ; i++)
	{
		printf("%d", p.a[p.n-i]);
	}
}

int main(){
	Decimal a = {{7, 4, 1}, 2}; // set number 147
	Decimal b = {{3, 1}, 1}; // set number 13
	Decimal res;
	
	res = add(a, b); // res = a+b = 147+13 = 160
	
	print(res); // print 160
	
	printf("\n");

return 0;
}