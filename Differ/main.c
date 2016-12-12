#include "Diff_Head.h"

int main(int argc, char *argv[])
{
	TreeList_t* tlist = ( TreeElem_t* ) calloc( 1, sizeof ( *tlist ) );
	TreeList_ctor( tlist, "0" );
	if ( !TreeList_read_in( tlist, "List_in.txt" ) );// return 1;
	
	TreeList_t* tlista = ( TreeElem_t* ) calloc( 1, sizeof ( *tlist ) );
	TreeList_ctor( tlista, "0" );
	
	tlista->head = Diff_Tree( tlist->head, "x" );

	//TreeList_dump( tlist );
	TreeList_dump( tlista );
	TreeList_dump_tex( tlist, tlista );
	//TreeList_dump_tex( tlist, NULL );
	
	Tree_Simpl( tlista->head );
	TreeList_dump( tlista );
	TreeList_dump_tex( tlist, tlista );
	TreeList_dtor( tlist );
	TreeList_dtor( tlista );
	return 0;
}

