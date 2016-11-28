#include <stdio.h>
#include "Diff_Head.h"

int main(int argc, char **argv)
{
	TreeList_t tlist = {};
	
	
	//sadfhasasdffdadsf vuiodoisa
	TreeList_ctor( &tlist, "" );

	
	
	if ( !TreeList_read_in( &tlist, "List_in.txt" ) ) return 1;

	//TreeList_write_in( &tlist, "List_in_w.txt" );
	
	//TreeList_dump_tex( &tlist );
	
	TreeList_dump( &tlist );
	
	TreeList_t* tlista = TreeList_cpy_sub( &tlist );
	
	//TreeList_dump( tlista );
	
	TreeList_dump_tex( &tlist );
	
	TreeList_dtor( tlista );
	TreeList_dtor( &tlist );
	return 0;
}

