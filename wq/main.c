#include <stdio.h>

int main(int argc, char **argv)
{
	FILE* f = fopen( "abc.txt", "w");
	char c = 0;
	int array_x[100];
	int array_y[100];
	int count_x = 0;
	int count_y = 0;
	while( c != EOF )
	{
		c = getc( f );
		if ( isdigit( c ) )
		{
			int res = 0;
			while ( !isspace( c ) )
			{
				res = res * 10 + c - '0' ;
				c = getc( f ); 
			}
			int x = res;
			c = getc( f );
			res = 0;
			c = getc( f );
			while ( !isspace( c ) )
			{
				res = res * 10 + c - '0' ;
				c = getc( f ); 
			}
			int y = res;
			array_x[count_x] = x;
			count_x++;
			array_y[count_y] = y;
			count_y++;
		}
	}
	
	
	
	
	return 0;
}
