#include <stdio.h>
#include "Diff_Head.h"

int main(int argc, char **argv)
{
	TreeList_t tlist = {};
	
	
	//sadfhasasdffdadsf
	TreeList_ctor( &tlist, "" );
	
	if ( !TreeList_read_pre( &tlist, "List.txt" ) ) return 1;
	
	
}

