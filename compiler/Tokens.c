
#include "Head.h"


#define PBEGIN "Great_Ilya!_Please_do_my_programm."
#define PEND "Thank_you_Ilya!_I_kiss_your_hands."
#define SEPARATION " \n\r\t,"


int Arr_of_Var_dump()
{
	printf( "------------------------------------------------------\n");
	for ( int i = 0; i < MAXVAL; i++ )
		printf( "\tvar [%d]\n"
				"\t\t name = %s\n"
				"\t\t data = %lg\n"
				"\t\t use = %d\n",
				i, array_of_variable_for_Tree_using_only_in_Diff_Tree[i].name,
				array_of_variable_for_Tree_using_only_in_Diff_Tree[i].data, 
				array_of_variable_for_Tree_using_only_in_Diff_Tree[i].use );
	printf( "------------------------------------------------------\n");
	return TRUE;
}


int Token_dump( Token* tokens, int size )
{
	printf( "=================================\n" );
	if ( tokens == NULL ) 
		printf( "Error! Null adress\n" );
	else
		for ( int i = 0; i < size; i++ )
		printf( "Tokens[%d]\n"
				"\tType = %d\n"
				"\tData = %lg\n"
				"\tString = %s\n",
				i, tokens[i].type, tokens[i].data, tokens[i].str );
	printf( "=================================\n" );
	
	return 0;
}

int Is_var( const char* name )
{
	if ( name == NULL ) return -1;
	
	Variable_t* pntr = array_of_variable_for_Tree_using_only_in_Diff_Tree;
	
	
	for ( int i = 0; pntr[i].name[0] != '\0'; i++ )
		if ( strcmp( pntr[i].name, name ) == 0 )
			return TRUE;
	
	return FALSE;
}

int isnumber( const char* str )
{
	if ( str == NULL ) return FALSE;
	char* s = str;
	for ( s; *s != '\0'; s++ )
		if ( !isdigit( *s ) )
			return FALSE;
	return TRUE;
}

Token* Get_Tokens_From_File( const char* name )
{
	IS_NULL( name );
	arr_of_variable_cntr = 0;
	
	FILE* input = fopen( name, "r" );
	IS_NULL( input );
	
	int size = File_Len( input );
	int countoken = 0;
	Token* TokArr = ( Token* ) calloc( size / 2, sizeof( *TokArr ) );
	IS_NULL( TokArr );
	
	char* str = ( char* ) calloc( size, sizeof( *str ) );
	IS_NULL( str );
	
	int check = fread( str, sizeof( *str ), size, input );
	fclose( input );
	
	char* p = strtok( str, SEPARATION );
	if ( p == NULL )
	{
		printf( " Error! Bad file\n" );
		return NULL;
	}
	
	if ( strcmp( "var:", p ) )
	{
		printf( " Error at %s\nWhere are the variable declarations?", p );
		return NULL;
	}
	p = strtok( NULL, SEPARATION );
	while ( *p != ';' )
	{
		Var_search( p );
		p = strtok( NULL, SEPARATION );
	}
	p = strtok( NULL, SEPARATION );
	if ( strcmp( PBEGIN, p ) )
	{
		printf( "Error at %s\nWhere is the begin?\n", p );
		return NULL;
	}
	p = strtok( NULL, SEPARATION );
	
	#define DEF_CMD( ttype, word, num, name ) if ( !strcmp( p, word ) ){ \
											TokArr[countoken].type = ttype; \
											TokArr[countoken].str = p; \
											TokArr[countoken++].data = num; } \
										else
	
	while ( p != NULL )
	{
		if ( !strcmp( p, "//" ) )
		{
			p = strtok( NULL, "\n\r" );
			p = strtok( NULL,  SEPARATION );
		}
		#include "KeyWords.h"
		if ( isnumber( p ) )
		{
			TokArr[countoken].data = atof( p );
			TokArr[countoken].str = p;
			TokArr[countoken++].type = constant;
		}
		else if ( Is_var( p ) )
		{
			TokArr[countoken].data = Var_search( p );
			TokArr[countoken].str = p;
			TokArr[countoken++].type = val;
		}
		else if ( !strcmp( p, PEND ) )
		{
			TokArr[countoken].data = 0;
			TokArr[countoken].str = p;
			TokArr[countoken++].type = endofprog;
			break;
		}
		else if ( p[strlen(p)-1] == '(' )
		{
			TokArr[countoken].data = myfunc;
			TokArr[countoken].str = p;
			TokArr[countoken++].type = myfunc;
		}
		else
		{
			printf( "Error at %s\n", p );
			//break;
			return NULL;
		}
		p = strtok( NULL, SEPARATION );
	}
	#undef DEF_CMD
	
	
	
	return TokArr;
}

