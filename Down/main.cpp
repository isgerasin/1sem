
#include "HeadDown.h"

int main(int argc, char **argv)
{
	char str[100] = "";
	while( 1 )
	{
		scanf( "%s", str );
		scanf( "%*[^]" );
		printf ( "%d\n", GetG0( str ) );
	}
	return 0;
}
