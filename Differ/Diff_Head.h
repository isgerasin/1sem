#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define DBG 

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



