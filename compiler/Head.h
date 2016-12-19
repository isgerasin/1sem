#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define DBG 

#define MAXFUNCT 100
#define CANARY 0XABBAABBA
#define MAXVAL 100
#define MAXNAME 100
#define TFORMAT "v2.0Trsv"

#define IS_DVAL( elem ) ( (elem->t == val) && \
		!strcmp( array_of_variable_for_Tree_using_only_in_Diff_Tree[(int) elem->data].name, dval ) )
#define IS_OPER( operator ) ( ( elem->t == oper ) && \
		( operator == ( char ) elem->data ) )
#define IS_CONST( element, c ) ( ( (element)->t == constant ) && ((element)->data == c ) )
#define IS_FUNCT( f ) ( ( elem->t == function ) && ( (int) elem->data == f ) )

#define IS_NULL( pntr ) if ( !pntr ) return NULL


#ifdef DBG
    #define ASSERT_OK( wat, strct ) \
        wat##_ok( strct ) ? : wat##_dump( (strct) )
#else
    #define ASSERT_OK( wat, strct )
#endif 

typedef double Tree_Type;

typedef struct TreeElem_t TreeElem_t;

typedef struct TreeList_t TreeList_t;

typedef enum TypeElem_t TypeElem_t; 


struct Token
{
	int type;
	char* str;
	double data;
} typedef Token;

enum TypeElem_t
{
	unformat = 0,
	constant = 1,
	oper = 2,
	val = 3,
	function = 4,
	cycle = 5,
	leftbrac = 6,
	rightbrac = 7,
	begin = 8,
	end = 9,
	endofprog = 10,
	separ = 11,
	ifel = 12,
	admyfunc = 13,
	myfunc = 14
};

enum TreeOper_t
{
	#define DEF_CMD( ttype, word, num, name ) name = num,
	
	#include "KeyWords.h"
	max
	#undef DEF_CMD
};

enum TreeFunct_t
{
	_unformatf = 0,
	_sinus = 1,
	_cosinus = 2
};

struct TreeElem_t
{
    unsigned int cnra;
	TypeElem_t t;
	Tree_Type data;
	char* str;
    TreeElem_t* left;
    TreeElem_t* right;
    TreeElem_t* parent;
    unsigned int cnrb;
};

struct TreeList_t
{
    unsigned int cnra;
    TreeElem_t* head;
    size_t count;
    unsigned int cnrb;
};

struct Variable_t
{
	char name[MAXNAME];
	double data;
	char use;
} typedef Variable_t;

Variable_t array_of_variable_for_Tree_using_only_in_Diff_Tree[MAXVAL];

TreeElem_t* arr_of_functions[MAXFUNCT];

int arr_of_functions_cntr;

int arr_of_variable_cntr;

int File_Len( FILE* fl1 );

int TreeElem_ok(   TreeElem_t* telem );

int TreeElem_dump( TreeElem_t* telem );

TreeElem_t* TreeElem_ctor( TreeElem_t* telem, const char* data );

int TreeElem_dtor( TreeElem_t* telem );

TreeElem_t* TreeElem_ctor_sub( TreeElem_t* telem, const char* str, TreeElem_t* sub, const char* side );

int TreeElem_dtor_sub( TreeElem_t* telem );

int TreeList_ctor( TreeList_t* tlist, const char* str );

int TreeList_dtor( TreeList_t* tlist );

int Tree_ok( TreeElem_t* telem );

int TreeList_ok( TreeList_t* tlist );

int TreeElem_dump_dot( TreeElem_t* elem, FILE* out );

int TreeList_dump( TreeList_t* tlist );

int TreeList_dump_dot( TreeList_t* tlist );

char TreeElem_search( TreeElem_t* elem, TreeElem_t* what );

int TreeElem_write_pre( TreeElem_t* elem, FILE* out );

int TreeElem_Type_Write( TreeElem_t* elem, const char* tmp );

int Var_search( const char* tmp );

int TreeElem_read_pre(  TreeElem_t* elem );

int TreeList_write_pre( TreeList_t* tlist, const char* fname );

int TreeList_read_pre( TreeList_t* tlist, const char* fname );

int TreeList_write_in( TreeList_t* tlist, const char* fname );

int TreeElem_write_in( TreeElem_t* elem, FILE* out );

int TreeElem_read_in(  TreeElem_t* elem );

int TreeList_read_in( TreeList_t* tlist, const char* fname );

int TreeElem_dump_tex(  TreeElem_t* elem, FILE* out );

int TreeList_dump_tex(  TreeList_t* tlist, TreeList_t* tlistb );

TreeElem_t* TreeElem_cpy_sub( TreeElem_t* elem );

TreeList_t* TreeList_cpy_sub( TreeList_t* list );

TreeElem_t* TreeElem_cpy( TreeElem_t* elem );

TreeElem_t* New_Tree_elem( const char* data, TreeElem_t* left, TreeElem_t* right );

TreeElem_t* Diff_Tree( TreeElem_t* elem, const char* dval );

int Tree_Simpl( TreeElem_t* elem );

int Token_dump( Token* tokens, int size );

int Is_var( const char* name );

int Arr_of_Var_dump();

Token* Get_Tokens_From_File( const char* name );

TreeList_t* Get0( Token* ArrTok );

TreeElem_t* GetOpMD( Token* ArrTok, int* i );

TreeElem_t* GetOpSA( Token* ArrTok, int* i );

TreeElem_t* GetBr( Token* ArrTok, int* i );

TreeElem_t* GetN( Token* ArrTok, int* i );

TreeElem_t* GetPow( Token* ArrTok, int* i );

TreeElem_t* GetAssig( Token* ArrTok, int* i );

TreeElem_t* GetStr( Token* ArrTok, int* i );

TreeElem_t* GetFun( Token* ArrTok, int* i );

TreeElem_t* GetPiec( Token* ArrTok, int* i );

TreeElem_t* GetFoo( Token* ArrTok, int* i );

TreeElem_t* GetAdFoo( Token* ArrTok, int* i );
