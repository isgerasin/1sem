#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

char** Get_Strings( int* count )
{
	int scount = 0;
	scanf( "%d", &scount );
	int i = 0;
	char** arrofstr = ( char** ) calloc( scount+1, sizeof( *arrofstr ) );
	for ( i = 0; i < scount; i++ )
	{
		arrofstr[i] = ( char* ) calloc( 15, sizeof( **arrofstr ) );
		scanf( "%s", arrofstr[i] );
	}
	*count = scount;
	return arrofstr;
}

int strcomp( const void** one, const void** two )
{
	char* a = (char*) *one ;
	char* b = (char*) *two ;
	
	//printf( "%s %s\n", a,  b  );
	return  strlen( a ) - strlen( b ) ;
}

int Out_Del( char** arr, int count )
{
	int tmp = 0;
	int i = 0;
	for ( i = count - 1; i >= 0; i-- )
	{
		int size = strlen( arr[i] );
		if ( size != tmp )
			printf("%d\n", size );
		
		
		
		int j = 0;
		for ( j = size - 1; j >= 0; j-- )
		{
			putchar( arr[i][j] );
		}
		printf( " %s\n", arr[i] );
		tmp = size;
		free( arr[i] );
	}
	free( arr );
	return 0;
}

int main(int argc, char **argv)
{
	int count = 0;
	char** arr = Get_Strings( &count );
	//printf( "%d", count );
	
	qsort( arr, count, sizeof( char* ), strcomp );
	Out_Del( arr, count );
	
	
	return 0;
}
