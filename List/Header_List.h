#include <assert.h>

#define TRUE 1 
#define FALSE 0
#define CANARY 0xABBAABBA
#define MAXHASH 120
#define SEPARATION " .,\n[]\"!\?\';:" 
// "? \n\';:.,"
#define DBG 
#define NAMEVAR( var, num ) (var##num) 
#define NAMENUM( nm, numb, form ) nm #numb form

#ifdef DBG 
	#define ASSERT_OK( wat, strct ) \
		wat##_ok( strct ) ? : wat##_dump( strct );
#else
	#define ASSERT_OK( wat, strct )     
#endif

struct ListElem_t;

struct List_t;

struct ListElem_t
{
	unsigned int cnra;
	char* data;
	ListElem_t* next;
	ListElem_t* prev;
	List_t* HeadList;
	int count;
	unsigned int cnrb;
};

struct List_t
{
	unsigned int cnra;
	ListElem_t datazero;
	int count;
	unsigned int cnrb;
};

struct HashTble_t
{
	unsigned int cnra;
	List_t* data;
	int count;
	unsigned int cnrb;
};

int File_Len( FILE* fl1 );

int List_ctor( List_t* list, const char* name );

int List_dtor( List_t* list );

int List_ok(   List_t* list );

int List_dump( List_t* list );

int List_out(  List_t* list );

int List_dump_dot( List_t* list );


int ListElem_ctor( ListElem_t* lel, const char* str );

int ListElem_dtor( ListElem_t* lel );

int ListElem_ok(   ListElem_t* lel );

int ListElem_dump( ListElem_t* lel );


int ListElem_add_begin(        List_t* list, ListElem_t* lel );

int ListElem_add_end(          List_t* list, ListElem_t* lel );

int ListElem_add_middle_after(  ListElem_t* lelmid, ListElem_t* lel );

int ListElem_add_middle_before( ListElem_t* lelmid, ListElem_t* lel );

int ListElem_del( ListElem_t* lel );

ListElem_t* ListElem_get_pntr_Slow_VerySlow( List_t* list, int n );


int HashTble_ok( HashTble_t* htbl );

int HashTble_dump( HashTble_t* htbl );

int HashTble_ctor( HashTble_t* htbl, int len );

int HashTble_dtor( HashTble_t* htbl );

int HashTble_dump_dot( HashTble_t* htbl );

int HashTble_DoTest( HashTble_t* htbl, char* data, unsigned int ( *HashFunc )( const char* ) );

ListElem_t* HashTble_Found( HashTble_t* htbl, char* data, int Hash );

unsigned int Hash_Func_1( const char* str );

unsigned int Hash_Func_2( const char* str );

unsigned int Hash_Func_3( const char* str );

unsigned int Hash_Func_4( const char* str );

unsigned int Hash_Func_5( const char* str );

unsigned int Hash_Func_6( const char* str );

unsigned int rol( unsigned int);
