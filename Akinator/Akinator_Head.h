#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
//#include <locale.h>


#define DBG
#define TRUE 1
#define FALSE 0
#define MAXNAME 100
#define MAXELEM 50

#ifdef DBG
    #define ASSERT_OK( wat, strct ) \
        wat##_ok( strct ) ? : wat##_dump( (strct) )
#else
    #define ASSERT_OK( wat, strct )
#endif

struct TreeElem_t
{
    unsigned int cnra;
    const char* data;
    size_t datalen;
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
	char* buf;
    unsigned int cnrb;
};


struct stack_t
{
    int c1 = 'I' + 'L' +'y' + 'a';
    char** data = NULL;
    int count = -1;
    int size = -1;
    int c2 = 'I' + 'L' + 'y' + 'a';
};

int Stack_Ok(     stack_t* stk );

int Stack_Dump(   stack_t* stk, char* txt );

int Stack_Ctor(   stack_t* stk, int n );

int Stack_Dtor(   stack_t* stk );

int Stack_Push(   stack_t* stk, char* n );

char* Stack_Pop( stack_t* stk );



int File_Len( FILE* fl1 );

int TreeElem_ok(   TreeElem_t* telem );

int TreeElem_dump( TreeElem_t* telem );

TreeElem_t* TreeElem_ctor( TreeElem_t* telem, const char* str );

int TreeElem_dtor( TreeElem_t* telem );

TreeElem_t* TreeElem_ctor_sub( TreeElem_t* telem, const char* str, TreeElem_t* sub, const char* side );

int TreeElem_dtor_sub( TreeElem_t* telem );

int TreeElem_dump_dot( TreeElem_t* elem, FILE* out );

TreeElem_t* TreeElem_add( TreeElem_t* telem, const char* side, TreeElem_t* to );

int Tree_ok(       TreeElem_t* telem );

int TreeList_ok(   TreeList_t* tlist );

int TreeList_dump( TreeList_t* tlist );

int TreeList_dump_dot( TreeList_t* tlist );

int TreeList_ctor( TreeList_t* tlist, const char* str );

int TreeList_dtor( TreeList_t* tlist );

int TreeElem_write_pre( TreeElem_t* elem, FILE* out );

int TreeElem_read_pre(  TreeElem_t* elem );

int TreeList_write_pre( TreeList_t* tlist, const char* fname );

int TreeList_read_pre(  TreeList_t* tlist, const char* fname );

char TreeElem_search( TreeElem_t* elem, TreeElem_t* what );

int Akin_Loop( TreeList_t* tlist );

int Akin_Guess( TreeElem_t* telem );

void Akin_Add( TreeElem_t* telem );

void Akin_Charac( TreeElem_t* telem );

TreeElem_t* Akin_Search( TreeElem_t* telem, char* txt );

int Akin_Diff( TreeElem_t* telem );