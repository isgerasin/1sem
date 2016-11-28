#include "Diff_Head.h"

#define CANARY 0XABBAABBA
#define MAXVAL 100

double array_of_variable_for_Tree_using_only_in_Var_search[MAXVAL] = {};
int count_array_of_variable_for_Tree_using_only_in_Var_search = 0;

int DotNumber = 0;


int File_Len( FILE* fl1 )
{
    fseek( fl1, 0, SEEK_END );
    int end = ftell( fl1 );
    
    fseek( fl1, 0, SEEK_SET );
    
    return end;
}

int TreeElem_ok(   TreeElem_t* telem )
{
    return telem &&
           telem->cnra == CANARY &&
           telem->cnrb == CANARY &&
           telem->parent != NULL;
}

int TreeElem_dump( TreeElem_t* telem )
{
    printf( "____________________________________\n" );
    if ( telem == NULL )
        printf( "ERROR: NULL ADRESS!!\n" );
    else
    {
        printf( "TreeElem_t (%s) [%X]\n"
                "\tCanary 1 = %X\n"
                "\t\tData = \"%s\"\n"
                "\tRight = [%X]\n"
                "\tLeft  = [%X]\n"
                "\tParent = [%X]\n"
                "\tCanary 2 = %X\n",
                TreeElem_ok( telem ) ? "OK" : "ERROR",
                telem, telem->cnra, telem->data,
                telem->right, telem->left, telem->parent, telem->cnrb );
    }
    printf( "____________________________________\n" );
    return TRUE;
}

TreeElem_t* TreeElem_ctor( TreeElem_t* telem, Tree_Type data )
{
	ASSERT_OK( TreeElem, telem );
    if ( telem == NULL ) return NULL;
    
    telem->cnra = CANARY;
    telem->cnrb = CANARY;
    telem->data = data;
    telem->left = NULL;
    telem->right = NULL;
    telem->parent = telem;
    
    ASSERT_OK( TreeElem, telem );
    return telem ;
}

int TreeElem_dtor( TreeElem_t* telem )
{
	ASSERT_OK( TreeElem, telem );
    if ( telem == NULL ) return FALSE;
    
    telem->left = NULL;
    telem->right = NULL;
    telem->parent = NULL;
	if ( telem->parent != telem )
		free( telem );
	telem->data = 0;
    return TRUE;
}

TreeElem_t* TreeElem_ctor_sub( TreeElem_t* telem, Tree_Type str, TreeElem_t* sub, const char* side )
{
	ASSERT_OK( TreeElem, telem ); ASSERT_OK( TreeElem, sub );
	if ( telem == NULL || sub == NULL || side == NULL ) return NULL;
    TreeElem_ctor( telem, str );
    switch( *side )
    {
        case 'r' : telem->right = sub; break;
        case 'l' : telem->left  = sub; break;
        default : return FALSE;
    }
    sub->parent = telem;
    ASSERT_OK( TreeElem, telem ); ASSERT_OK( TreeElem, sub );
    return telem;
}

int TreeElem_dtor_sub( TreeElem_t* telem )
{
	ASSERT_OK( TreeElem, telem );
	if ( telem == NULL ) return FALSE;
	
    ASSERT_OK( TreeElem, telem );
    
    if ( telem->right != NULL )
        TreeElem_dtor_sub( telem->right );
    if ( telem->left != NULL )
        TreeElem_dtor_sub( telem->left );
    TreeElem_dtor( telem );
    
	ASSERT_OK( TreeElem, telem );
    return TRUE;
}

int TreeList_ctor( TreeList_t* tlist, Tree_Type str )
{
	ASSERT_OK( TreeList, tlist ); 
    if ( tlist == NULL )return FALSE;
	
    tlist->cnra = CANARY;
    tlist->cnrb = CANARY;
    tlist->count = 1;

    TreeElem_ctor( &tlist->head, str );
    tlist->head.parent = &tlist->head;
	
	ASSERT_OK( TreeList, tlist );
    return TRUE;
}

int TreeList_dtor( TreeList_t* tlist )
{
	ASSERT_OK( TreeList, tlist );
    if ( tlist == NULL ) return FALSE;

    
    tlist->cnra = 0;
    tlist->cnrb = 0;
    tlist->count = -1;
    TreeElem_dtor_sub( tlist->head.right );
	TreeElem_dtor_sub( tlist->head.left );
    
    return TRUE;
}


int Tree_ok( TreeElem_t* telem )
{
    if ( telem == NULL ) return TRUE;
    return TreeElem_ok( telem ) &&
            Tree_ok( telem->left ) &&
            Tree_ok( telem->right );
}

int TreeList_ok( TreeList_t* tlist )
{
    
    
    return  tlist &&
			tlist->count >= 1 &&
			tlist->cnra == CANARY &&
            tlist->cnrb == CANARY &&
            Tree_ok( &tlist->head );
}

int TreeElem_dump_dot( TreeElem_t* elem, FILE* out )
{

    if ( elem == NULL ) return TRUE;
    if ( elem->left )
    {
        fprintf( out, "\t\"%s\"->\"%s\"\n", elem->data, elem->left->data );
        TreeElem_dump_dot( elem->left, out );
    }
    if ( elem->right )
    {
        fprintf( out, "\t\"%s\"->\"%s\"\n", elem->data, elem->right->data );
        TreeElem_dump_dot( elem->right, out );
    }
    return  TRUE;
}

int TreeList_dump( TreeList_t* tlist )
{
    return TreeList_dump_dot( tlist );
}

int TreeList_dump_dot( TreeList_t* tlist )
{
	ASSERT_OK( TreeList, tlist );
    DotNumber++;
    if ( tlist == NULL )
	{
		printf( "ERROR!! NULL ADRESS LIST" );
		return FALSE;
	}
    char fname[ sizeof( "graph_tree.gv" ) + 3 ];
    sprintf( fname, "graph_tree%d.gv", DotNumber );
    FILE* out = fopen( fname, "w" );
    if ( out == NULL ) return FALSE;
    
    fprintf( out, "digraph Tree\n{\n\tnode[shape = polygon]; edge[dir=both];\n" );
    
    if ( TreeElem_dump_dot( &tlist->head, out ) == FALSE )
	{
		fprintf( out, "}" );
		fclose( out );
		printf( "Error! Can't dump the tree!\n" );
		return FALSE;
	}
    
    fprintf( out, "}" );
    fclose( out );
    char com[100] = "";
    sprintf( com, "dot"
            " -Tsvg -O %s", fname );
    system( com );
    char com1[20] = "";
    sprintf( com1, "firefox %s.svg", fname );
    system( com1 );
	ASSERT_OK( TreeList, tlist );
    return TRUE;
}

char TreeElem_search( TreeElem_t* elem, TreeElem_t* what )
{
	ASSERT_OK( TreeElem, elem ); ASSERT_OK( TreeElem, what );
	if ( elem == NULL || what == NULL ) return 'e';
	
	if ( elem->right == what ) return 'r';
	else if ( elem->left == what ) return 'l';
	else return 'n';

}

int TreeElem_write_pre( TreeElem_t* elem, FILE* out )
{
	ASSERT_OK( TreeElem, elem );
    if ( elem == NULL || out == NULL ) return FALSE;
    
    fprintf( out, "( \"%s\" ", elem->data );
    
    if ( elem->left == NULL )
        fprintf( out, "nil " );
    else
        if ( TreeElem_write_pre( elem->left, out ) == FALSE )
			return FALSE;
    if ( elem->right == NULL )
        fprintf( out, "nil " );
    else
        if ( TreeElem_write_pre( elem->left, out ) == FALSE )
			return FALSE;
    
    fprintf( out, ") " );
    
    ASSERT_OK( TreeElem, elem );
    return TRUE;
}

TypeElem_t TreeElem_Type_Write( TreeElem_t* elem, const char* tmp )
{
	ASSERT_OK( TreeElem, elem ); 
	if ( elem == NULL || tmp == NULL ) return FALSE;
	
	if ( '0' <= tmp[0] && tmp[0] <= '9')
	{
		elem->t = constant;
		elem->data = ( Tree_Type ) atof( tmp );
	}
	else if ( tmp[0] == '-' || tmp[0] == '+' || tmp[0] == '*' || tmp[0] == '//'  )
	{
		elem->t = oper;
		elem->data = ( Tree_Type ) tmp[0];
	}
	else if ( 'A' <= tmp[0] && tmp[0] <= 'z')
	{
		elem->t = val;
		elem->data = ( Tree_Type ) tmp[0];
	}
	else 
	{
		elem->t = unformat;
		elem->data = ( Tree_Type ) 0;
	}
	return elem->t;
		
}

//double array_of_variable_for_Tree_using_only_in_Var_search[MAXVAL];

double Var_Search( const char* tmp )
{
	double tmp2 = 0;
	for ( char* c = tmp; *c != '\0'; c ++)
		tmp2 = tmp2*100 + *c;
	
	
}

int TreeElem_read_pre(  TreeElem_t* elem )
{
	ASSERT_OK( TreeElem, elem );
    if ( elem == NULL ) return FALSE;
	
    int check = 0;
    char* tmp = strtok( NULL, "\"" );
	

	
	
    elem->data = ( Tree_Type ) atof( tmp );
	
    tmp = strtok( NULL, " " );

    switch ( *tmp )
    {
        case 'n' : elem->left = NULL; break;
        case '(' : TreeElem_read_pre( elem->left =
                    TreeElem_ctor( ( TreeElem_t* ) calloc( 1, sizeof( TreeElem_t ) ), 0 ) );
					elem->left->parent = elem; break;
        default : check++;
    }
    tmp = strtok( NULL, " " );
    //printf( "!%s!\n", tmp );
    switch ( *tmp )
    {
        case 'n' : elem->right = NULL; break;
        case '(' : TreeElem_read_pre( elem->right =
                    TreeElem_ctor( ( TreeElem_t* ) calloc( 1, sizeof( TreeElem_t ) ), 0 ) );
					elem->right->parent = elem; break;
        default: check++;
    }
    if ( *strtok( NULL, " " ) != ')' ) check++;
    
    ASSERT_OK( TreeElem, elem );
    return !check;
}

int TreeList_write_pre( TreeList_t* tlist, const char* fname )
{
	ASSERT_OK( TreeList, tlist );
    if ( tlist == NULL || fname == NULL ) return FALSE;
    
    FILE* out = fopen( fname, "wb" );
    if ( out == NULL ) return FALSE;
    fprintf( out, "v1.0Trsv " );
    
    if ( TreeElem_write_pre( &tlist->head, out ) == FALSE )
	{
		fclose( out );
		return FALSE;
	}
    
    fclose( out );
	ASSERT_OK( TreeList, tlist );
    return TRUE;
}

int TreeList_read_pre( TreeList_t* tlist, const char* fname )
{
    if ( tlist == NULL || fname == NULL ) return FALSE;
    
    FILE* in = fopen( fname, "r" );
    if ( in == NULL ) return FALSE;

    
    char* buff = ( char* ) calloc( File_Len( in ) + 2, sizeof( *buff ) );
    fread( buff, File_Len( in ) + 2, sizeof( *buff ), in );
    fclose( in );
    char* tmp = strtok( buff, " ");
    //printf( "!%s!%d\n", tmp, strcmp( tmp, "v1.0Trsv" ) );
    if ( strcmp( tmp, "v1.0Trsv" ) )
    {
        printf( "Error! Unknown Format %s\n", fname );
        return FALSE;
    }
    
    tmp = strtok( NULL, " " );
    if ( tmp == NULL || *tmp != '(' )
    {
        printf( "Error! Can't read the file or it empty %s\n", fname );
        return FALSE;
    }
    else
        if ( !TreeElem_read_pre( &tlist->head ) )
        {
            
            printf( "Error! Can't read the file %s\n", fname );
            TreeList_dtor( tlist );
            return FALSE;
            
        }
    return TRUE;
}