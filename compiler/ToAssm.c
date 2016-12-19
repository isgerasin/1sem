#include "Head.h"



int Count_pointers_using_in_ToAssm = 0;
int max_pushr = 0;
int Write_Elem( TreeElem_t* elem, FILE* output )
{
	if ( elem == NULL || output == NULL ) return FALSE;
	
	if ( elem->left->t != separ )
		Write_Oper( elem->left, output );
	else 
		Write_Elem( elem->left, output );
	
	
	Write_Elem( elem->right, output );
	
	return TRUE;
}

int Write_Oper( TreeElem_t* elem, FILE* output )
{
	if ( elem == NULL || output == NULL ) return FALSE;
	
	
	if ( (elem->t != ifel || elem->data != fi ) && elem->t != cycle && elem->t != admyfunc  && elem->t != myfunc )
	{

		if ( elem->t == oper && elem->data == '=' )
		{
			if ( elem->right != NULL )
				Write_Oper( elem->right, output );
			if ( elem->left != NULL ) 
				Write_Oper( elem->left, output );
		}
		//if ( ( elem->t == oper && elem->data != '=' || elem->t == function ) || elem->t == ifel && elem->data == esle  || elem->t == separ )
		else
		{
			if ( elem->left != NULL ) 
				Write_Oper( elem->left, output );
			if ( elem->right != NULL )
				Write_Oper( elem->right, output );
		}
		
		
	}
	
	if ( elem->t == admyfunc )
	{
		int c = ++Count_pointers_using_in_ToAssm;
		fprintf( output,  "jmp cont%d\n:%s\n", c, elem->left->str );
		if ( elem->right != NULL )
				Write_Oper( elem->right, output );
		fprintf( output,  "ret\n:cont%d\n", c );
	}
	else if ( elem->t == myfunc )
	{
		//TreeElem_dump( elem );
		TreeElem_t* tmpl = elem->left;
		TreeElem_t* tmpr = elem->right;
		int cout_var_func = 0;
		while ( tmpl != NULL )
		{
			//max_pushr
			//printf( "%lg\n", elem->data );
			fprintf( output, "pushr %cx\n"
							 "popr %cx\n"
							 , (char) (tmpl->data) + 'a', (char) (tmpr->data) +  arr_of_variable_cntr + 'a');
			tmpl = tmpl->left;
			tmpr = tmpr->left;
			cout_var_func++;
		}
		fprintf( output, "call %s\nnop\n", elem->str );
	}
	else if ( elem->t == constant )
		fprintf( output,  "push %lg\n", elem->data );
	else if ( elem->t == val &&  elem->parent->data == '=' && elem->parent->left != elem && elem->parent->left->t == val )
	{
		fprintf( output, "pushr %cx\n", (char) ('a' + elem->data) );
		max_pushr++;
	}
	else if ( elem->t == val && elem->parent->data == '=' )
		fprintf( output, "popr %cx\n", (char) ('a' + elem->data) );
	else if ( elem->t == val && elem->parent->data != '=' && elem->parent->data != in)
	{
		max_pushr++;
		fprintf( output, "pushr %cx\n", (char) ('a' + elem->data) );
	}
	else if ( elem->t == oper )
	{
		if ( IS_OPER( '+' ) )
			 fprintf( output, "add\n" );
		else if ( IS_OPER( '-' ) )
			 fprintf( output, "sub\n" );
		else if ( IS_OPER( '/' ) )
			 fprintf( output, "div\n" );
		else if ( IS_OPER( '*' ) )
			 fprintf( output, "mul\n" );
		else if ( IS_OPER( '^' ) )
			fprintf( output, "pow\n" );
		else if ( IS_OPER( A ) )
			fprintf( output, "a\n" );
		else if ( IS_OPER( B ) )
			fprintf( output, "b\n" );
		else if ( IS_OPER( E ))
			fprintf( output, "e\n" );
		else if ( IS_OPER( NE ))
			fprintf( output, "ne\n" );
		else if ( IS_OPER( AE ))
			fprintf( output, "ae\n" );
		else if ( IS_OPER( BE ))
			fprintf( output, "be\n" );
	}
	
	else if ( elem->t == function )
	{
		#define  DEF_CMD( ttype, word, num, name ) \
		if ( elem->data == num && ttype == function ) \
			fprintf( output, "%s\n", word ); else \
		
		#include "KeyWords.h"
			;
		
		if ( elem->data == in )
			fprintf( output, "popr %cx\n\n", (char) ('a' + elem->left->data) );
		else if ( elem->data == out )
			fprintf( output, "pop\n\n" );
		
		#undef DEF_CMD 
	}
	else if( elem->t == ifel && elem->data == fi )
	{
		int c = ++Count_pointers_using_in_ToAssm;

		fprintf( output, "push 0\n"
					  "jne true%d\n"
					  "jmp false%d\n"
					  ":true%d\npop\npop\n", c, c, c );
		Write_Oper( elem->left, output );
		fprintf( output, "jmp cont%d\n"
					  ":false%d\npop\npop\n", c, c );
		Write_Oper( elem->right, output );
		fprintf( output, ":cont%d\n\n", c );
	}
	else if( elem->t == cycle )
	{
		
		int c = ++Count_pointers_using_in_ToAssm;
		fprintf( output, ":beg%d\n", c );
		Write_Oper( elem->left, output );
		fprintf( output, "push 0\n"
						 "je cont%d\npop\npop\n", c );
		Write_Oper( elem->right, output );
		fprintf( output, "jmp beg%d\n"
						 ":cont%d\npop\npop\n\n", c, c );
		
	}
	
	return TRUE;
}

int Write_Fun( TreeElem_t* elem, FILE* output )
{
	if ( elem == NULL || output == NULL ) return FALSE;
	
	
	#define  DEF_CMD( ttype, word, num, name ) \
	if ( num != in && elem->data == num ) \
		fprintf( output, "pushr %cx\n" \
					  "%s\n", \
					(char) ('q' + elem->left->data) , word ); else \
	
	#include "KeyWords.h"
	if ( elem->data == in )
	{
		fprintf( output, "in\n" 
					  "popr %cx\n", 
					  (char) ('q' + elem->left->data) );
					  max_pushr++;
	}
	else
		return FALSE;
	#undef DEF_CMD 
	
	return TRUE;
}

int WriteTree_to_assm( const char* flname, TreeList_t* list )
{
	if ( flname == NULL || list == NULL ) return FALSE;
	
	FILE* output = fopen( flname, "w");
	if ( output == NULL ) return FALSE;
	fprintf( output, "%d\n", arr_of_variable_cntr );
	//printf( "%d\n", arr_of_variable_cntr );
	if ( !Write_Elem( list->head, output ) )
	{
		fprintf( stderr, "Error at assm!\n");
		return FALSE;
	}
	fprintf( output, "end\n" );
	
	fclose( output );
	
	return TRUE;
}


