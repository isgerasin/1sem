#include "Diff_Head.h"

int main(int argc, char **argv)
{
	
	TreeList_t* tlist = ( TreeElem_t* ) calloc( 1, sizeof ( *tlist ) );
	
	TreeList_ctor( tlist, "0" );
	
	//TreeList_dump( tlist );
	
	//sadfhasasdffdadsf vuiodoisa
	
	if ( !TreeList_read_in( tlist, "List_in.txt" ) ) return 1;

	//TreeList_write_in( &tlist, "List_in_w.txt" );
	
	//TreeList_dump_tex( &tlist );
	
	//TreeList_dump( tlist );
	
	
	
	//TreeList_t* tlista = TreeList_cpy_sub( tlist );
	//TreeList_dump( tlista );
	
	TreeList_t* tlista = ( TreeElem_t* ) calloc( 1, sizeof ( *tlist ) );
	
	TreeList_ctor( tlista, "0" );
	
	tlista->head = Diff_Tree( tlist->head, "x" );
	
	//TreeList_dump( tlist );
	//TreeList_dump( tlista );
	
	TreeList_dump_tex( tlist, tlista );
	//TreeList_dump_tex( tlista );
	

	//TreeList_dump_tex( tlist );
	
	TreeList_dtor( tlist );
	TreeList_dtor( tlista );
	return 0;
}

