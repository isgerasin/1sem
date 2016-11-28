#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "Header_List.h"


int main( int argc, char* argv[] )
{
	ListElem_t lel, lela, lelb, lelc, leld;
	List_t list;
	HashTble_t tbl;
	assert( HashTble_ctor( &tbl, MAXHASH ) );
	/*
	assert( ListElem_ctor( &lel, "first") ); 
	assert( ListElem_ctor( &lela, "second") ); 
	assert( ListElem_ctor( &lelb, "third" ) );
	assert( ListElem_ctor( &lelc, "fifth" ) );
	assert( ListElem_ctor( &leld, "sixth" ) );
	assert( List_ctor( &list, "Head" ) );
	
	
	ListElem_add_begin( &list,  &lel );
	ListElem_add_middle_before( &lel,  &lela );

	ListElem_add_end( &list, &lelc );
	ListElem_add_begin( &list , &leld );
	
	ListElem_add_middle_after( &lelc, &lelb );
	
	//ListElem_del( &lel );
	//List_out( &list );
	List_dump_dot( &list );
	
	//ListElem_t* outf = ListElem_get_pntr_Slow_VerySlow( &list, 2);
	//ListElem_dump( outf );
	
	//HashTble_dump( &tbl );
	//printf("+++++++++++++++++++++++\n");
	HashTble_dump_dot( &tbl );
	*/
	
	FILE* sh = fopen( "Sheakspeare.txt", "r" );
	int len = 2*File_Len( sh );
	char* sheak = ( char* ) calloc( len, sizeof( *sheak ) );
	fread( sheak, sizeof( *sheak ), len, sh );
	fclose( sh );
	
	assert( ListElem_ctor( &lel, "first") ); 
	ListElem_dump( &lel );
	
	HashTble_DoTest( &tbl, sheak, Hash_Func_2 );


	//List_out( tbl.data );
	//HashTble_dump( &tbl );
	//HashTble_dump_dot( &tbl );
	
	//assert( ListElem_dtor( &lel ) );
	assert( HashTble_dtor( &tbl ) );
	//assert( List_dtor( &list ) );
	
	

}
