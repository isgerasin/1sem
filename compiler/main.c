#include <stdio.h>
#include "Head.h"

int main(int argc, char **argv)
{
	Token* TokArr = NULL ;
	if ( argc == 2 )
	{
		TokArr = Get_Tokens_From_File( argv[1] );
		
	}
	else 
		TokArr = Get_Tokens_From_File( "programm.il" );
	
	if ( TokArr == NULL )
	{
		printf( "Error in File!!\n");
		return 1;
	}
	
	//Token_dump( TokArr, 50 );
	
	TreeList_t* list = Get0( TokArr );
	if ( list == NULL )
	{
		printf( "Error in File!!!\n");
		return 2;
	}
	
	
	//free( TokArr );
	TreeList_dump( list );
	Tree_Simpl( list->head );
	//Arr_of_Var_dump();
	TreeList_dump( list );
	WriteTree_to_assm( "assm.txt", list );
	//TreeList_dtor( list );
	free( TokArr );
	
}
