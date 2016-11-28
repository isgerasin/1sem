#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
//#define DBG 

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


enum TypeElem_t
{
	unformat = 0,
	constant = 1,
	oper = 2,
	val = 3
};

enum TreeOper_t
{
	add = '+',
	sub = '-',
	mul = '*',
	divv = '\\'
};

struct TreeElem_t
{
    unsigned int cnra;
	TypeElem_t t;
	Tree_Type data;
    TreeElem_t* left;
    TreeElem_t* right;
    TreeElem_t* parent;
    unsigned int cnrb;
};

struct TreeList_t
{
    unsigned int cnra;
    TreeElem_t head;
    size_t count;
    unsigned int cnrb;
};


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

int TreeList_dump_tex(  TreeList_t* tlist );

TreeElem_t* TreeElem_cpy_sub( TreeElem_t* elem );

TreeList_t* TreeList_cpy_sub( TreeList_t* list );
