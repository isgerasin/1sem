#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "Header_List.h"


int List_dump( List_t* list )
{
	assert( list );
	printf( "__________________________________\n");
	printf( "List_t %s (%s) [%0X] \n "
			"\t canary 1 = %0X \n", 
			"list", List_ok( list )? "ok" : "ERROR!!!" , 
			list, list->cnra );
	ListElem_dump( &list->datazero );
	printf( "\t count = %d \n\t canary 2 = %0X \n", list->count, list->cnrb );
	printf( "__________________________________\n");
	return TRUE;
	
	
}

int List_ok(   List_t* list )
{
	return list &&
		   list->cnra == CANARY &&
		   list->cnrb == CANARY &&
		   list->count >= 0 &&
		   ListElem_ok( &list->datazero );
}

int List_ctor( List_t* list, const char* name )
{
	assert( list );
	list->cnra = CANARY;
	list->cnrb = CANARY;
	list->count = 0;
	ListElem_ctor( &list->datazero, name );
	list->datazero.HeadList = list;
	
	ASSERT_OK( List, list )
	return List_ok( list );
}

int List_dtor( List_t* list )
{
	ASSERT_OK( List, list )
	
	ListElem_t* tmp = list->datazero.prev;
	ListElem_t* i = &list->datazero; 
	ListElem_dtor( i );
	if ( i->next == NULL) return TRUE;
	while ( i != tmp )
	{
		i = i->next;
		ListElem_dtor( i );
		
	}
	
	return TRUE;
}

int List_out( List_t* list )
{
	ASSERT_OK( List, list )
	
	ListElem_t* tmp = list->datazero.prev;
	ListElem_t* i = &list->datazero; 
	List_dump( list );
	while ( i != tmp )
	{
		i = i->next;
		printf(" %c \n", 18 );
		ListElem_dump( i );
	}
	return TRUE;
}

int List_dump_dot( List_t* list )
{
	ASSERT_OK( List, list )

	
	FILE* out = fopen( "graph_list.gv", "w" );
	if ( !out ) return FALSE;
	
	fprintf( out, "digraph List\n{\n\tnode[shape =polygon]; edge[dir=both];\n" );
	
	ListElem_t* tmp = list->datazero.prev;
	ListElem_t* i = &list->datazero; 
	int cntr = 0;

	fprintf( out, "\t\"%s\"->\"%s\"", list->datazero.data, list->datazero.next->data );
	fprintf( out, "\t{rank = same; %d[shape=plaintext]; \"%s\";}\n", cntr, list->datazero.data );
	cntr++;
	
	while ( i != tmp )
	{
		i = i->next;
		fprintf( out, "\t{edge[color = white]; %d->%d;}\n", cntr - 1, cntr );
		fprintf( out, "\t\"%s\"->\"%s\";\n", i->data, i->next->data);
		fprintf( out, "\t{rank = same; %d[shape=plaintext]; \"%s\";}\n", cntr, i->data );
		cntr++;
	}
	
	fprintf( out, "}" );
	
	fclose( out );
	
	system("C:\\\"Program Files (x86)\"\\Graphviz2.38\\bin\\dot.exe"
			" -Tsvg -O graph_list.gv");
	//system("rundll32.exe C:\\Windows\\System32\\shimgvw.dll,ImageView_Fullscreen" 
			//" C:\\Users\\User\\Documents\\\"Industrial Programming\"\\List\\Debug\\graph_list.gv.png" );
	
	return TRUE;
}

int ListElem_ok(   ListElem_t* lel)
{
	return lel &&
		   lel->cnra == CANARY &&
		   lel->cnrb == CANARY &&
		   lel->data != NULL &&
		   lel->next != NULL &&
		   lel->prev != NULL;
		   
}

int ListElem_ctor( ListElem_t* lel, const char* str )
{
	assert( lel && str );
	
	lel->cnra = CANARY;
	lel->cnrb = CANARY;
	lel->data = ( char* ) str;
	lel->next = lel;
	lel->prev = lel;
	lel->count = 1;
	
	ASSERT_OK( ListElem, lel )
	return ListElem_ok( lel );
}

int ListElem_dtor( ListElem_t* lel )
{
	ASSERT_OK( ListElem, lel )
	
	lel->data = NULL;
	lel->HeadList = NULL;
	lel->next = NULL;
	lel->prev = NULL;
	lel = NULL;
	
	return TRUE;
}

int ListElem_dump( ListElem_t* lel )
{
	printf("-------------------------\n");
	if ( !lel ) 
		printf( "ERROR!! NULL POINTER\n");
	else
	{
		printf("ListElem_t %s (%s) [%0X] \n "
				"\t canary 1 = %0X \n "
				"\t\t data [%0X] = \"%s\"\n"
				"\t next = [%0X]\n "
				"\t prev = [%0X]\n "
				"\t HeadList = [%0X]\n "
				"\t canary 2 = %0X\n", 
				"lel", ListElem_ok( lel )? "ok" : "ERROR!!!" , 
				lel, lel->cnra, lel->data, lel->data, 
				lel->next, lel->prev, lel->HeadList, lel->cnrb  );
	}
	printf("-------------------------\n");
	return TRUE;
}

int ListElem_add_begin( List_t* list, ListElem_t* lel )
{
	ASSERT_OK( List, list )
	ASSERT_OK( ListElem, lel )
	
	ListElem_t* tmp = list->datazero.next;
	list->datazero.next = lel;
	lel->prev = &list->datazero;
	tmp->prev = lel;
	lel->next = tmp;
	list->count++;
	lel->HeadList = list;
	
	ASSERT_OK( List, list )
	ASSERT_OK( ListElem, lel )
	
	return TRUE;
}

int ListElem_add_end( List_t* list, ListElem_t* lel )
{
	ASSERT_OK( List, list )
	ASSERT_OK( ListElem, lel )
	
	ListElem_t* tmp = list->datazero.prev;
	lel->next = &list->datazero;
	lel->prev = tmp;
	tmp->next = lel;
	list->datazero.prev = lel;
	lel->HeadList = list;
	list->count++;
	
	ASSERT_OK( List, list )
	ASSERT_OK( ListElem, lel )
	
	return TRUE;
}

int ListElem_add_middle_after( ListElem_t* lelmid, ListElem_t* lel )
{
	ASSERT_OK( ListElem, lel )
	ASSERT_OK( ListElem, lelmid )
	
	lel->next = lelmid->next;
	lelmid->next->prev = lel;
	
	lelmid->next = lel;
	lel->prev = lelmid;
	
	lel->HeadList = lelmid->HeadList;
	lel->HeadList->count++;
	
	
	ASSERT_OK( ListElem, lel )
	ASSERT_OK( ListElem, lelmid )
	
	return TRUE;
}

int ListElem_add_middle_before( ListElem_t* lelmid, ListElem_t* lel )
{
	ASSERT_OK( ListElem, lel )
	ASSERT_OK( ListElem, lelmid )
	
	lel->prev = lelmid->prev;
	lelmid->prev->next = lel;
	
	lel->next = lelmid;
	lelmid->prev = lel;
	
	lel->HeadList = lelmid->HeadList;
	lel->HeadList->count++;
	
	ASSERT_OK( ListElem, lel )
	ASSERT_OK( ListElem, lelmid )
	
	return TRUE;
}

int ListElem_del( ListElem_t* lel )
{
	ASSERT_OK( ListElem, lel )
	
	ListElem_t* tmp = lel->next;
	
	tmp->prev = lel->prev;
	tmp->prev->next = tmp;
	tmp->HeadList->count--;
	
	//ListElem_dtor( lel );
	
	return TRUE;
}

ListElem_t* ListElem_get_pntr_Slow_VerySlow( List_t* list, int n )
{
	ASSERT_OK( List, list )
	
	ListElem_t* tmp = &list->datazero;
	
	for ( int i = 0; i < n; i++ )
	{
		tmp = tmp->next;
	}
	
	ASSERT_OK( List, list )
	return tmp;
}







//#define ListElem_ctor(elem)  ListElem_ctor_((elem), #elem)


