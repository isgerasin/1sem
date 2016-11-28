#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "Header_List.h"

int FuncCount = 0;
unsigned int HashPrev = 0; 

int File_Len( FILE* fl1 )
{
	assert (fl1);
	
	fseek( fl1, 0, SEEK_END );
	int end = ftell (fl1);
	
	fseek (fl1, 0, SEEK_SET);
	int start = ftell (fl1);
	
	return ( end - start );
}

int HashTble_ok( HashTble_t* htbl )
{
	
	if ( !( htbl &&
			htbl->cnra == CANARY &&
			htbl->cnrb == CANARY &&
			htbl->count >= 0 &&
			htbl->data != NULL &&
			List_ok( htbl->data - 1 ) &&
			List_ok( htbl->data + htbl->count ) ) )
		{
			return FALSE;
		}
	else
	{
		for ( int i = 0; i < htbl->count; i++)
		{
			if ( ! List_ok( htbl->data + i ) )
				return FALSE;
		}
	}
	
	return TRUE;
}

int HashTble_ctor( HashTble_t* htbl, int len )
{
	assert( htbl );
	len++;
	htbl->cnra = CANARY;
	htbl->cnrb = CANARY;
	
	List_t* tmp = ( List_t* ) calloc( len + 2, sizeof( *tmp ) );
	if ( !tmp ) return FALSE; 
	htbl->count = len;
	assert( List_ctor( tmp, "ABBAABBA" ) );
	tmp++;
	assert( List_ctor( tmp + len , "ABBAABBA" ) );
	htbl->data = tmp;
	char hl[MAXHASH] = {};
	size_t hashlen = sprintf( hl, "%d" , MAXHASH );
	for (int i  = 0; i < len; i++ )
	{
		char* tmpa = ( char* ) calloc( hashlen + 5, sizeof( *tmpa ) );
		sprintf( tmpa, "Hash%d", i );
		List_ctor( htbl->data + i, tmpa );
		
	}
	
	return HashTble_ok( htbl );
}

int HashTble_dump( HashTble_t* htbl )
{
	
	for( int i = 0; i < htbl->count; i++ )
		List_out( htbl->data + i );
	return TRUE;
}

int HashTble_dtor( HashTble_t* htbl )
{
	ASSERT_OK( HashTble, htbl )
	
	for (int i  = 0; i < htbl->count; i++ )
	{
		List_dtor( htbl->data + i );
	}
	return TRUE;
}

int HashTble_dump_dot( HashTble_t* htbl )
{
	ASSERT_OK( HashTble, htbl )
	
	FILE* out = fopen( "graph_HTble.gv", "w" );
	if ( !out ) return FALSE;
	
	
	
	fprintf( out, "digraph Tabe\n{\n\tedge[dir=both]\n\t" );
	fprintf( out, "{node[shape = polygon]; rank = same;\n" );
	
	for ( int i = 0; i < htbl->count; i++ )
	{
		fprintf( out, "\t\t\"%s=%d\";\n",
				 htbl->data[i].datazero.data, htbl->data[i].datazero.count );
	}
	
	fprintf( out, "\t}\n" );
	
	for ( int j = 0; j < htbl->count; j++ )
	{
		ListElem_t* tmp = htbl->data[j].datazero.prev;
		ListElem_t* i =  &htbl->data[j].datazero;
		
		//printf( "\t\"%s\"->\"%s\";\n", i->data, i->next->data );
		fprintf( out, "\t\"%s=%d\"->\"%s=%d\";\n",
		i->data, i->count, i->next->data, i->next->count );
		while ( i != tmp && i != NULL )
		{
			
			i = i->next;
			assert(i);
			fprintf( out,  "\t\"%s=%d\"->\"%s=%d\";\n",
			i->data, i->count, i->next->data, i->next->count );
			
		}
	}
	
	fprintf( out, "}\n" );
	fclose( out );
	
	system("\"C:/Program Files (x86)/Graphviz2.38/bin/dot.exe\""
			" -Tsvg -O graph_HTble.gv");
	system("firefox graph_HTble.gv.svg");
	
	return TRUE;
}

int HashTble_DoTest( HashTble_t* htbl, char* data, unsigned int ( *HashFunc )( const char* ) )
{
	ASSERT_OK( HashTble, htbl )
	
	FuncCount++;
	char* tmp  = strtok( data, SEPARATION );
	int i = 1;
	
	while( tmp!= NULL )
	{
		unsigned int Hash = ( *HashFunc )( tmp ) ;
		
		if ( isalpha( tmp[0] ) && isdigit( tmp[0] ) );
		{
			ListElem_t* tmpelem = HashTble_Found( htbl, tmp, Hash );
			if ( tmpelem  == NULL )
			{
				
				ListElem_t* leltmp = ( ListElem_t* ) calloc( 1, sizeof( *leltmp ) );
				if ( !ListElem_ctor( leltmp, tmp ) )
					return FALSE;
				if ( !ListElem_add_end( &htbl->data[ Hash ], leltmp ) )
					return FALSE;
				i++;
				
			}
			else
			{
				tmpelem->count++;
			}
		}
		tmp = strtok( NULL, SEPARATION );
		
	}
	
	char hf [MAXHASH] = "";
	sprintf( hf, "plot%d.plt", FuncCount );
	FILE* out = fopen( hf, "w" );
	if ( !out ) return FALSE;
	
	fprintf( out, "set terminal png\n set output 'plot%d.png' \nset xrange[0:%d]\nplot \'-\' with boxes\n", FuncCount, htbl->count );
	for ( int j = 0; j < htbl->count; j++)
	{
		fprintf( out, "%d %d\n", j, htbl->data[j].count );
	}
	fclose( out );
	
	char syscom[150] = {};
	sprintf( syscom, "gnuplot %s\n", hf );
	
	system( syscom );
	system( "firefox plot1.png" );
	
	ASSERT_OK( HashTble, htbl )
	
	return TRUE;
}

ListElem_t* HashTble_Found( HashTble_t* htbl, char* data, int Hash )
{
	List_t* list = &htbl->data[ Hash ];
	
	ListElem_t* tmp = list->datazero.prev;
	ListElem_t* i = &list->datazero; 
	while ( i != tmp )
	{
		i = i->next;
		if ( strcmp( data, i->data ) == 0 )
			return i;
	}
	return NULL;
}

unsigned int Hash_Func_1( const char* str )
{
	return 0;
}

unsigned int Hash_Func_2( const char* str )
{
	return *str;
}

unsigned int Hash_Func_3( const char* str )
{
	return strlen( str );
}

unsigned int Hash_Func_4( const char* str )
{
	int sum = 0;
	for ( int i = 0; str[i]; i++ )
	{
		sum += str[i];
	}
	
	return sum;
}

unsigned int Hash_Func_5( const char* str )
{
	return Hash_Func_4( str ) / strlen( str );
}

unsigned int rol( unsigned int data )
{
	if ( data & 1 )
	{
		data = data >> 1;
		data = data | 4294967296; // 2 ^ 32
	}
	else
		data = data >> 1;

	return data;
}

unsigned int Hash_Func_6( const char* str )
{
	HashPrev = rol( HashPrev ) ^ str[0] * str[0];
	return HashPrev;
}

