#include <stdio.h>

int comp( void** a1, void** a2 )

{
	char* d1 = ( char* ) *a1;
	char* d2 = ( char* ) *a2;
	if ( (d1[0] + d1[1] + d1[2]) != (d2[0] + d2[1] + d2[2]) )
		return d1[0] + d1[1] + d1[2] -( d2[0] + d2[1] + d2[2] ); 
	else if ( d1[0] != d2[0] )
		return  d1[0] - d2[0];
	else if ( d1[1] != d2[1] )
		return  d1[1] - d2[1];
	else if ( d1[2] != d2[2] )
		return  d1[2] - d2[2];
	else
		return 0;
}

int main(int argc, char **argv)
{
	int b = 0;
	scanf( "%d", &b );
	int data[1000][3] = {};
	int i = 0;
	for ( i; i < b; i++ )
		scanf( "%d %d %d", &data[i][0], &data[i][1], &data[i][2] );
	
	qsort( data, b, 3 * sizeof( int ), comp );
	
	for ( i = 0; i < b; i++ )
		printf( "%d %d %d\n", data[i][0], data[i][1], data[i][2] );

}
