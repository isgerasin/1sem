
#include "Akinator_Head.h"

int main( int argc, const char* argv[] )
{
	
	TreeList_t tlist = {};
	
	TreeList_ctor( &tlist, "" );
	
	if ( !TreeList_read_pre( &tlist, "List.txt" ) ) return 1;

	//TreeList_dump( &tlist );
	Akin_Loop( &tlist );
	
	
	TreeList_dtor( &tlist );
	return 0;
}
