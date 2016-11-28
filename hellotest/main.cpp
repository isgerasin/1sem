#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define MAXNAME 50

int main( int argc, char* argv[] )
{
	char str[50] = "";
	char* name = ( char* ) calloc( 2 * MAXNAME, sizeof( *name ) );
	char* diff = name + MAXNAME;

	
	printf( "А кто это был?\n" );
	scanf( "%[^\n\r]", name );
	
	scanf( "%*[^\n]" ); scanf( "%*c" );
	
	printf( "Чем отличается %s от %s\?\n", name, "telem->data" );
	
	//fgets( diff, MAXNAME, stdout );
	scanf( "%[^\n\r]", diff );
	printf( "%s! %s \n", diff, name );
	
	return 0;
}
